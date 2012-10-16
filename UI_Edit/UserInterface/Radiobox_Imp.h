#ifndef USER_INTERFACE_RADIOBOX_IMP_H
#define USER_INTERFACE_RADIOBOX_IMP_H

#include "PaneItem_Imp.h"

/// @brief Structure used to represent a radiobox widget
struct Radiobox : PaneItem {
// Members
	Uint32 mNumOptions;	///< Count of radiobox options
	Uint32 mChoice;	///< The current option
	Uint32 mUnderOption;///< Choice currently beneath option
	Uint32 mHeldOption;	///< Currently held option
	Uint32 mInOption;	///< Option currently containing cursor
// Enumerations
	enum {
		eNoOption = 0xFFFFFFFF	/// Index reserved for null options
	};
	enum {
		eCannotClick = ePaneItemNext	/// The options cannot be clicked
	};
// Methods
	Radiobox (void);
	~Radiobox (void);

	static Radiobox & Get (Uint32 name);

	void GrabOption (void * pContext);
	void DropOption (void * pContext);
	void EnterOption (void * pContext);
	void LeaveOption (void * pContext);
	void Clear (void);
	void CleanTemps (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_RADIOBOX_IMP_H
