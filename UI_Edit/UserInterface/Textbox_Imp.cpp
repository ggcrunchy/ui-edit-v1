#include "Textbox_Imp.h"
#include "UserInterface_Imp.h"
#include "Textbox.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Textbox object
/// @note Tested
Textbox::Textbox (void) : PaneItem(eTextbox), mFitBestSpot(0), mOffset(0), mCursor(0), mMaxLength(0), mNumSelect(0), mUnderSpot(eNoSpot), mHeldSpot(eNoSpot)
{
}

/// @brief Destructs a Textbox object
/// @note Tested
Textbox::~Textbox (void)
{
}

/// @brief Acquires a Textbox object
/// @param name Name used to reference the textbox
/// @return Reference to the Textbox object
/// @note Tested
Textbox & Textbox::Get (Uint32 name)
{
	return static_cast<Textbox&>(Widget::Get(name));
}

/// @brief Trims the interval [start, start + count) to [start, size)
/// @param start The index of the start of the interval
/// @param count The count of items in the interval
/// @return The modified item count
/// @note Tested
Uint32 Textbox::TrimToSize (Uint32 start, Uint32 count)
{
	if (start + count > mString.size())
	{
		return static_cast<Uint32>(mString.size()) - start;
	}

	return count;
}

/// @brief Trims the interval [start, start + count) to [start, max)
/// @param start The index of the start of the interval
/// @param count The count of items in the interval
/// @return The modified item count
/// @note Tested
Uint32 Textbox::TrimToMax (Uint32 start, Uint32 count)
{
	if (start + count > mMaxLength)
	{
		return mMaxLength - start;
	}

	return count;
}

/// @brief Gets a textbox's best fit spot in [0,size]
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
Uint32 Textbox::GetSpot (float fCursorX, float fCursorY, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// We start with the held spot. If there is no fit best spot handler, we just settle
	// for this. Otherwise, we call the handler, and clamp to [0,size] if needed. 
	/////////////////////////////////////////////////////////////////////////////////////
	Uint32 spot = mHeldSpot;

	if (mFitBestSpot != 0)
	{
		spot = mFitBestSpot(UserInterface::Get().mChoice, fCursorX, fCursorY, pContext);

		if (spot > mString.size()) spot = static_cast<Uint32>(mString.size());
	}

	return spot;
}

/// @brief Grabs a textbox item and issues a grab spot event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Textbox::GrabSpot (void * pContext)
{
	///////////////////////////////////////////////////////////
	// We record the held spot, and initiate a one-item range.
	///////////////////////////////////////////////////////////
	mHeldSpot = mUnderSpot;
	mRangeEnd = mUnderSpot;

	/////////////////////////////////////
	// We now issue the grab spot event.
	/////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eTextboxEvent_GrabSpot, mHeldSpot, pContext);
}

/// @brief Drops a textbox spot and issues a drop spot event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Textbox::DropSpot (void * pContext)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// We first find the edge positions in the text range. We then nullify the held spot.
	//////////////////////////////////////////////////////////////////////////////////////
	Uint32 min = mHeldSpot < mRangeEnd ? mHeldSpot : mRangeEnd;
	Uint32 max = mHeldSpot > mRangeEnd ? mHeldSpot : mRangeEnd;

	mHeldSpot = eNoSpot;

	/////////////////////////////////////
	// We now issue the drop spot event.
	/////////////////////////////////////
	UserInterface::Get().IssueRangeEvent(eTextboxEvent_DropSpot, min, max - min + 1, pContext);
}

/// @brief Drags over a textbox text range and issues a textbox drag over event
/// @param over Index of spot best fit by cursor
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Textbox::DragOver (Uint32 over, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////
	// We set the range end position. We then find the edge order in the text range.
	/////////////////////////////////////////////////////////////////////////////////
	mRangeEnd = over;

	Uint32 min = mHeldSpot < mRangeEnd ? mHeldSpot : mRangeEnd;
	Uint32 max = mHeldSpot > mRangeEnd ? mHeldSpot : mRangeEnd;

	/////////////////////////////////////
	// We now issue the drag over event.
	/////////////////////////////////////
	UserInterface::Get().IssueRangeEvent(eTextboxEvent_DragOver, min, max - min + 1, pContext);
}

