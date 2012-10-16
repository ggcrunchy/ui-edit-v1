#ifndef USER_INTERFACE_CHECKBOX_IMP_H
#define USER_INTERFACE_CHECKBOX_IMP_H

#include "PaneItem_Imp.h"

/// @brief Structure used to represent a checkbox widget
struct Checkbox : PaneItem {
// Enumerations
	enum {
		eCannotClick = ePaneItemNext,	/// The checkbox cannot be clicked
		eClicked,	///< The checkbox is clicked
		eChecked	///< The checkbox is checked
	};
// Methods
	Checkbox (void);
	~Checkbox (void);

	static Checkbox & Get (Uint32 name);

	void Toggle (void * pContext);
	void Clear (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_CHECKBOX_IMP_H
