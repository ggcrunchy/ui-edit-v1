/// @file
/// Implementation for UI management

#include "Button_Imp.h"
#include "Checkbox_Imp.h"
#include "Listbox_Imp.h"
#include "Pane_Imp.h"
#include "PaneItem_Imp.h"
#include "PaneLayer_Imp.h"
#include "Radiobox_Imp.h"
#include "Slider_Imp.h"
#include "Textbox_Imp.h"
#include "UserInterface_Imp.h"
#include "Widget_Imp.h"
#include "WidgetEvent.h"
#include <cassert>

/// @var G_UserInterface
/// @brief User interface manager singleton
UserInterface G_UserInterface;

/// @brief Constructs the user interface manager
/// @note Tested
UserInterface::UserInterface (void) : mEventType(eBasicEvent)
{
}

/// @brief Destructs the user interface manager
/// @note Tested
UserInterface::~UserInterface (void)
{
}

/// @brief Accesses the user interface manager singleton
/// @return Reference to the user interface manager singleton
/// @note Tested
UserInterface & UserInterface::Get (void)
{
	return G_UserInterface;
}

/// @brief Gets the index of a free slot in the user interface manager's layer vector,
///		   adding more space if needed
/// @return Index of free layer slot
/// @note Tested
Uint32 UserInterface::GetFreeLayerSlot (void)
{
	//////////////////////////////////////////////////////////////////////////////////////
	// If there are no entries in the free layer list, we add a null entry to the back of
	// the layer vector and return the index of the back entry.
	//////////////////////////////////////////////////////////////////////////////////////
	if (mFreeLayers.empty())
	{
		mLayers.push_back(0);

		return static_cast<Uint32>(mLayers.size() - 1);
	}

	////////////////////////////////////////////////////////////////////////////////
	// If the free layer list is not empty, we pull off and return its front index.
	////////////////////////////////////////////////////////////////////////////////
	Uint32 slot = mFreeLayers.front();

	mFreeLayers.pop_front();

	return slot;
}

/// @brief Gets the index of a free slot in the user interface manager's widget vector,
///		   adding more space if needed
/// @return Index of free widget slot
Uint32 UserInterface::GetFreeWidgetSlot (void)
{
	///////////////////////////////////////////////////////////////////////////////////////
	// If there are no entries in the free widget list, we add a null entry to the back of
	// the widget vector and return the index of the back entry.
	///////////////////////////////////////////////////////////////////////////////////////
	if (mFreeWidgets.empty())
	{
		mWidgets.push_back(0);

		return static_cast<Uint32>(mWidgets.size() - 1);
	}

	/////////////////////////////////////////////////////////////////////////////////
	// If the free widget list is not empty, we pull off and return its front index.
	/////////////////////////////////////////////////////////////////////////////////
	Uint32 slot = mFreeWidgets.front();

	mFreeWidgets.pop_front();

	return slot;	
}

/// @brief Constructs a widget of a given type
/// @param type Type of the widget to create
/// @param name [out] On success, the name used to reference the widget
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface::CreateWidget (Widget::WidgetType type, Uint32 * name)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// We first get a free slot in the widget vector. We branch on the type, construct a
	// widget of the appropriate type, and assign the slot as the name.
	/////////////////////////////////////////////////////////////////////////////////////
	try {
		Uint32 slot = GetFreeWidgetSlot();

		switch (type)
		{
		case Widget::ePane:
			mWidgets[slot] = new Pane();
			break;
		case Widget::eButton:
			mWidgets[slot] = new Button();
			break;
		case Widget::eSlider:
			mWidgets[slot] = new Slider();
			break;
		case Widget::eListbox:
			mWidgets[slot] = new Listbox();
			break;
		case Widget::eTextbox:
			mWidgets[slot] = new Textbox();
			break;
		case Widget::eCheckbox:
			mWidgets[slot] = new Checkbox();
			break;
		case Widget::eRadiobox:
			mWidgets[slot] = new Radiobox();
			break;
		}

		*name = slot;
	} catch (std::out_of_range &) { return 0; }

	return 1;
}

/// @brief Finds the top widget that is beneath the cursor (if multiple widgets overlap one
///		   another--i.e. two or more panes on the same layer or two or more items on the
///		   same pane--and more than one is hit, the first hit is chosen)
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::CheckForHits (float fCursorX, float fCursorY, void * pContext)
{
	////////////////////////////////////////////////////////////////////////////////////////
	// We iterate through the frame front to back, and run through the panes in each layer.
	////////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 layer = 0; layer < mFrame.size(); ++layer)
	{
		std::list<Uint32> & panes = mLayers[mFrame[layer]]->mPanes;

		for (std::list<Uint32>::iterator paneIter = panes.begin(); paneIter != panes.end(); ++paneIter)
		{
			Pane & pane = Pane::Get(*paneIter);

			std::list<Uint32> & items = pane.mItems;

			/////////////////////////////////////////////////////////////////////////
			// We first iterate through the items on a pane. If there is no hit test
			// handler installed for an item's type, we skip it. Otherwise, we set
			// the item as the current hit and do a hit test. If the item is flagged
			// as under the cursor, we have our hit and quit; otherwise we continue.
			/////////////////////////////////////////////////////////////////////////
			for (std::list<Uint32>::iterator itemIter = items.begin(); itemIter != items.end(); ++itemIter)
			{
				PaneItem & item = PaneItem::Get(*itemIter);

				if (0 == item.mHitTest) continue;

				mCurrentHit = *itemIter;

				item.mHitTest(*itemIter, fCursorX, fCursorY, pContext);

				if (item.mStatus[Widget::eUnder]) return;
			}

			////////////////////////////////////////////////////////////////////////////
			// If we did not hit any of the items, we test the pane. If there is no hit
			// test handler installed for panes, we skip it. Otherwise, we set the pane
			// as the current hit and do a hit test. If the pane is flagged as under
			// the cursor, we have our hit and quit; otherwise we continue.
			////////////////////////////////////////////////////////////////////////////
			if (0 == pane.mHitTest) continue;

			mCurrentHit = *paneIter;

			pane.mHitTest(*paneIter, fCursorX, fCursorY, pContext);

			if (pane.mStatus[Widget::eUnder]) return;
		}
	}

	//////////////////////////////////////////////////////////////////////
	// If we did not get any hits, then nullify the current hit and quit.
	//////////////////////////////////////////////////////////////////////
	mCurrentHit = eNullWidget;
}

