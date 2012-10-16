#include "Slider_Imp.h"
#include "UserInterface_Imp.h"
#include "WidgetEvent.h"
#include <cassert>

/// @brief Constructs a Slider object
/// @note Tested
Slider::Slider (void) : PaneItem(eSlider), mFitBestOffset(0), mOffset(0.0f)
{
}

/// @brief Destructs a Slider object
/// @note Tested
Slider::~Slider (void)
{
}

/// @brief Acquires a Slider object
/// @param name Name used to reference the slider
/// @return Reference to the Slider object
/// @note Tested
Slider & Slider::Get (Uint32 name)
{
	return static_cast<Slider&>(Widget::Get(name));
}

/// @brief Gets a slider's best fit offset in [0,1]
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
float Slider::GetOffset (float fCursorX, float fCursorY, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// We start with the current offset. If there is no fit best offset handler, we just
	// settle for this. Otherwise, we call the handler, and clamp to [0,1] if needed. 
	/////////////////////////////////////////////////////////////////////////////////////
	float fOffset = mOffset;

	if (mFitBestOffset != 0)
	{
		fOffset = mFitBestOffset(UserInterface::Get().mChoice, fCursorX, fCursorY, pContext);

		if (fOffset < 0.0f) fOffset = 0.0f;
		if (fOffset > 1.0f) fOffset = 1.0f;
	}

	return fOffset;
}

/// @brief Grabs the slider thumb and issues a grab thumb event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::GrabThumb (void * pContext)
{
	//////////////////////////////
	// We flag the thumb as held.
	//////////////////////////////
	mStatus[eThumbHeld] = true;

	//////////////////////////////////////
	// We now issue the thumb grab event.
	//////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_GrabThumb, pContext);
}

/// @brief Drops the slider thumb and issues a thumb drop event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::DropThumb (void * pContext)
{
	//////////////////////////////////
	// We flag the thumb as not held.
	//////////////////////////////////
	mStatus[eThumbHeld] = false;

	//////////////////////////////////////
	// We now issue the thumb drop event.
	//////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_DropThumb, pContext);
}

/// @brief Enters the slider thumb and issues an thumb enter event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::EnterThumb (void * pContext)
{
	/////////////////////////////////
	// We flag the thumb as entered.
	/////////////////////////////////
	mStatus[eThumbIn] = true;

	///////////////////////////////////////
	// We now issue the thumb enter event.
	///////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_EnterThumb, pContext);
}

/// @brief Leaves the slider thumb and issues a thumb leave event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::LeaveThumb (void * pContext)
{
	/////////////////////////////////////
	// We flag the thumb as not entered.
	/////////////////////////////////////
	mStatus[eThumbIn] = false;

	///////////////////////////////////////
	// We now issue the thumb leave event.
	///////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_LeaveThumb, pContext);
}

/// @brief Snaps the slider thumb to an offset and issues a thumb snap event
/// @param fOffset Offset to snap thumb to, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::SnapThumb (float fOffset, void * pContext)
{
	///////////////////////
	// We snap the offset.
	///////////////////////
	mOffset = fOffset;

	//////////////////////////////////////
	// We now issue the thumb snap event.
	//////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_SnapThumb, pContext);
}

/// @brief Catches the slider thumb and issues a thumb catch event
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::CatchThumb (float fCursorX, float fCursorY, void * pContext)
{
	////////////////////////////////
	// We flag the thumb as caught.
	////////////////////////////////
	mStatus[eThumbCaught] = true;

	///////////////////////////////////////
	// We now issue the catch thumb event.
	///////////////////////////////////////
	UserInterface::Get().IssuePointEvent(eSliderEvent_CatchThumb, fCursorX, fCursorY, pContext);
}

/// @brief Releases the slider thumb and emits a thumb release event
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::ReleaseThumb (void * pContext)
{
	/////////////////////////////////////
	// We flag the thumb as not caught.
	/////////////////////////////////////
	mStatus[eThumbCaught] = false;

	/////////////////////////////////////////
	// We now issue the release thumb event.
	/////////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_ReleaseThumb, pContext);
}

/// @brief Drags the slider thumb to an offset and issues a thumb drag event
/// @param fOffset Offset to drag the thumb to, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::DragThumb (float fOffset, void * pContext)
{
	//////////////////////////
	// We drag to the offset.
	//////////////////////////
	mOffset = fOffset;

	//////////////////////////////////////
	// We now issue the drag thumb event.
	//////////////////////////////////////
	UserInterface::Get().IssueBasicEvent(eSliderEvent_DragThumb, pContext);
}

/// @brief Clears all important input state
/// @note Tested
void Slider::Clear (void)
{
	Widget::Clear();

	mStatus[eThumbCaught] = false;
	mStatus[eThumbHeld] = false;
	mStatus[eThumbIn] = false;
}

/// @brief Cleans all temporary input state
/// @note Tested
void Slider::CleanTemps (void)
{
	Widget::CleanTemps();

	mStatus[eThumbUnder] = false;
}

