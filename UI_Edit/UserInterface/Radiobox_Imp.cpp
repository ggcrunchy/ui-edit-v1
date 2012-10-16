#include "Radiobox_Imp.h"
#include "UserInterface_Imp.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Radiobox object
/// @note Tested
Radiobox::Radiobox (void) : PaneItem(eRadiobox), mNumOptions(0), mUnderOption(eNoOption), mHeldOption(eNoOption), mInOption(eNoOption)
{
}

/// @brief Destructs a Radiobox object
/// @note Tested
Radiobox::~Radiobox (void)
{
}

/// @brief Acquires a Radiobox object
/// @param name Name used to reference the radiobox
/// @return Reference to the Radiobox object
/// @note Tested
Radiobox & Radiobox::Get (Uint32 name)
{
	return static_cast<Radiobox&>(Widget::Get(name));
}

/// @brief Grabs the option and issues an option grab event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Radiobox::GrabOption (void * pContext)
{
	//////////////////////////////
	// We record the held option.
	//////////////////////////////
	mHeldOption = mUnderOption;

	///////////////////////////////////////
	// We now issue the grab option event.
	///////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eRadioboxEvent_GrabOption, mHeldOption, pContext);
}

/// @brief Drops the option and issues an option drop event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Radiobox::DropOption (void * pContext)
{
	///////////////////////////////
	// We nullify the held option.
	///////////////////////////////
	Uint32 heldOption = mHeldOption;

	mHeldOption = eNoOption;

	///////////////////////////////////////
	// We now issue the grab option event.
	///////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eRadioboxEvent_DropOption, heldOption, pContext);
}

/// @brief Enter the option and issues an option enter event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Radiobox::EnterOption (void * pContext)
{
	////////////////////////////
	// We record the in option.
	////////////////////////////
	mInOption = mUnderOption;

	////////////////////////////////////////
	// We now issue the enter option event.
	////////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eRadioboxEvent_EnterOption, mInOption, pContext);
}

/// @brief Leaves the option and issues an option leave event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Radiobox::LeaveOption (void * pContext)
{
	/////////////////////////////
	// We nullify the in option.
	/////////////////////////////
	Uint32 inOption = mInOption;

	mInOption = eNoOption;

	////////////////////////////////////////
	// We now issue the leave option event.
	////////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eRadioboxEvent_LeaveOption, inOption, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Radiobox::Clear (void)
{
	Widget::Clear();

	mHeldOption = eNoOption;
	mInOption = eNoOption;
}

/// @brief Cleans all temporary input state
/// @note Tested
void Radiobox::CleanTemps (void)
{
	Widget::CleanTemps();

	mUnderOption = eNoOption;
}

/// @brief Handles situation where the radiobox becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Radiobox::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);
	assert(eNoOption == mInOption);
	assert(eNoOption == mHeldOption);

	////////////////////////////////////////////////////////////////////////////////////
	// We enter the radiobox. If an option is under the cursor, we enter the option. We 
	// then check for presses.
	////////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (mUnderOption != eNoOption) EnterOption(pContext);

	//////////////////////////////////////////////////////////////////////////////////
	// If the cursor is pressed, we do one of two things. If an option is beneath the
	// cursor and clicking is permitted, we grab it. Otherwise, we grab the radiobox.
	//////////////////////////////////////////////////////////////////////////////////
	if (bPressed) 
	{
		if (!mStatus[eCannotClick] && mUnderOption != eNoOption) GrabOption(pContext);

		else Grab(pContext);
	}
}

/// @brief Updates the radiobox when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the radiobox is no longer the widget of choice
/// @note Tested
bool Radiobox::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	UserInterface & UI = UserInterface::Get();

	//////////////////////////////////////////////////////////////////////////////////
	// If the option beneath the cursor differs from the current option, we leave it.
	//////////////////////////////////////////////////////////////////////////////////
	if (mInOption != eNoOption && mInOption != mUnderOption) LeaveOption(pContext);

	//////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the radiobox, we check three conditions: First, we check
	// whether the cursor has just entered the radiobox; if so, we enter it. Second, 
	// we check whether the cursor just entered an option, and if no option is held;
	// if so, we enter it. Third, we check whether the radiobox and its options are
	// not yet held, and if there was a press.
	//////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);
		if (mUnderOption != eNoOption && mUnderOption != mInOption && eNoOption == mHeldOption) EnterOption(pContext);

		if (bPressed && !(mStatus[eHeld] || mHeldOption != eNoOption))
		{
			//////////////////////////////////////////////////////////////////////////
			// If the cursor is over an option and clicking is permitted, we grab it.
			// Otherwise, we grab the radiobox.
			//////////////////////////////////////////////////////////////////////////
			if (!mStatus[eCannotClick] && mUnderOption != eNoOption) GrabOption(pContext);

			else Grab(pContext);
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the radiobox, but was during the last propagation, then 
	// we leave the radiobox.
	////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	////////////////////////////////////////////////////////////////////////////////////
	// If there is no press, we check whether an option or the radiobox is held. In the
	// first case, we drop the option; in the second, we drop the radiobox.
	////////////////////////////////////////////////////////////////////////////////////
	if (!bPressed)
	{
		assert(!(mStatus[eHeld] && mHeldOption != eNoOption));

		if (mHeldOption != eNoOption) DropOption(pContext);

		else if (mStatus[eHeld]) Drop(pContext);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the radiobox and neither the radiobox nor an
	// option is held, the radiobox is no longer the widget of choice.
	///////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !(mStatus[eHeld] || mHeldOption != eNoOption);
}