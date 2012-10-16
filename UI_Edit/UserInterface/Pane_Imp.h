#ifndef USER_INTERFACE_PANE_IMP_H
#define USER_INTERFACE_PANE_IMP_H

#include "Widget_Imp.h"
#include <list>
#include <vector>

/// @brief Widget type which can be loaded into layers, and can have item widgets loaded
struct Pane : Widget {
// Members
	std::list<Uint32> mItems;	///< Items loaded into the pane
	std::list<Uint32>::iterator mIter;	///< Iterator in layer corresponding to pane
	std::vector<Uint32> mChain;	///< Range of focus item indices
	void (*mFitBestXY)(Uint32, float, float, void *, float *, float *);	///< Returns the pane coordinates that best fit the cursor coordinates
	Uint32 mLayer;	///< Layer to which pane is bound
	Uint32 mFocusSlot;	///< Current slot used by the focus
// Enumerations
	enum {
		eNoLayer = 0xFFFFFFFF	///< Name reserved for null layer
	};
	enum {
		eCannotDrag = eWidgetNext,	///< The pane cannot be dragged
		eCaught,///< The pane is caught
		eBackOnDelete	///< If the focus is deleted, migrate to the prior item; otherwise, use the next item
	};
// Methods
	Pane (void);
	~Pane (void);

	static Pane & Get (Uint32 name);

	void GetXY (float fCursorX, float fCursorY, void * pContext, float & fX, float & fY);

	void Catch (float fCursorX, float fCursorY, void * pContext);
	void Release (void * pContext);
	void Drag (float fDX, float fDY, void * pContext);
	void Clear (void);
	void Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext);
	bool Update (float fCursorX, float fCursorY, bool bPressed, void * pContext);
};

#endif // USER_INTERFACE_PANE_IMP_H