/// @brief Handles situation where the slider becomes the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void Slider::Choose (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	assert(mStatus[eUnder]);
	assert(!mStatus[eIn]);
	assert(!mStatus[eHeld]);
	assert(!mStatus[eThumbIn]);
	assert(!mStatus[eThumbHeld]);
	assert(!mStatus[eThumbCaught]);

	//////////////////////////////////////////////////////////////////////////////////////
	// We enter the slider. If the thumb is under the cursor, we enter the thumb. We then
	// check for presses.
	//////////////////////////////////////////////////////////////////////////////////////
	Enter(pContext);

	if (mStatus[eThumbUnder]) EnterThumb(pContext);

	if (bPressed) 
	{
		///////////////////////////////////////////////////////////////////////////////
		// If the thumb was under the cursor during a press, we grab the thumb; if the
		// thumb is draggable, we catch the thumb.
		///////////////////////////////////////////////////////////////////////////////
		if (mStatus[eThumbUnder])
		{
			GrabThumb(pContext);

			if (!mStatus[eThumbCannotDrag]) CatchThumb(fCursorX, fCursorY, pContext);
		}

		///////////////////////////////////////////////////////////////////////////////////
		// Otherwise, we grab the slider. If the slider is snappable, we check what offset
		// the cursor coordinates fit. If this offset varies from the current offset, we
		// adjust it and emit a snap thumb event.
		///////////////////////////////////////////////////////////////////////////////////
		else
		{
			Grab(pContext);

			if (!mStatus[eThumbCannotSnap])
			{
				float fOffset = GetOffset(fCursorX, fCursorY, pContext);

				if (mOffset - fOffset != 0.0f) SnapThumb(fOffset, pContext);
			}
		}
	}
}

/// @brief Updates the slider when it is the widget of choice
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @return A boolean indicating whether the slider is no longer the widget of choice
/// @note Tested
bool Slider::Update (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////
	// If the cursor is over the slider, we check three conditions: First, we check
	// whether the cursor has just entered the slider; if so, we enter the slider. 
	// Second, we check whether the cursor just entered the thumb; if so, we enter
	// the thumb. Third, we check whether the slider and its thumb are not yet held,
	// and if there was a press.
	/////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eUnder])
	{
		if (!mStatus[eIn]) Enter(pContext);
		if (!mStatus[eThumbIn] && mStatus[eThumbUnder]) EnterThumb(pContext);

		if (bPressed && !(mStatus[eHeld] || mStatus[eThumbHeld]))
		{
			///////////////////////////////////////////////////////////////////////
			// If the cursor is over the thumb, we grab the thumb; if the thumb is
			// draggable, we also catch the thumb.
			///////////////////////////////////////////////////////////////////////
			if (mStatus[eThumbUnder])
			{
				GrabThumb(pContext);

				if (!mStatus[eThumbCannotDrag]) CatchThumb(fCursorX, fCursorY, pContext);
			}

			////////////////////////////////////////////////////////////////////////////////
			// Otherwise, we grab the slider. If the slider is snappable, we fit the cursor
			// coordinates to an offset. If the offset varies from the current offset, we
			// snap the thumb to it.
			////////////////////////////////////////////////////////////////////////////////
			else
			{
				Grab(pContext);

				if (!mStatus[eThumbCannotSnap])
				{
					float fOffset = GetOffset(fCursorX, fCursorY, pContext);

					if (mOffset - fOffset != 0.0f) SnapThumb(fOffset, pContext);                    
				}
			}
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// If the cursor is not over the thumb, but was during the last propagation, then we
	// leave the thumb. Likewise, we leave the slider if its confinement changes.
	////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[eThumbUnder] && mStatus[eThumbIn]) LeaveThumb(pContext);
	if (!mStatus[eUnder] && mStatus[eIn]) Leave(pContext);

	////////////////////////////////////////////////////////////////////////////////////
	// If there is no press, we check whether the thumb or slider is held. In the first
	// case, we release the thumb if it is caught, and drop the thumb; in the second, 
	// we drop the slider.
	////////////////////////////////////////////////////////////////////////////////////
	if (!bPressed)
	{
		assert(!(mStatus[eHeld] && mStatus[eThumbHeld]));

		if (mStatus[eThumbHeld])
		{
			if (mStatus[eThumbCaught]) ReleaseThumb(pContext);

			DropThumb(pContext);
		}

		else if (mStatus[eHeld]) Drop(pContext);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// If the thumb is caught, we check for movement. If there is any, we drag the thumb.
	//////////////////////////////////////////////////////////////////////////////////////
	if (mStatus[eThumbCaught])
	{
		float fOffset = GetOffset(fCursorX, fCursorY, pContext);

		if (mOffset - fOffset != 0.0f) DragThumb(fOffset, pContext);
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// Finally, if the cursor is not over the slider and neither the slider nor the thumb
	// is held, the slider is no longer the widget of choice.
	//////////////////////////////////////////////////////////////////////////////////////
	return !mStatus[eUnder] && !(mStatus[eHeld] || mStatus[eThumbHeld]);
}