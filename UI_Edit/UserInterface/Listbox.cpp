/// @file
/// Interface for listbox widgets

#include "Listbox_Imp.h"
#include "UserInterface_Imp.h"
#include "Listbox.h"
#include "PaneItem.h"
#include "UserInterface.h"
#include <cassert>

/// @brief Instantiates a listbox
/// @param name [out] On success, the name used to reference the listbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_Create (Uint32 * name)
{
	assert(name != 0);

	if (!UserInterface_WasInit()) return 0;

	return UserInterface::Get().CreateWidget(Widget::eListbox, name);
}

/// @brief Gets the count of items in the listbox
/// @param name Name used to reference the listbox
/// @param count [out] On success, the item count
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_GetItemCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!Listbox_IsValid(name)) return 0;

	*count = static_cast<Uint32>(Listbox::Get(name).mItems.size());

	return 1;
}

/// @brief Sets the offset from which to begin drawing and hit testing items
/// @param name Name used to reference the listbox
/// @param offset Offset at which to begin
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_SetOffset (Uint32 name, Uint32 offset)
{
	if (!Listbox_IsValid(name)) return 0;

	Listbox::Get(name).mOffset = offset;

	return 1;
}

/// @brief Gets the offset from which to begin drawing and hit testing items
/// @param name Name used to reference the listbox
/// @param offset [out] On success, the offset at which to begin
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_GetOffset (Uint32 name, Uint32 * offset)
{
	assert(offset != 0);

	if (!Listbox_IsValid(name)) return 0;

	*offset = Listbox::Get(name).mOffset;

	return 1;
}

/// @brief Sets the number of items that may be drawn and hit tested
/// @param name Name used to reference the listbox
/// @param capacity Number of items on which to operate
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_SetCapacity (Uint32 name, Uint32 capacity)
{
	if (!Listbox_IsValid(name)) return 0;

	Listbox::Get(name).mCapacity = capacity;

	return 1;
}

/// @brief Gets the number of items that may be drawn and hit tested
/// @param name Name used to reference the listbox
/// @param capacity [out] On success, the number of items on which to operate
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_GetCapacity (Uint32 name, Uint32 * capacity)
{
	assert(capacity != 0);

	if (!Listbox_IsValid(name)) return 0;

	*capacity = Listbox::Get(name).mCapacity;

	return 1;
}

/// @brief Gets the listbox's currently held item
/// @param name Name used to reference the listbox
/// @param item [out] On success, the held item
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_GetHeldItem (Uint32 name, Uint32 * item)
{
	assert(item != 0);

	if (!Listbox_IsValid(name)) return 0;

	Listbox & listbox = Listbox::Get(name);

	if (Listbox::eNoItem == listbox.mHeldItem) return 0;

	*item = listbox.mHeldItem;

	return 1;
}

/// @brief Gets the listbox's currently entered item
/// @param name Name used to reference the listbox
/// @param item [out] On success, the entered item
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_GetInItem (Uint32 name, Uint32 * item)
{
	assert(item != 0);

	if (!Listbox_IsValid(name)) return 0;

	Listbox & listbox = Listbox::Get(name);

	if (Listbox::eNoItem == listbox.mInItem) return 0;

	*item = listbox.mInItem;

	return 1;
}

/// @brief Sets an item's context
/// @param name Name used to reference the listbox
/// @param item Index of item in the listbox
/// @param context User-defined context
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_SetItemContext (Uint32 name, Uint32 item, Uint32 context)
{
	if (!Listbox_IsItemValid(name, item, SDL_FALSE)) return 0;

	Listbox::Get(name).mItems[item]->mContext = context;

	return 1;
}

/// @brief Gets an item's context
/// @param name Name used to reference the listbox
/// @param item Index of item in the listbox
/// @param context [out] On success, the user-defined context
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_GetItemContext (Uint32 name, Uint32 item, Uint32 * context)
{
	assert(context != 0);

	if (!Listbox_IsItemValid(name, item, SDL_FALSE)) return 0;

	*context = Listbox::Get(name).mItems[item]->mContext;

	return 1;
}

