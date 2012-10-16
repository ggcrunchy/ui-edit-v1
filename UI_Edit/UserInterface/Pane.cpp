/// @file
/// Interface for pane widgets

#include "Pane_Imp.h"
#include "PaneItem_Imp.h"
#include "PaneLayer_Imp.h"
#include "UserInterface_Imp.h"
#include "Pane.h"
#include "PaneItem.h"
#include "UserInterface.h"
#include "Widget.h"
#include <cassert>

/// @brief Instantiates a pane
/// @param name [out] On success, the name used to reference the pane
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_Create (Uint32 * name)
{
	assert(name != 0);

	if (!UserInterface_WasInit()) return 0;

	return UserInterface::Get().CreateWidget(Widget::ePane, name);
}

/// @brief Adds an item to a given region of a pane; coordinates and dimensions are clamped
///		   so x, y, x + w, y + h lie in [0,1]
/// @param name Name used to reference the pane
/// @param item Name used to reference the pane item
/// @param fX Relative x coordinate, in [0,1]
/// @param fY Relative y coordinate, in [0,1]
/// @param fW Relative width, in [0,1]
/// @param fH Relative height, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_AddItem (Uint32 name, Uint32 item, float fX, float fY, float fW, float fH)
{
	if (!Pane_IsValid(name)) return 0;
	if (!PaneItem_IsValid(item)) return 0;
	if (fX >= 1.0f || fW <= 0.0f) return 0;
	if (fY >= 1.0f || fH <= 0.0f) return 0;

	PaneItem & rItem = PaneItem::Get(item);

	////////////////////////////////////////////////////////////////////////////////////
	// If the item is already loaded into the pane, we can ignore this step. Otherwise,
	// we first remove the item from the pane it is currently in, if it is loaded. We
	// then add its name to the pane's list of item names, and give the item back an
	// iterator so that it may later be easily removed from the pane. Finally, we give
	// the item the pane name as reference.
	///////////////////////////////////////////////////////////////////////////////////
	if (rItem.mPane != name)
	{
		PaneItem_RemoveFromPane(item);

		Pane & pane = Pane::Get(name);

		pane.mItems.push_front(item);

		rItem.mIter = pane.mItems.begin();
		rItem.mPane = name;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// We first ensure that the coordinates and dimensions will confine the item to the
	// pane. We then set the item's pane-relative coordinates and dimensions.
	////////////////////////////////////////////////////////////////////////////////////
	if (fX < 0.0f) fX = 0.0f;
	if (fX + fW > 1.0f) fW = 1.0f - fX;
	if (fY < 0.0f) fY = 0.0f;
	if (fY + fH > 1.0f) fH = 1.0f - fY;

	rItem.mX = fX;
	rItem.mY = fY;
	rItem.mW = fW;
	rItem.mH = fH;

	return 1;
}

/// @brief Removes a pane from its layer, if loaded
/// @param name Name used to reference the pane
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_RemoveFromLayer (Uint32 name)
{
	if (!Pane_IsValid(name)) return 0;

	Pane & pane = Pane::Get(name);

	//////////////////////////////////////////////////////////////////////////////
	// We remove the pane's name from the layer's name list and nullify its layer 
	// reference. If the pane is not loaded, this is a NOP.
	//////////////////////////////////////////////////////////////////////////////
	if (pane.mLayer != Pane::eNoLayer)
	{
		PaneLayer::Get(pane.mLayer).mPanes.erase(pane.mIter);

		pane.mLayer = Pane::eNoLayer;
	}

	return 1;
}

/// @brief Gets the pane layer into which a pane is loaded
/// @param name Name used to reference the pane
/// @param layer [out] On success, the pane's layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetLayer (Uint32 name, Uint32 * layer)
{
	assert(layer != 0);

	if (!Pane_IsLoaded(name)) return 0;

	*layer = Pane::Get(name).mLayer;

	return 1;
}

/// @brief Gets the count of items loaded into a pane
/// @param name Name used to reference the pane
/// @param count [out] On success, the count of loaded items
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetItemCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!Pane_IsValid(name)) return 0;

	*count = static_cast<Uint32>(Pane::Get(name).mItems.size());

	return 1;
}

