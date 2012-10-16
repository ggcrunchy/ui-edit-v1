#include "Pane_Imp.h"
#include "PaneItem_Imp.h"
#include "UserInterface_Imp.h"
#include "Pane.h"

/// @brief Constructs a PaneItem object
/// @note Tested
PaneItem::PaneItem (WidgetType type) : Widget(type), mPane(eNoPane), mSlot(eNoSlot)
{
}

/// @brief Destructs a PaneItem object
/// @note Tested
PaneItem::~PaneItem (void)
{
	///////////////////////////////////////////////////////////////////////////////////
	// If the item is part of the pane's focus chain, we remove it. We then remove the 
	// item from the pane itself. If the item is not loaded, this is a NOP.
	///////////////////////////////////////////////////////////////////////////////////
	if (mPane != eNoPane)
	{
		if (mSlot != eNoSlot) Pane_RemoveFocusChainItem(mPane, mSlot);

		Pane::Get(mPane).mItems.erase(mIter);
	}
}

/// @brief Acquires a PaneItem object
/// @param name Name used to reference the item
/// @return Reference to the PaneItem object
/// @note Tested
PaneItem & PaneItem::Get (Uint32 name)
{
	return static_cast<PaneItem&>(Widget::Get(name));
}