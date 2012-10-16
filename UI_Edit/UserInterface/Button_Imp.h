#ifndef USER_INTERFACE_BUTTON_IMP_H
#define USER_INTERFACE_BUTTON_IMP_H

#include "PaneItem_Imp.h"

/// @brief Structure used to represent a button widget
struct Button : PaneItem {
// Enumerations
	enum {
		eCannotPush = ePaneItemNext,/// The button cannot be pushed
		ePushed	///< The button is pushed
	};
// Methods
	Button (void);
	~Button (void);

	static Button & Get (Uint32 name);

	void Push (float fCursorX, float fCursorY, void * pContext);
	void Release (void * pContext);
	void Clear (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_BUTTON_IMP_H