/// @brief Selects or unselects a given listbox item
/// @param name Name used to reference the listbox
/// @param item Index of item in the listbox
/// @param bSelect If true, select the item; otherwise unselect it
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_SelectItem (Uint32 name, Uint32 item, SDL_bool bSelect)
{
	if (!Listbox_IsItemValid(name, item, SDL_FALSE)) return 0;

	Listbox::Get(name).mItems[item]->mSelected = bSelect != SDL_FALSE;

	return 1;
}

/// @brief Selects or unselects a range of listbox items
/// @param name Name used to reference the listbox
/// @param start Index of initial listbox item in range
/// @param numItems [in-out] Count of items to select or unselect; on success, the count of
///					items actually selected or unselected
/// @param bSelect If true, select the items; otherwise unselect them
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_SelectItemRange (Uint32 name, Uint32 start, Uint32 * numItems, SDL_bool bSelect)
{
	assert(numItems != 0);

	if (!Listbox_IsItemValid(name, start, SDL_TRUE)) return 0;

	Listbox & listbox = Listbox::Get(name);

	///////////////////////////////////////////////////////////////////////////////////
	// If the requested count will extend beyond the item vector, we bound it. We then
	// iterate over the range, selecting or unselecting all its items. 
	///////////////////////////////////////////////////////////////////////////////////
	*numItems = listbox.TrimToSize(start, *numItems);

	Uint32 end = start + *numItems;

	for (Uint32 index = start; index < end; ++index)
	{
		listbox.mItems[index]->mSelected = bSelect != SDL_FALSE;
	}

	return 1;
}

/// @brief Adds an item to the listbox at a given spot
/// @param name Name used to reference the listbox
/// @param where Spot at which to add item; this can be equal to the listbox size, in which
///				 case the item is appended
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_AddItem (Uint32 name, Uint32 where)
{
	if (!Listbox_IsItemValid(name, where, SDL_TRUE)) return 0;

	Listbox & listbox = Listbox::Get(name);

	///////////////////////////////////////////////////////////////////////////////////////
	// We can insert an item at any spot within the item vector, or append (where = size).
	// We need only construct a new item and put it into the listbox's item vector.
	///////////////////////////////////////////////////////////////////////////////////////
	try {
		Listbox::Item * pItem = new Listbox::Item();

		listbox.mItems.insert(listbox.mItems.begin() + where, pItem);
	} catch (std::bad_alloc &) { return 0; }

	/////////////////////////////////////////////////////////////////////////////////////
	// If the offset follows the point of insertion, we need to move it ahead one place.
	// We must do similar upkeep in the cases where an item after the point of insertion
	// is held or contains the cursor.
	/////////////////////////////////////////////////////////////////////////////////////
	if (where < listbox.mOffset) ++listbox.mOffset;

	if (listbox.mHeldItem != Listbox::eNoItem)
	{
		if (where < listbox.mHeldItem) ++listbox.mHeldItem;
	}

	if (listbox.mInItem != Listbox::eNoItem)
	{
		if (where < listbox.mInItem) ++listbox.mInItem;
	}

	return 1;
}

