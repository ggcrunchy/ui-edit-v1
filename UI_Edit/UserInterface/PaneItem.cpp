/// @file
/// Interface for pane items

#include "Pane_Imp.h"
#include "PaneItem_Imp.h"
#include "UserInterface_Imp.h"
#include "PaneItem.h"
#include "Pane.h"
#include "Widget.h"
#include <cassert>

/// @brief Removes a pane item from its pane, if loaded
/// @param name Name used to reference the item
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneItem_RemoveFromPane (Uint32 name)
{
	if (!PaneItem_IsValid(name)) return 0;

	PaneItem & item = PaneItem::Get(name);

	///////////////////////////////////////////////////////////////////////////////////
	// If the item is part of the pane's focus chain, we remove it. We then remove the 
	// item's name from the pane's name list and nullify its pane reference. If the 
	// item is not loaded, this is a NOP.
	///////////////////////////////////////////////////////////////////////////////////
	if (item.mPane != PaneItem::eNoPane)
	{
		if (item.mSlot != PaneItem::eNoSlot) Pane_RemoveFocusChainItem(item.mPane, item.mSlot);

		Pane::Get(item.mPane).mItems.erase(item.mIter);

		item.mPane = PaneItem::eNoPane;
	}

	return 1;
}

/// @brief Gets the pane into which a pane item is loaded
/// @param name Name used to reference the item
/// @param pane [out] On success, the item's pane
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneItem_GetPane (Uint32 name, Uint32 * pane)
{
	assert(pane != 0);

	if (!PaneItem_IsLoaded(name)) return 0;

	*pane = PaneItem::Get(name).mPane;

	return 1;
}

/// @brief Gets the pane item's focus chain slot
/// @param name Name used to reference the item
/// @param slot [out] On success, the slot
/// @return 0 on failure, non-0 for success
/// @note Tested
int PaneItem_GetFocusChainSlot (Uint32 name, Uint32 * slot)
{
	assert(slot != 0);

	if (!PaneItem_IsFocusChainItem(name)) return 0;

	*slot = PaneItem::Get(name).mSlot;

	return 1;
}

/// @brief Indicates whether a pane item is part of a pane's focus chain
/// @param name Name used to reference the item
/// @return A boolean indicating whether the item is in a focus chain
/// @note Tested
SDL_bool PaneItem_IsFocusChainItem (Uint32 name)
{
	if (!PaneItem_IsLoaded(name)) return SDL_FALSE;
	if (PaneItem::eNoSlot == PaneItem::Get(name).mSlot) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a pane item is loaded into a pane
/// @param name Name used to reference the item
/// @return A boolean indicating whether the item is loaded
/// @note Tested
SDL_bool PaneItem_IsLoaded (Uint32 name)
{
	////////////////////////////////////////////////////////////
	// A pane item is loaded if its pane reference is not null.
	////////////////////////////////////////////////////////////
	if (!PaneItem_IsValid(name)) return SDL_FALSE;
	if (PaneItem::eNoPane == PaneItem::Get(name).mPane) return SDL_FALSE;

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid pane item
/// @param name Name used to reference the item
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool PaneItem_IsValid (Uint32 name)
{
	///////////////////////////////////////////////////////////////////////////////////////
	// A pane item is valid if it is first a valid widget and also is not typed as a pane.
	///////////////////////////////////////////////////////////////////////////////////////
	if (!Widget_IsValid(name)) return SDL_FALSE;
	if (Widget::ePane == Widget::Get(name).mType) return SDL_FALSE;

	assert(Widget::Get(name).mType < Widget::eNumTypes);

	return SDL_TRUE;
}