/// @brief Updates the widget of choice, if applicable, and chooses a new widget if called
///		   for; also, updates input state
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::ResolveHits (float fCursorX, float fCursorY, bool bPressed, void * pContext)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// The cursor may have been pressed while not over any widget. If this was the case,
	// and the cursor is still pressed, there is no meaningful way to interact with the
	// interface, and we ignore that step.
	/////////////////////////////////////////////////////////////////////////////////////
	if (!mStatus[ePressed] || mChoice != eNullWidget)
	{
		///////////////////////////////////////////////////////////////////////////////////
		// If there is a widget of choice, we want to update it with the new cursor state.
		// We then clean up any temporary data it was using. If necessary, we indicate
		// that the widget is no longer the widget of choice.
		///////////////////////////////////////////////////////////////////////////////////
		if (mChoice != eNullWidget)
		{
			bool bNotChoice = mWidgets[mChoice]->Update(fCursorX, fCursorY, bPressed, pContext);

			mWidgets[mChoice]->CleanTemps();

			if (bNotChoice) mChoice = eNullWidget;
		}

		/////////////////////////////////////////////////////////////////////////////////
		// If there is a valid current hit, but no widget of choice, we make the hit the 
		// new widget of choice, taking measures appropriate for its type. We then clean
		// up any temporary data is was using.
		/////////////////////////////////////////////////////////////////////////////////
		if (mCurrentHit != eNullWidget)
		{
			if (eNullWidget == mChoice)
			{
				mChoice = mCurrentHit;

				mWidgets[mChoice]->Choose(fCursorX, fCursorY, bPressed, pContext);
			}

			mWidgets[mChoice]->CleanTemps();
		}
	}

	///////////////////////////////////////////////////////////////////////////////////////
	// The current hit is intermediate data. It should be clear when we run the next input
	// propagation, so we nullify it now. We store the cursor press state, so that we can
	// compare against it on the next propagation.
	///////////////////////////////////////////////////////////////////////////////////////
	mCurrentHit = eNullWidget;

	mStatus[ePressed] = bPressed;
}

/// @brief Issues an event without attached data to the widget of choice
/// @param type Type of event to issue
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::IssueBasicEvent (WidgetEventType type, void * pContext)
{
	void (*processEvent)(Uint32, WidgetEventType, void *) = Widget::Get(mChoice).mProcessEvent;

	if (processEvent != 0) processEvent(mChoice, type, pContext);
}

/// @brief Issues an event with index-type data to the widget of choice
/// @param type Type of event to issue
/// @param index Index datum
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::IssueIndexEvent (WidgetEventType type, Uint32 index, void * pContext)
{
	void (*processEvent)(Uint32, WidgetEventType, void *) = Widget::Get(mChoice).mProcessEvent;

	if (processEvent != 0)
	{
		UserInterface & UI = UserInterface::Get();

		UI.mEventType = UserInterface::eIndexEvent;
		UI.mEvent.mIndex = index;

		processEvent(mChoice, type, pContext);

		UI.mEventType = UserInterface::eBasicEvent;
	}
}

/// @brief Issues an event with range-type data to the widget of choice
/// @param type Type of event to issue
/// @param start Start of range
/// @param count Count of items in range
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::IssueRangeEvent (WidgetEventType type, Uint32 start, Uint32 count, void * pContext)
{
	void (*processEvent)(Uint32, WidgetEventType, void *) = Widget::Get(mChoice).mProcessEvent;

	if (processEvent != 0)
	{
		UserInterface & UI = UserInterface::Get();

		UI.mEventType = UserInterface::eRangeEvent;
		UI.mEvent.mRange.mCount = count;
		UI.mEvent.mRange.mStart = start;

		processEvent(mChoice, type, pContext);

		UI.mEventType = UserInterface::eBasicEvent;
	}
}

/// @brief Issues an event with point-type data to the widget of choice
/// @param type Type of event to issue
/// @param fX General x coordinate, in [0,1]
/// @param fY General y coordinate, in [0,1]
/// @param pContext [in-out] User-defined context parameter
/// @note Tested
void UserInterface::IssuePointEvent (WidgetEventType type, float fX, float fY, void * pContext)
{
	void (*processEvent)(Uint32, WidgetEventType, void *) = Widget::Get(mChoice).mProcessEvent;

	if (processEvent != 0)
	{
		UserInterface & UI = UserInterface::Get();

		UI.mEventType = UserInterface::ePointEvent;
		UI.mEvent.mPoint.mX = fX;
		UI.mEvent.mPoint.mY = fY;

		processEvent(mChoice, type, pContext);

		UI.mEventType = UserInterface::eBasicEvent;
	}
}