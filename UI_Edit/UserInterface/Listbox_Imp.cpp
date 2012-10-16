#include "Listbox_Imp.h"
#include "UserInterface_Imp.h"
#include "Listbox.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Listbox::Item object
/// @note Tested
Listbox::Item::Item (void) : mContext(0), mSelected(false)
{
}

/// @brief Destructs a Listbox::Item object
/// @note Tested
Listbox::Item::~Item (void)
{
}

/// @brief Constructs a Listbox object
/// @note Tested
Listbox::Listbox (void) : PaneItem(eListbox), mFitBestItem(0), mOffset(0), mCapacity(0), mUnderItem(eNoItem), mHeldItem(eNoItem), mInItem(eNoItem)
{
}

/// @brief Destructs a Listbox object
/// @note Tested
Listbox::~Listbox (void)
{
	////////////////////////////////////////////////////
	// On destruction, we clean up any remaining items.
	////////////////////////////////////////////////////
	for (Uint32 item = 0; item < mItems.size(); ++item)
	{
		delete mItems[item];
	}
}

/// @brief Acquires a Listbox object
/// @param name Name used to reference the listbox
/// @return Reference to the Listbox object
/// @note Tested
Listbox & Listbox::Get (Uint32 name)
{
	return static_cast<Listbox&>(Widget::Get(name));
}

/// @brief Trims the interval [start, start + count) to [start, size)
/// @param start The index of the start of the interval
/// @param count The count of items in the interval
/// @return The modified item count
/// @note Tested
Uint32 Listbox::TrimToSize (Uint32 start, Uint32 count)
{
	if (start + count > mItems.size())
	{
		return static_cast<Uint32>(mItems.size()) - start;
	}

	return count;
}

/// @brief Gets a listbox's best fit item in [0,size)
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
Uint32 Listbox::GetItem (float fCursorX, float fCursorY, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// We start with the held item. If there is no fit best item handler, we just settle
	// for this. Otherwise, we call the handler, and clamp to [0,size) if needed. 
	/////////////////////////////////////////////////////////////////////////////////////
	Uint32 item = mHeldItem;

	if (mFitBestItem != 0)
	{
		item = mFitBestItem(UserInterface::Get().mChoice, fCursorX, fCursorY, pContext);

		if (item >= mItems.size()) item = static_cast<Uint32>(mItems.size() - 1);
	}

	return item;
}

/// @brief Grabs a listbox item and issues a grab item event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Listbox::GrabItem (void * pContext)
{
	///////////////////////////////////////////////////////////
	// We record the held item, and initiate a one-item range.
	///////////////////////////////////////////////////////////
	mHeldItem = mUnderItem;
	mRangeEnd = mUnderItem;

	/////////////////////////////////////
	// We now issue the grab item event.
	/////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eListboxEvent_GrabItem, mHeldItem, pContext);
}

/// @brief Drops a listbox item and issues a drop item event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Listbox::DropItem (void * pContext)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// We first find the edge positions in the item range. We then nullify the held item.
	//////////////////////////////////////////////////////////////////////////////////////
	Uint32 min = mHeldItem < mRangeEnd ? mHeldItem : mRangeEnd;
	Uint32 max = mHeldItem > mRangeEnd ? mHeldItem : mRangeEnd;

	mHeldItem = eNoItem;

	/////////////////////////////////////
	// We now issue the drop item event.
	/////////////////////////////////////
	UserInterface::Get().IssueRangeEvent(eListboxEvent_DropItem, min, max - min + 1, pContext);
}

/// @brief Enters a listbox item and issues an enter item event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Listbox::EnterItem (void * pContext)
{
	//////////////////////////
	// We record the in item.
	//////////////////////////
	mInItem = mUnderItem;

	/////////////////////////////////////
	// We now issue the grab item event.
	/////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eListboxEvent_EnterItem, mInItem, pContext);
}

/// @brief Leaves a listbox item and issues a leave item event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Listbox::LeaveItem (void * pContext)
{
	///////////////////////////////
	// We now nullify the in item.
	///////////////////////////////
	Uint32 inItem = mInItem;

	mInItem = eNoItem;

	/////////////////////////////////////
	// We now issue the grab item event.
	/////////////////////////////////////
	UserInterface::Get().IssueIndexEvent(eListboxEvent_LeaveItem, inItem, pContext);
}

