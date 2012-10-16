#ifndef USER_INTERFACE_PANE_ITEM_IMP_H
#define USER_INTERFACE_PANE_ITEM_IMP_H

#include "Widget_Imp.h"
#include <list>

/// @brief Widget type which can be loaded into panes
struct PaneItem : Widget {
// Members
	std::list<Uint32>::iterator mIter;	///< Iterator in pane list corresponding to item
	Uint32 mPane;	///< Pane to which item is bound
	Uint32 mSlot;	///< Slot pane item is occupying
// Enumerations
	enum {
		eNoPane = 0xFFFFFFFF,	///< Name reserved for null pane
		eNoSlot = 0xFFFFFFFF	///< Index reserved for null slot
	};
	enum {
		ePaneItemNext = eWidgetNext	///< Used to continue the bits in derived types
	};
// Methods
	PaneItem (WidgetType type);
	~PaneItem (void);

	static PaneItem & Get (Uint32 name);

	virtual void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext) = 0;	///< Implemented by individual pane items
	virtual bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext) = 0;	///< Implemented by individual pane items
};

#endif // USER_INTERFACE_PANE_ITEM_IMP_H
