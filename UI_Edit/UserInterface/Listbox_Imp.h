#ifndef USER_INTERFACE_LISTBOX_IMP_H
#define USER_INTERFACE_LISTBOX_IMP_H

#include "PaneItem_Imp.h"
#include <vector>

/// @brief Structure used to represent a listbox widget
struct Listbox : PaneItem {
// Types
	/// @brief Structure used to represent a listbox item
	struct Item {
	// Members
		Uint32 mContext;///< Item-specific, user-provided data
		bool mSelected;	///< If true, the item is selected
	// Methods
		Item (void);
		~Item (void);
	};
// Members
	std::vector<Item*> mItems;	///< Range of items loaded into the listbox
	Uint32 (*mFitBestItem)(Uint32, float, float, void *);	///< Returns the item index that best fits the cursor coordinates
	Uint32 mCapacity;	///< Number of items listbox can display
	Uint32 mOffset;	///< Current list offset
	Uint32 mUnderItem;	///< Item currently beneath cursor
	Uint32 mHeldItem;	///< Currenly held item
	Uint32 mInItem;	///< Item currently containing cursor
	Uint32 mRangeEnd;	///< Item at end of drag range
// Enumerations
	enum {
		eNoItem = 0xFFFFFFFF	///< Index reserved for null item
	};
	enum {
		eCannotClickItem = ePaneItemNext,	///< We cannot click on items in the listbox
		eCannotDragOver,///< We cannot drag over the items
	};
// Methods
	Listbox (void);
	~Listbox (void);

	static Listbox & Get (Uint32 name);

	Uint32 TrimToSize (Uint32 start, Uint32 count);
	Uint32 GetItem (float fCursorX, float fCursorY, void * pContext);

	void GrabItem (void * pContext);
	void DropItem (void * pContext);
	void EnterItem (void * pContext);
	void LeaveItem (void * pContext);
	void DragOver (Uint32 over, void * pContext);
	void Clear (void);
	void CleanTemps (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_LISTBOX_IMP_H