/// @brief Drags over a listbox item range and issues a listbox drag over event
/// @param over Index of item best fit by cursor
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Listbox::DragOver (Uint32 over, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////
	// We set the range end position. We then find the edge order in the item range.
	/////////////////////////////////////////////////////////////////////////////////
	mRangeEnd = over;

	Uint32 min = mHeldItem < mRangeEnd ? mHeldItem : mRangeEnd;
	Uint32 max = mHeldItem > mRangeEnd ? mHeldItem : mRangeEnd;

	/////////////////////////////////////
	// We now issue the drag over event.
	/////////////////////////////////////
	UserInterface::Get().IssueRangeEvent(eListboxEvent_DragOver, min, max - min + 1, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Listbox::Clear (void)
{
	Widget::Clear();

	mHeldItem = eNoItem;
	mInItem = eNoItem;
}

/// @brief Cleans all temporary input state
/// @note Tested
void Listbox::CleanTemps (void)
{
	Widget::CleanTemps();

	mUnderItem = eNoItem;
}

/// @brief Handles situation where the listbox becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Listbox::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);
	assert(eNoItem == mHeldItem);

	//////////////////////////////////////////////////////////////////////////////////////
	// We enter the listbox. If we are over an item, we enter the item. We then check for
	// presses. If an item was under the cursor during a press and clicking is permitted,
	// we grab the item. Otherwise, we grab the listbox.
	//////////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (mUnderItem != eNoItem) EnterItem(pContext);

	if (bPressed) 
	{
		if (!mStatus[eCannotClickItem] && mUnderItem != eNoItem) GrabItem(pContext);

		else Grab(pContext);
	}
}

/// @brief Updates the listbox when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the listbox is no longer the widget of choice
/// @note Tested
bool Listbox::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	//////////////////////////////////////////////////////////////////////////////
	// If the item beneath the cursor differs from the current item, we leave it.
	//////////////////////////////////////////////////////////////////////////////
	if (mInItem != eNoItem && mInItem != mUnderItem) LeaveItem(pContext);

	/////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the listbox, we check three conditions: First, we check 
	// whether the cursor has just entered the listbox; if so, we enter the listbox.
	// Second, we check whether the cursor has just entered a new item, and no item
	// is held; if so, we enter the item. Finally, we check whether neither the
	// listbox nor its items are held, and if there was a press.
	/////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);
		if (mUnderItem != eNoItem && mUnderItem != mInItem && eNoItem == mHeldItem) EnterItem(pContext);

		if (bPressed && !(mStatus[eHeld] || mHeldItem != eNoItem))
		{
			//////////////////////////////////////////////////////////////////////////////
			// If the cursor is over an item and clicking is permitted, we grab the item.
			// Otherwise, we grab the listbox.
			//////////////////////////////////////////////////////////////////////////////
			if (!mStatus[eCannotClickItem] && mUnderItem != eNoItem) GrabItem(pContext);

			else Grab(pContext);
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the listbox, but was during the last propagation, then we
	// leave the listbox.
	///////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	///////////////////////////////////////////////////////////////////////////////////////
	// If there is no press, we check whether an item or the listbox is held. In the first
	// case, we drop the item; in the second, we drop the listbox.
	///////////////////////////////////////////////////////////////////////////////////////
	if (!bPressed)
	{
		assert(!(mStatus[eHeld] && mHeldItem != eNoItem));

		if (mHeldItem != eNoItem) DropItem(pContext);

		else if (mStatus[eHeld]) Drop(pContext);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// If an item is held and dragging is permitted, we fit the cursor coordinates to an 
	// item. If this item varies from the current range cap, we drag over the items.
	/////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eCannotDragOver] && mHeldItem != eNoItem)
	{
		Uint32 item = GetItem(fCursorX, fCursorY, pContext);

		if (item != mRangeEnd) DragOver(item, pContext);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the listbox and neither an item nor the listbox
	// is held, the listbox is no longer the widget of choice.
	//////////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !(mStatus[eHeld] || mHeldItem != eNoItem);
}