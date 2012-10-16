/// @file
/// Implementation for pane widgets

#include "Pane_Imp.h"
#include "PaneLayer_Imp.h"
#include "UserInterface_Imp.h"
#include "PaneItem.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Pane object
/// @note Tested
Pane::Pane (void) : Widget(ePane), mLayer(eNoLayer)
{
}

/// @brief Destructs a Pane object
/// @note Tested
Pane::~Pane (void)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// If the pane is loaded into a pane layer, we unload it. We then unload all items in
	// the pane, which will also clear its focus chain.
	//////////////////////////////////////////////////////////////////////////////////////
	if (mLayer != eNoLayer) PaneLayer::Get(mLayer).mPanes.erase(mIter);

	while (!mItems.empty())
	{
		PaneItem_RemoveFromPane(mItems.front());
	}
}

/// @brief Acquires a Pane object
/// @param name Name used to reference the pane
/// @return Reference to the Pane object
/// @note Tested
Pane & Pane::Get (Uint32 name)
{
	return static_cast<Pane&>(Widget::Get(name));
}

/// @brief Gets a pane's best fit coordinates
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @param fX [out] Fitted x coordinate, in [0,1]
/// @param fY [out] Fitted y coordinate, in [0,1]
/// @note Tested
void Pane::GetXY (float fCursorX, float fCursorY, void * pContext, float & fX, float & fY)
{
	//////////////////////////////////////////////////////////////////////////////
	// We start with the current coordinates. If there is no fit best coordinates 
	// handler, we just settle for this. Otherwise, we call the handler, and clip
	// the coordinates as needed. 
	//////////////////////////////////////////////////////////////////////////////
	fX = mX;
	fY = mY;

	if (mFitBestXY != 0)
	{
		mFitBestXY(UserInterface::Get().mChoice, fCursorX, fCursorY, pContext, &fX, &fY);

		if (fX < 0.0f) fX = 0.0f;
		if (fX + mW > 1.0f) fX = 1.0f - mW;
		if (fY < 0.0f) fY = 0.0f;
		if (fY + mH > 1.0f) fY = 1.0f - mH;
	}
}

/// @brief Catches the pane and issues a pane catch event
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Pane::Catch (float fCursorX, float fCursorY, void * pContext)
{
	///////////////////////////////
	// We flag the pane as caught.
	///////////////////////////////
	mStatus[eCaught] = true;

	/////////////////////////////////
	// We now issue the catch event.
	/////////////////////////////////
	UserInterface::Get().IssuePointEvent(ePaneEvent_Catch, fCursorX, fCursorY, pContext);
}

/// @brief Releases the pane and emits a pane release event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Pane::Release (void * pContext)
{
	///////////////////////////////////
	// We flag the pane as not caught.
	///////////////////////////////////
	mStatus[eCaught] = false;

	///////////////////////////////////
	// We now issue the release event.
	///////////////////////////////////
	UserInterface::Get().IssueBasicEvent(ePaneEvent_Release, pContext);
}

/// @brief Drags the pane and emits a pane drag event
/// @param fDX Cursor x-displacement, in [-1,+1]
/// @param fDY Cursor y-displacement, in [-1,+1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Pane::Drag (float fDX, float fDY, void * pContext)
{
	////////////////////////////////////////////////////
	// We accumulate the increments in each coordinate. 
	////////////////////////////////////////////////////
	mX += fDX;
	mY += fDY;

	////////////////////////////////
	// We now issue the drag event.
	////////////////////////////////
	UserInterface::Get().IssueBasicEvent(ePaneEvent_Drag, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Pane::Clear (void)
{
	Widget::Clear();

	mStatus[eCaught] = false;
}

/// @brief Handles situation where the pane becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Pane::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);
	assert(!mStatus[eCaught]);

	//////////////////////////////////////////////////////////////////////////////////////
	// We enter the pane. If there was a press at the same time, we grab the pane; if the
	// pane is draggable, we catch the pane.
	//////////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (bPressed) 
	{
		Grab(pContext);

		if (!mStatus[eCannotDrag]) Catch(fCursorX, fCursorY, pContext);
	}
}

/// @brief Updates the pane when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the pane is no longer the widget of choice
/// @note Tested
bool Pane::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the pane, we check two conditions: First, we check whether 
	// the cursor has just entered the pane; if so, we enter the pane. Second, we check
	// whether the pane is not yet held, and if there was a press--since the cursor is 
	// over the pane, we grab the pane; if the pane is draggable, we also catch the 
	// pane.
	////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);

		if (!mStatus[eHeld] && bPressed) 
		{
			Grab(pContext);

			if (!mStatus[eCannotDrag]) Catch(fCursorX, fCursorY, pContext);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the pane, but was during the last propagation, then we
	// leave the pane.
	////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	//////////////////////////////////////////////////////////////////////////////////
	// We check if the pane is held, but there is no press. If the pane is caught, we
	// release the pane. We then drop the pane.
	//////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eHeld] && !bPressed)
	{
		if (mStatus[eCaught]) Release(pContext);

		Drop(pContext);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// If the pane is caught, we check for movement. If there is any, we drag the pane.
	////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eCaught])
	{
		float fX, fY;	GetXY(fCursorX, fCursorY, pContext, fX, fY);

		float fDX = fX - mX;
		float fDY = fY - mY;

		if (fDX != 0.0f || fDY != 0.0f) Drag(fDX, fDY, pContext);
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the pane and the pane is not held, the pane is
	// no longer the widget of choice.
	/////////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !mStatus[eHeld];
}