/// @brief Remove an item from the listbox
/// @param name Name used to reference the listbox
/// @param item Index of item in the listbox
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_RemoveItem (Uint32 name, Uint32 item)
{
	if (!Listbox_IsItemValid(name, item, SDL_FALSE)) return 0;

	Listbox & listbox = Listbox::Get(name);

	//////////////////////////////////////////////////////////////////////////////////
	// We invoke the item's destructor, and remove it from the listbox's item vector.
	//////////////////////////////////////////////////////////////////////////////////
	delete listbox.mItems[item];

	listbox.mItems.erase(listbox.mItems.begin() + item);

	/////////////////////////////////////////////////////////////////////////////////////
	// If the offset follows the point of removal, we need to move it back one place. We
	// must do similar upkeep in the cases where an item after the point of removal is
	// held or contains the cursor. If one of these items is at the point of removal, we
	// nullify the item.
	/////////////////////////////////////////////////////////////////////////////////////
	if (listbox.mOffset > item) --listbox.mOffset;

	if (listbox.mHeldItem != Listbox::eNoItem)
	{
		if (listbox.mHeldItem > item) --listbox.mHeldItem;

		else if (listbox.mHeldItem == item) listbox.mHeldItem = Listbox::eNoItem;
	}

	if (listbox.mInItem != Listbox::eNoItem)
	{
		if (listbox.mInItem > item) --listbox.mInItem;

		else if (listbox.mInItem == item) listbox.mInItem = Listbox::eNoItem;
	}

	return 1;
}

/// @brief Removes all items in a range from the listbox
/// @param name Name used to reference the listbox
/// @param start Index of initial listbox item in range
/// @param numItems [in-out] Count of items to remove; on success, the count of items
///					actually removed
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_RemoveItemRange (Uint32 name, Uint32 start, Uint32 * numItems)
{
	assert(numItems != 0);

	if (!Listbox_IsItemValid(name, start, SDL_TRUE)) return 0;

	Listbox & listbox = Listbox::Get(name);

	///////////////////////////////////////////////////////////////////////////////////
	// If the requested count will extend beyond the item vector, we bound it. We then
	// remove all items within this range.
	///////////////////////////////////////////////////////////////////////////////////
	*numItems = listbox.TrimToSize(start, *numItems);

	listbox.mItems.erase(listbox.mItems.begin() + start, listbox.mItems.begin() + start + *numItems);

	//////////////////////////////////////////////////////////////////////////////////////
	// If the offset follows the point of removal, we need to move it back. We reduce the
	// offset by the lesser of the count of items removed and the distance from the point
	// of removal to the offset.
	//////////////////////////////////////////////////////////////////////////////////////
	if (listbox.mOffset > start)
	{
		Uint32 adjust = listbox.mOffset - start;

		if (*numItems < adjust) adjust = *numItems;

		listbox.mOffset -= adjust;
	}

	////////////////////////////////////////////////////////////////////////////////
	// We must also do some upkeep if an item after the point of removal is held or
	// contains the cursor. If the item is after the interval we are removing, we
	// slide it back by the number of items to remove. Otherwise, it lies within
	// the interval, and we nullify the item.
	////////////////////////////////////////////////////////////////////////////////
	if (listbox.mHeldItem != Listbox::eNoItem)
	{
		if (listbox.mHeldItem >= start + *numItems) listbox.mHeldItem -= *numItems;

		else if (listbox.mHeldItem >= start) listbox.mHeldItem = Listbox::eNoItem;
	}

	if (listbox.mInItem != Listbox::eNoItem)
	{
		if (listbox.mInItem >= start + *numItems) listbox.mInItem -= *numItems;

		else if (listbox.mInItem >= start) listbox.mInItem = Listbox::eNoItem;
	}

	return 1;
}

/// @brief Allows or disallows clicking of a listbox's items
/// @param name Name used to reference the listbox
/// @param bAllow If true, we allow clicks
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_AllowItemClick (Uint32 name, SDL_bool bAllow)
{
	if (!Listbox_IsValid(name)) return 0;

	Listbox & listbox = Listbox::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// We clear or set the clickable flag as called for. If we are disallowing clicks, we
	// nullify any held items.
	//////////////////////////////////////////////////////////////////////////////////////
    if (bAllow)
	{
		listbox.mStatus[Listbox::eCannotClickItem] = false;
	}

	else
	{
		listbox.mStatus[Listbox::eCannotClickItem] = true;

		listbox.mHeldItem = Listbox::eNoItem;
	}

	return 1;
}