/// @brief Modifies selection properties affected by insertion
/// @param where Index of insertion
/// @param count Count of inserted characters
/// @note Tested
void Textbox::AdjustForInsert (Uint32 where, Uint32 count)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// If the insertion occurred before the selected text, we move the selection ahead by
	// the count of inserted items.
	//////////////////////////////////////////////////////////////////////////////////////
	if (where < mSelect)
	{
		mSelect += count;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Otherwise, we check whether we inserted into the selection. If so, we augment it
	// by the count of inserted items.
	////////////////////////////////////////////////////////////////////////////////////
	else if (where >= mSelect && where < mSelect + mNumSelect)
	{
		mNumSelect += count;
	}
}

/// @brief Clears all important input state
/// @note Tested
void Textbox::Clear (void)
{
	Widget::Clear();

	mHeldSpot = eNoSpot;
}

/// @brief Cleans all temporary input state
/// @note Tested
void Textbox::CleanTemps (void)
{
	Widget::CleanTemps();

	mUnderSpot = eNoSpot;
}

/// @brief Handles situation where the textbox becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Textbox::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);
	assert(eNoSpot == mHeldSpot);

	///////////////////////////////////////////////////////////////////////////////////
	// We enter the textbox. We then check for presses. If a spot was under the cursor
	// during a press and clicking is permitted, we grab the spot. Otherwise, we grab
	// the textbox.
	///////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (bPressed) 
	{
		if (!mStatus[eCannotClickSpot] && mUnderSpot != eNoSpot) GrabSpot(pContext);

		else Grab(pContext);
	}
}

/// @brief Updates the textbox when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the textbox is no longer the widget of choice
/// @note Tested
bool Textbox::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	///////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the textbox, we check two conditions: First, we check whether 
	// the cursor has just entered the textbox; if so, we enter the textbox. Second, we
	// check whether neither the textbox nor its spots are held, and if there was a press.
	///////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);

		if (bPressed && !(mStatus[eHeld] || mHeldSpot != eNoSpot))
		{
			/////////////////////////////////////////////////////////////////////////////
			// If the cursor is over a spot and clicking is permitted, we grab the spot.
			// Otherwise, we grab the textbox
			/////////////////////////////////////////////////////////////////////////////
			if (!mStatus[eCannotClickSpot] && mUnderSpot != eNoSpot) GrabSpot(pContext);

			else Grab(pContext);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the textbox, but was during the last propagation, then we
	// leave the textbox.
	///////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	//////////////////////////////////////////////////////////////////////////////////////
	// If there is no press, we check whether a spot or the textbox is held. In the first
	// case, we drop the spot; in the second, we drop the textbox.
	//////////////////////////////////////////////////////////////////////////////////////
	if (!bPressed)
	{
		assert(!(mStatus[eHeld] && mHeldSpot != eNoSpot));

		if (mHeldSpot != eNoSpot) DropSpot(pContext);

		else if (mStatus[eHeld]) Drop(pContext);
	}

	///////////////////////////////////////////////////////////////////////////////////
	// If a spot is held and dragging is permitted, we fit the cursor coordinates to a
	// spot. If this spot varies from the current range cap, we drag over the text.
	///////////////////////////////////////////////////////////////////////////////////
	if (mHeldSpot != eNoSpot && !mStatus[eCannotDragOver])
	{
		Uint32 spot = GetSpot(fCursorX, fCursorY, pContext);

		if (spot != mRangeEnd) DragOver(spot, pContext);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the textbox and neither a spot nor the textbox
	// is held, the textbox is no longer the widget of choice.
	/////////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !(mStatus[eHeld] || mHeldSpot != eNoSpot);
}