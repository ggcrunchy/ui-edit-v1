#include "Checkbox_Imp.h"
#include "UserInterface_Imp.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Checkbox object
/// @note Tested
Checkbox::Checkbox (void) : PaneItem(eCheckbox)
{
}

/// @brief Destructs a Checkbox object
/// @note Tested
Checkbox::~Checkbox (void)
{
}

/// @brief Acquires a Checkbox object
/// @param name Name used to reference the checkbox
/// @return Reference to the Checkbox object
/// @note Tested
Checkbox & Checkbox::Get (Uint32 name)
{
	return static_cast<Checkbox&>(Widget::Get(name));
}

/// @brief Toggles the check state and issues a check or uncheck event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Checkbox::Toggle (void * pContext)
{
	///////////////////////////////////////////////////////////////////
	// We flag the checkbox as not clicked, and toggle the check flag.
	///////////////////////////////////////////////////////////////////
	mStatus[eClicked] = false;
	mStatus[eChecked] = !mStatus[eChecked];

	////////////////////////////////////////////
	// We now issue the check or uncheck event.
	////////////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(mStatus[eChecked] ? eCheckboxEvent_Check : eCheckboxEvent_Uncheck, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Checkbox::Clear (void)
{
	Widget::Clear();

	mStatus[eClicked] = false;
}

/// @brief Handles situation where the checkbox becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Checkbox::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);

	///////////////////////////////////////////////////////////////////////////////////////
	// We enter the checkbox. If there was a press at the same time, we grab the checkbox,
	// and click the checkbox if permitted.
	///////////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (bPressed)
	{
		Grab(pContext);

		if (!mStatus[eCannotClick]) mStatus[eClicked] = true;
	}
}

/// @brief Updates the checkbox when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the checkbox is no longer the widget of choice
/// @note Tested
bool Checkbox::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the checkbox, we check two conditions: First, we check
	// whether the cursor has just entered the checkbox; if so, we enter the
	// checkbox. Second, we check whether the checkbox is not yet held, and if
	// there was a press--since the cursor is over the checkbox, we grab it, and
	// click if it permitted.
	////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);

		if (!mStatus[eHeld] && bPressed)
		{
			Grab(pContext);

			if (!mStatus[eCannotClick]) mStatus[eClicked] = true;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the checkbox, but was during the last propagation, then 
	// we leave the checkbox.
	/////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	/////////////////////////////////////////////////////////////////////////////////////
	// We check if the checkbox is held, but there is no press. We drop the checkbox. If
	// the checkbox is clicked, we then toggle it.
	/////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eHeld] && !bPressed)
	{
		Drop(pContext);

		if (mStatus[eClicked]) Toggle(pContext);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the checkbox and the checkbox is not held, the
	// checkbox is no longer the widget of choice.
	/////////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !mStatus[eHeld];
}