/// @brief Allows or disallows dragging over a listbox's items
/// @param name Name used to reference the listbox
/// @return 0 on failure, non-0 for success
/// @param bAllow If true, we allow dragging
/// @note Tested
int Listbox_AllowDragOver (Uint32 name, SDL_bool bAllow)
{
	if (!Listbox_IsValid(name)) return 0;

	Listbox::Get(name).mStatus[Listbox::eCannotDragOver] = !bAllow;

	return 1;
}

/// @brief Sets a listbox's fit best item callback
/// @param name Name used to reference the listbox
/// @param fitBestItem Callback used to fit an item, in [0,size)
/// @return 0 on failure, non-0 for success
/// @note Tested
int Listbox_SetFitBestItem (Uint32 name, Uint32 (*fitBestItem)(Uint32, float, float, void *))
{
	if (!Listbox_IsValid(name)) return 0;

	Listbox::Get(name).mFitBestItem = fitBestItem;

	return 1;
}

/// @brief Used to signal that the cursor is over a listbox item
/// @note Function will NOP if not called from a hit test callback during input propagation,
///		  after the listbox itself has been signaled as beneath the cursor
/// @note Tested
void Listbox_SignalCursorOverItem (Uint32 item)
{
	UserInterface & UI = UserInterface::Get();

	if (!Listbox_IsItemValid(UI.mCurrentHit, item, SDL_FALSE)) return;

	Listbox & listbox = Listbox::Get(UI.mCurrentHit);

	if (listbox.mStatus[Widget::eUnder]) listbox.mUnderItem = item;
}

/// @brief Indicates whether a listbox's items may be clicked
/// @param name Name used to reference the listbox
/// @return A boolean indicating whether the listbox's items may be clicked
/// @note Tested
SDL_bool Listbox_IsItemClickAllowed (Uint32 name)
{
	if (!Listbox_IsValid(name)) return SDL_FALSE;
	if (Listbox::Get(name).mStatus[Listbox::eCannotClickItem]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether dragging is allowed over a listbox's items
/// @param name Name used to reference the listbox
/// @return A boolean indicating whether dragging is allowed
/// @note Tested
SDL_bool Listbox_IsDragOverAllowed (Uint32 name)
{
	if (!Listbox_IsValid(name)) return SDL_FALSE;
	if (Listbox::Get(name).mStatus[Listbox::eCannotDragOver]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a listbox item is selected
/// @param name Name used to reference the listbox
/// @param item Index of item in the listbox
/// @return A boolean whether the item is selected
/// @note Tested
SDL_bool Listbox_IsItemSelected (Uint32 name, Uint32 item)
{
	if (!Listbox_IsItemValid(name, item, SDL_FALSE)) return SDL_FALSE;
	if (!Listbox::Get(name).mItems[item]->mSelected) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether an item is found in the listbox
/// @param name Name used to reference the listbox
/// @param item Index of item in the listbox
/// @param bAddSpot If true, the spot after the items is considered valid
/// @return A boolean indicating item validity
/// @note Tested
SDL_bool Listbox_IsItemValid (Uint32 name, Uint32 item, SDL_bool bAddSpot)
{
	if (!Listbox_IsValid(name)) return SDL_FALSE;

	///////////////////////////////////////////////////////////////////////////////////////
	// An item is valid if it falls in the range of its listbox's item vector. In the case
	// of add spots, we extend the range by one to allow for spots at the end.
	///////////////////////////////////////////////////////////////////////////////////////
	Uint32 range = static_cast<Uint32>(Listbox::Get(name).mItems.size());

	if (bAddSpot) ++range;

	if (item >= range) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid listbox
/// @param name Name used to reference the listbox
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Listbox_IsValid (Uint32 name)
{
	///////////////////////////////////////////////////////////////////////////////////////
	// A listbox is valid if it is first a valid pane item and also is typed as a listbox.
	///////////////////////////////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::eListbox) return SDL_FALSE;

	return SDL_TRUE;
}