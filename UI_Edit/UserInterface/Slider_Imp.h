#ifndef USER_INTERFACE_SLIDER_IMP_H
#define USER_INTERFACE_SLIDER_IMP_H

#include "PaneItem_Imp.h"

/// @brief Structure used to represent a slider widget
struct Slider : PaneItem {
// Members
	float (*mFitBestOffset)(Uint32, float, float, void *);	///< Returns the offset that best fits the cursor coordinates
	float mOffset;	///< Current value of offset, in [0,1]
// Enumerations
	enum {
		eThumbCannotSnap = ePaneItemNext,	///< The thumb cannot be snapped
		eThumbCannotDrag,	///< The thumb cannot be dragged
		eThumbCaught,	///< The thumb is caught
		eThumbUnder,///< The thumb is beneath the cursor
		eThumbHeld,	///< The thumb is held by the cursor
		eThumbIn	///< The widget was beneath the thumb on the previous input propagation
	};
// Methods
	Slider (void);
	~Slider (void);

	static Slider & Get (Uint32 name);

	float GetOffset (float fCursorX, float fCursorY, void * pContext);

	void GrabThumb (void * pContext);
	void DropThumb (void * pContext);
	void EnterThumb (void * pContext);
	void LeaveThumb (void * pContext);
	void SnapThumb (float fOffset, void * pContext);
	void CatchThumb (float fCursorX, float fCursorY, void * pContext);
	void ReleaseThumb (void * pContext);
	void DragThumb (float fOffset, void * pContext);
	void Clear (void);
	void CleanTemps (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_SLIDER_IMP_H
