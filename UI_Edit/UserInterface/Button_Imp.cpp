#include "Button_Imp.h"
#include "UserInterface_Imp.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Button object
/// @note Tested
Button::Button (void) : PaneItem(eButton)
{
}

/// @brief Destructs a Button object
/// @note Tested
Button::~Button (void)
{
}

/// @brief Acquires a Button object
/// @param name Name used to reference the button
/// @return Reference to the Button object
/// @note Tested
Button & Button::Get (Uint32 name)
{
	return static_cast<Button&>(Widget::Get(name));
}

/// @brief Pushes the button and issues a button push event
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Button::Push (float fCursorX, float fCursorY, void * pContext)
{
	/////////////////////////////////
	// We flag the button as pushed.
	/////////////////////////////////
	mStatus[ePushed] = true;

	////////////////////////////////
	// We now issue the push event.
	////////////////////////////////
	UserInterface::Get().IssuePointEvent(eButtonEvent_Push, fCursorX, fCursorY, pContext);
}

/// @brief Releases the button and emits a button release event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Button::Release (void * pContext)
{
	/////////////////////////////////////
	// We flag the widget as not pushed.
	/////////////////////////////////////
	mStatus[ePushed] = false;

	///////////////////////////////////
	// We now issue the release event.
	///////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eButtonEvent_Release, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Button::Clear (void)
{
	Widget::Clear();

	mStatus[ePushed] = false;
}

/// @brief Handles situation where the button becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Button::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);
	assert(!mStatus[ePushed]);

	//////////////////////////////////////////////////////////////////////////////////////
	// We enter the button. If there was a press at the same time, we grab the button; if
	// the button is pushable, we push the button.
	//////////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (bPressed) 
	{
		Grab(pContext);

		if (!mStatus[eCannotPush]) Push(fCursorX, fCursorY, pContext);
	}
}

/// @brief Updates the button when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the button is no longer the widget of choice
/// @note Tested
bool Button::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the button, we check two conditions: First, we check whether 
	// the cursor has just entered the button; if so, we enter the button. Second, we
	// check whether the button is not yet held, and if there was a press--since the
	// cursor is over the button, we grab the button; if the button is pushable, we also
	// push the button.
	//////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);

		if (!mStatus[eHeld] && bPressed) 
		{
			Grab(pContext);

			if (!mStatus[eCannotPush]) Push(fCursorX, fCursorY, pContext);
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the button, but was during the last propagation, then we
	// leave the button.
	//////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	//////////////////////////////////////////////////////////////////////////////////////
	// We check if the button is held, but there is no press. If the button is pushed, we
	// release the button. We then drop the button.
	//////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eHeld] && !bPressed)
	{
		if (mStatus[ePushed]) Release(pContext);

		Drop(pContext);
	}

	/////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the button and the button is not held, the
	// button is no longer the widget of choice.
	/////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !mStatus[eHeld];
}