/// @brief Removes an item from the focus chain at a given slot
/// @param name Name used to reference the pane
/// @param slot Slot at which to remove the item
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_RemoveFocusChainItem (Uint32 name, Uint32 slot)
{
	if (!Pane_IsFocusChainSlotValid(name, slot)) return 0;

	Pane & pane = Pane::Get(name);

	//////////////////////////////////////////////////////////////////////////////////
	// If we are removing the focus, we need to switch the focus to an adjacent item,
	// depending on what behavior was requested. If the focus slot is after the point
	// of removal, we decrement the focus slot.
	//////////////////////////////////////////////////////////////////////////////////
	if (slot == pane.mFocusSlot)
	{
		if (pane.mStatus[Pane::eBackOnDelete]) Pane_GetFocusPriorSlot(name, &pane.mFocusSlot);

		else Pane_GetFocusNextSlot(name, &pane.mFocusSlot);
	}

	if (pane.mFocusSlot > slot) --pane.mFocusSlot;

	////////////////////////////////////////////////////////////////////////
	// We nullify the entry's slot reference, and remove it from the chain.
	////////////////////////////////////////////////////////////////////////
	PaneItem::Get(pane.mChain[slot]).mSlot = PaneItem::eNoSlot;

	pane.mChain.erase(pane.mChain.begin() + slot);

	/////////////////////////////////////////////////////////////////////////////////////
	// To maintain consistency, we iterate through all entries from the point of removal
	// onward, reassigning their slots to account for the change.
	/////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 index = slot; index < pane.mChain.size(); ++index)
	{
		PaneItem::Get(pane.mChain[index]).mSlot = index;
	}

	return 1;
}

/// @brief Empties out a pane's focus chain
/// @param name Name used to reference the pane
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_ClearFocusChain (Uint32 name)
{
	if (!Pane_IsValid(name)) return 0;

	Pane & pane = Pane::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// For each entry in the chain, we nullify the slot reference. Once that is done, we
	// empty the chain to maintain consistency.
	/////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 index = 0; index < pane.mChain.size(); ++index)
	{
		PaneItem::Get(pane.mChain[index]).mSlot = PaneItem::eNoSlot;
	}

	pane.mChain.clear();
	
	return 1;
}

