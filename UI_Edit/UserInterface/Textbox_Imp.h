#ifndef USER_INTERFACE_TEXTBOX_IMP_H
#define USER_INTERFACE_TEXTBOX_IMP_H

#include "PaneItem_Imp.h"

/// @brief Structure used to represent a textbox widget
struct Textbox : PaneItem {
// Members
	std::basic_string<wchar_t> mString;	///< Text string used by textbox
	Uint32 (*mFitBestSpot)(Uint32, float, float, void *);	///< Returns the spot index that best fits the cursor coordinates
	Uint32 mMaxLength;	///< Length of longest permissible text string
	Uint32 mNumSelect;	///< Count of selected items
	Uint32 mOffset;	///< Current text offset
	Uint32 mCursor;	///< Current cursor position
	Uint32 mSelect;	///< Current index of selection
	Uint32 mUnderSpot;	///< Spot currently beneath cursor
	Uint32 mHeldSpot;	///< Currenly held spot
	Uint32 mRangeEnd;	///< Spot at end of drag range
// Enumerations
	enum {
		eNoSpot = 0xFFFFFFFF	///< Reserved for null spot
	};
	enum {
		eCannotClickSpot = ePaneItemNext,	///< We cannot click on spots in the textbox
		eCannotDragOver	///< We cannot drag over the text
	};
// Methods
	Textbox (void);
	~Textbox (void);

	static Textbox & Get (Uint32 name);

	Uint32 TrimToSize (Uint32 start, Uint32 count);
	Uint32 TrimToMax (Uint32 start, Uint32 count);
	Uint32 GetSpot (float fCursorX, float fCursorY, void * pContext);

	void GrabSpot (void * pContext);
	void DropSpot (void * pContext);
	void DragOver (Uint32 over, void * pContext);
	void AdjustForInsert (Uint32 where, Uint32 count);
	void Clear (void);
	void CleanTemps (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_TEXTBOX_IMP_H