/// @brief Loads a pane's focus chain, removing any current contents; focus chain items are
///		   arranged in the order they appear in the array, with the first item as focus
/// @param name Name used to reference the pane
/// @param items An array of unique item names
/// @param count The count of item names to load
/// @param bBackOnFocusDelete If true, set the focus to the prior item if the focus is
///							  removed from the chain; otherwise, use the next item
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_LoadFocusChain (Uint32 name, Uint32 const * items, Uint32 count, SDL_bool bBackOnFocusDelete)
{
	assert(items != 0);

	if (!Pane_IsValid(name)) return 0;

	Pane & pane = Pane::Get(name);

	///////////////////////////////////////////////////////////////////////////////////
	// To maintain consistency, we must clear out any loaded items. We then resize the
	// pane's chain to accomodate the new items, and load them iteratively.
	///////////////////////////////////////////////////////////////////////////////////
	Pane_ClearFocusChain(name);

	pane.mChain.resize(count, 0);

	for (Uint32 index = 0; index < count; ++index)
	{
		Uint32 item = items[index];

		///////////////////////////////////////////////////////////////////////////////
		// Invalid and duplicate entries in the item set are errors, as are items from
		// other panes. We clean up by nullifying the loaded slots' references, and
		// emptying the chain.
		///////////////////////////////////////////////////////////////////////////////
		if (!PaneItem_IsLoaded(item) || PaneItem::Get(item).mSlot != PaneItem::eNoSlot || PaneItem::Get(item).mPane != name)
		{
			for (Uint32 entry = 0; entry < index; ++entry)
			{
				PaneItem::Get(items[entry]).mSlot = PaneItem::eNoSlot;
			}

			pane.mChain.clear();

			return 0;
		}

		///////////////////////////////////////////////////////////////////////////////////
		// If the entry is valid, we load it into the chain, and set its slot's reference.
		///////////////////////////////////////////////////////////////////////////////////
		pane.mChain[index] = item;

		PaneItem::Get(item).mSlot = index;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Finally, indicate the pane's focus deletion behavior, and set the initial focus.
	////////////////////////////////////////////////////////////////////////////////////
	pane.mStatus[Pane::eBackOnDelete] = bBackOnFocusDelete != SDL_FALSE;

	pane.mFocusSlot = 0;

	return 1;
}

/// @brief Swaps the contents of two loaded focus chain slots
/// @param name Name used to reference the pane
/// @param one Slot used to reference the first item
/// @param two Slot used to reference the second item
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_SwapFocusChainItems (Uint32 name, Uint32 one, Uint32 two)
{
	if (!Pane_IsValid(name)) return 0;

	Pane & pane = Pane::Get(name);

	if (one >= pane.mChain.size()) return 0;
	if (two >= pane.mChain.size()) return 0;

	/////////////////////////////////////////////////////////////////////////////////////
	// To swap items, we swap the entries in the chain. To maintain consistency, we must
	// also swap the corresponding slots' references.
	/////////////////////////////////////////////////////////////////////////////////////
	Uint32 entry1 = pane.mChain[one];
	Uint32 entry2 = pane.mChain[two];
	
	pane.mChain[one] = entry2;
	pane.mChain[two] = entry1;

	PaneItem::Get(entry1).mSlot = two;
	PaneItem::Get(entry2).mSlot = one;

	return 1;
}

/// @brief Gets the name of the item loaded in a focus chain slot
/// @param name Name used to reference the pane
/// @param slot The slot holding the item
/// @param item [out] On success, the name used to reference the item
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetFocusChainItem (Uint32 name, Uint32 slot, Uint32 * item)
{
	assert(item != 0);

	if (!Pane_IsFocusChainSlotValid(name, slot)) return 0;

	*item = Pane::Get(name).mChain[slot];

	return 1;
}

/// @brief Gets the size of the pane's focus chain
/// @param name Name used to reference the pane
/// @param count [out] On success, the number of layers loaded into the focus chain
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetFocusChainItemCount (Uint32 name, Uint32 * count)
{
	assert(count != 0);

	if (!Pane_IsValid(name)) return 0;

	*count = static_cast<Uint32>(Pane::Get(name).mChain.size());

	return 1;
}

/// @brief Sets the slot of a pane's focus
/// @param name Name used to reference the pane
/// @param slot The slot of the focus
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_SetFocusSlot (Uint32 name, Uint32 slot)
{
	if (!Pane_IsFocusChainSlotValid(name, slot)) return 0;

	Pane::Get(name).mFocusSlot = slot;

	return 1;
}

/// @brief Gets the slot of a pane's focus
/// @param name Name used to reference the pane
/// @param slot [out] On success, the slot of the focus
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetFocusSlot (Uint32 name, Uint32 * slot)
{
	assert(slot != 0);

	if (!Pane_IsFocusChainSlotValid(name, 0)) return 0;

	*slot = Pane::Get(name).mFocusSlot;

	return 1;
}

/// @brief Gets the slot of the item in the focus chain prior to the focus
/// @param name Name used to reference the pane
/// @param slot [out] On success, the prior slot
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetFocusPriorSlot (Uint32 name, Uint32 * slot)
{
	if (!Pane_IsFocusChainSlotValid(name, 0)) return 0;

	Pane & pane = Pane::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// If the focus is at the front of the chain, we start after the back; otherwise, we 
	// use the focus slot. The prior slot is one less than this index.
	/////////////////////////////////////////////////////////////////////////////////////
	Uint32 index = 0 == pane.mFocusSlot ? static_cast<Uint32>(pane.mChain.size()) : pane.mFocusSlot;

	*slot = index - 1;

	return 1;
}

/// @brief Gets the slot of the item in the focus chain next after the focus
/// @param name Name used to reference the pane
/// @param slot [out] On success, the next slot
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_GetFocusNextSlot (Uint32 name, Uint32 * slot)
{
	if (!Pane_IsFocusChainSlotValid(name, 0)) return 0;

	Pane & pane = Pane::Get(name);

	////////////////////////////////////////////////////////////////////////////////////
	// If the focus is at the back of the chain, the next slot is the front. Otherwise,
	// it is the slot one more than the focus slot.
	////////////////////////////////////////////////////////////////////////////////////
	Uint32 index = pane.mFocusSlot + 1;

	*slot = index == static_cast<Uint32>(pane.mChain.size()) ? 0 : index;

	return 1;
}

/// @brief Allows or disallows dragging of a pane
/// @param name Name used to reference the pane
/// @param bAllow If true, we allow dragging
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_AllowDrag (Uint32 name, SDL_bool bAllow)
{
	if (!Pane_IsValid(name)) return 0;

	Pane::Get(name).mStatus[Pane::eCannotDrag] = !bAllow;

	return 1;
}

/// @brief Sets a pane's fit best coordinates callback
/// @param name Name used to reference the pane
/// @param fitBestXY Callback used to fit a pair of coordinates
/// @return 0 on failure, non-0 for success
/// @note Tested
int Pane_SetFitBestXY (Uint32 name, void (*fitBestXY)(Uint32, float, float, void *, float *, float *))
{
	if (!Pane_IsValid(name)) return 0;

	Pane::Get(name).mFitBestXY = fitBestXY;

	return 1;
}

/// @brief Indicates whether a pane is caught
/// @param name Name used to reference the pane
/// @return A boolean indicating whether the pane is caught
/// @note Tested
SDL_bool Pane_IsCaught (Uint32 name)
{
	if (!Pane_IsValid(name)) return SDL_FALSE;
	if (!Pane::Get(name).mStatus[Pane::eCaught]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a pane can be dragged
/// @param name Name used to reference the pane
/// @return A boolean indicating whether the pane can be dragged
/// @note Tested
SDL_bool Pane_IsDragAllowed (Uint32 name)
{
	if (!Pane_IsValid(name)) return SDL_FALSE;
	if (Pane::Get(name).mStatus[Pane::eCannotDrag]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a slot in the pane's focus chain is valid
/// @param name Name used to reference the pane
/// @param slot Index of focus chain slot
/// @return A boolean indicating slot validity
/// @note Tested
SDL_bool Pane_IsFocusChainSlotValid (Uint32 name, Uint32 slot)
{
	if (!Pane_IsValid(name)) return SDL_FALSE;
	if (slot >= Pane::Get(name).mChain.size()) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a pane is loaded into a pane layer
/// @param name Name used to reference the pane
/// @return A boolean indicating whether the pane is loaded
/// @note Tested
SDL_bool Pane_IsLoaded (Uint32 name)
{
	////////////////////////////////////////////////////////
	// A pane is loaded if its layer reference is not null.
	////////////////////////////////////////////////////////
	if (!Pane_IsValid(name)) return SDL_FALSE;
	if (Pane::eNoLayer == Pane::Get(name).mLayer) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid pane
/// @param name Name used to reference the pane
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Pane_IsValid (Uint32 name)
{
	//////////////////////////////////////////////////////////////////////////////
	// A pane is valid if it is first a valid widget and also is typed as a pane.
	//////////////////////////////////////////////////////////////////////////////
	if (!Widget_IsValid(name)) return SDL_FALSE;
	if (Widget::Get(name).mType != Widget::ePane) return SDL_FALSE;

	return SDL_TRUE;
}