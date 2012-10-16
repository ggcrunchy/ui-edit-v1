/// @file
/// Interface for UI management

#include "Pane_Imp.h"
#include "PaneItem_Imp.h"
#include "PaneLayer_Imp.h"
#include "UserInterface_Imp.h"
#include "PaneItem.h"
#include "PaneLayer.h"
#include "UserInterface.h"
#include "Widget.h"
#include <iostream>
#include <cassert>

/// @brief Prepares the user interface manager for use
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_InitSystem (void)
{
	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////
	// Flush any information present in the system.
	////////////////////////////////////////////////
	if (UI.mStatus[UserInterface::eInitialized]) UserInterface_QuitSystem();

	////////////////////////////////////////////////////////////////////////////////////
	// Initially, there will be no widget of choice. Also, we nullify the currently hit
	// widget, as this is only valid during an input propagation.
	////////////////////////////////////////////////////////////////////////////////////
	UI.mChoice = UserInterface::eNullWidget;
	UI.mCurrentHit = UserInterface::eNullWidget;

	/////////////////////////////////////////////////////////////
	// Indicate that the user interface system is ready for use.
	/////////////////////////////////////////////////////////////
	UI.mStatus[UserInterface::eInitialized] = true;

	return 1;
}

/// @brief Propagates cursor input through the user interface layers, and responds to it;
///		   widgets are not hit tested and/or receive no events if hit test and process
///		   event handlers have not been installed for their type
/// @param fCursorX Cursor x coordinate, in [0,1]
/// @param fCursorY Cursor y coordinate, in [0,1]
/// @param bPressed If true, the cursor is pressed
/// @param pContext [in-out] User-defined context parameter; argument to hit test and
///							 process event handlers
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_PropagateInput (float fCursorX, float fCursorY, SDL_bool bPressed, void * pContext)
{
	if (!UserInterface_WasInit()) return 0;
	if (fCursorX < 0.0f || fCursorX > 1.0f) return 0;
	if (fCursorY < 0.0f || fCursorY > 1.0f) return 0;

	UserInterface & UI = UserInterface::Get();

	assert(UserInterface::eNullWidget == UI.mCurrentHit);
	assert(UserInterface::eBasicEvent == UI.mEventType);

	/////////////////////////////////////////////////////////////////////////////////////
	// We scan until we find the first widget hit. We then resolve the hit, dealing with
	// the previously hit widget and the new hit as needed.
	/////////////////////////////////////////////////////////////////////////////////////
	UI.CheckForHits(fCursorX, fCursorY, pContext);

	UI.ResolveHits(fCursorX, fCursorY, bPressed != SDL_FALSE, pContext);

	return 1;
}

/// @brief Clears the user interface manager's input state
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_ClearInput (void)
{
	UserInterface & UI = UserInterface::Get();

	//////////////////////////////////////////////////////////////////////////////////////
	// If there is a widget of choice, we invoke its clear method to restore it to a pure
	// state, and nullify the manager's choice.
	//////////////////////////////////////////////////////////////////////////////////////
	if (UI.mChoice != UserInterface::eNullWidget)
	{
		assert(UserInterface_WasInit());

		UI.mWidgets[UI.mChoice]->Clear();

		UI.mChoice = UserInterface::eNullWidget;
	}

	//////////////////////////////////
	// Clear the cursor press record.
	//////////////////////////////////
	UI.mStatus[UserInterface::ePressed] = false;

	return 1;
}

/// @brief Draws the user interface; this proceeds from the last pane layer to the first
///		   (back to front); each non-hidden pane loaded into a layer is drawn, along with
///		   all non-hidden items loaded into said pane; widgets are not drawn if no draw
///		   handler has been installed for their type
/// @param pContext [in-out] User-defined context parameter; argument to draw handlers
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_Draw (void * pContext)
{
	if (!UserInterface_WasInit()) return 0;

	UserInterface & UI = UserInterface::Get();

	//////////////////////////////////////////////////////////////////////////////////////
	// We run through the frame backward, and iterate through the pane list on each slot.
	// If a pane draw handler exists, we draw each pane.
	//////////////////////////////////////////////////////////////////////////////////////
	for (std::vector<Uint32>::reverse_iterator layerIter = UI.mFrame.rbegin(); layerIter != UI.mFrame.rend(); ++layerIter)
	{
		std::list<Uint32> & panes = UI.mLayers[*layerIter]->mPanes;

		for (std::list<Uint32>::iterator paneIter = panes.begin(); paneIter != panes.end(); ++paneIter)
		{
			Pane & pane = Pane::Get(*paneIter);

			if (pane.mDraw != 0) pane.mDraw(*paneIter, pContext);

			//////////////////////////////////////////////////////////////////////////////
			// We iterate through the list of pane items loaded into the current pane. If
			// a draw handler is installed for an item's type, we draw it.
			//////////////////////////////////////////////////////////////////////////////
			std::list<Uint32> & items = Pane::Get(*paneIter).mItems;

			for (std::list<Uint32>::iterator itemIter = items.begin(); itemIter != items.end(); ++itemIter)
			{
				PaneItem & item = PaneItem::Get(*itemIter);

				if (item.mDraw != 0) item.mDraw(*itemIter, pContext);
			}
		}
	}

	return 1;
}

/// @brief Removes a pane layer loaded at a given slot
/// @param slot The slot holding the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_RemoveFrameLayer (Uint32 slot)
{
	if (!UserInterface_IsFrameSlotValid(slot)) return 0;

	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////////////////////////////
	// We nullify the entry's slot reference, and remove it from the frame.
	////////////////////////////////////////////////////////////////////////
    UI.mLayers[UI.mFrame[slot]]->mSlot = PaneLayer::eNoSlot;

	assert(UserInterface_WasInit());

	UI.mFrame.erase(UI.mFrame.begin() + slot);

	/////////////////////////////////////////////////////////////////////////////////////
	// To maintain consistency, we iterate through all entries from the point of removal
	// onward, reassigning their slots to account for the change.
	/////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 index = slot; index < UI.mFrame.size(); ++index)
	{
		UI.mLayers[UI.mFrame[index]]->mSlot = index;
	}

	return 1;
}

/// @brief Empties out the user interface manager's loaded pane layers
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_ClearFrameLayers (void)
{
	if (!UserInterface_WasInit()) return 0;

	UserInterface & UI = UserInterface::Get();

	/////////////////////////////////////////////////////////////////////////////////////
	// For each entry in the frame, we nullify the slot reference. Once that is done, we
	// empty the frame to maintain consistency.
	/////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 index = 0; index < UI.mFrame.size(); ++index)
	{
		UI.mLayers[UI.mFrame[index]]->mSlot = PaneLayer::eNoSlot;
	}

	UI.mFrame.clear();

	return 1;
}

/// @brief Loads the user interface manager's pane layers, removing any current contents
/// @param layers An array of unique layer names
/// @param count The count of layer names to load
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_LoadFrameLayers (Uint32 const * layers, Uint32 count)
{
	assert(layers != 0);

	if (!UserInterface_WasInit()) return 0;

	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////////////////////////////////////////
	// To maintain consistency, we must clear out any loaded layers. We then resize the
	// frame to accomodate the new layers, and load them iteratively.
	////////////////////////////////////////////////////////////////////////////////////
	UserInterface_ClearFrameLayers();

	UI.mFrame.resize(count, 0);

	for (Uint32 index = 0; index < count; ++index)
	{
		Uint32 name = layers[index];

		/////////////////////////////////////////////////////////////////////////////
		// Invalid and duplicate entries in the layer set are errors. We clean up by
		// nullifying the loaded slots' references, and emptying the frame.
		/////////////////////////////////////////////////////////////////////////////
		if (!PaneLayer_IsValid(name) || UI.mLayers[name]->mSlot != PaneLayer::eNoSlot)
		{
			for (Uint32 entry = 0; entry < index; ++entry)
			{
				UI.mLayers[layers[entry]]->mSlot = PaneLayer::eNoSlot;
			}

			UI.mFrame.clear();

			return 0;
		}

		///////////////////////////////////////////////////////////////////////////////////
		// If the entry is valid, we load it into the frame, and set its slot's reference.
		///////////////////////////////////////////////////////////////////////////////////
		UI.mFrame[index] = name;

		UI.mLayers[name]->mSlot = index;
	}

	return 1;
}

/// @brief Swaps the contents of two loaded pane layer slots
/// @param one Slot used to reference the first layer
/// @param two Slot used to reference the second layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_SwapFrameLayers (Uint32 one, Uint32 two)
{
	UserInterface & UI = UserInterface::Get();

	if (one >= UI.mFrame.size()) return 0;
	if (two >= UI.mFrame.size()) return 0;

	assert(UserInterface_WasInit());

	//////////////////////////////////////////////////////////////////////////////////////
	// To swap layers, we swap the entries in the frame. To maintain consistency, we must
	// also swap the corresponding slots' references.
	//////////////////////////////////////////////////////////////////////////////////////
	Uint32 entry1 = UI.mFrame[one];
	Uint32 entry2 = UI.mFrame[two];

	UI.mFrame[one] = entry2;
	UI.mFrame[two] = entry1;

	UI.mLayers[entry1]->mSlot = two;
	UI.mLayers[entry2]->mSlot = one;

	return 1;
}

/// @brief Gets the name of the pane layer loaded in a slot
/// @param slot The slot holding the layer
/// @param layer [out] On success, the name used to reference the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_GetFrameLayer (Uint32 slot, Uint32 * layer)
{
	assert(layer != 0);

	if (!UserInterface_IsFrameSlotValid(slot)) return 0;

	*layer = UserInterface::Get().mFrame[slot];

	return 1;
}

/// @brief Gets the size of the pane layer frame
/// @param size [out] On success, the number of layers loaded into the frame
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_GetFrameSize (Uint32 * size)
{
	assert(size != 0);

	if (!UserInterface_WasInit()) return 0;

	*size = static_cast<Uint32>(UserInterface::Get().mFrame.size());

	return 1;
}

/// @brief Acquires the name of a pane layer, given its tag
/// @param tag The Unicode tag used to look up the layer
/// @param layer [out] On success, the name used to reference the layer
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_FindLayer (wchar_t const * tag, Uint32 * layer)
{
	assert(tag != 0);
	assert(layer != 0);

	std::map<std::basic_string<wchar_t>, Uint32>::iterator tagIter = UserInterface::Get().mLayerTags.find(tag);

	if (tagIter == UserInterface::Get().mLayerTags.end()) return 0;

	assert(UserInterface_WasInit());

	*layer = tagIter->second;

	return 1;
}

/// @brief Acquires the name of a widget, given its tag
/// @param tag The Unicode tag used to look up the widget
/// @param widget [out] On success, the name used to reference the widget
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_FindWidget (wchar_t const * tag, Uint32 * widget)
{
	assert(tag != 0);
	assert(widget != 0);

	std::map<std::basic_string<wchar_t>, Uint32>::iterator tagIter = UserInterface::Get().mWidgetTags.find(tag);
	
	if (tagIter == UserInterface::Get().mWidgetTags.end()) return 0;

	assert(UserInterface_WasInit());

	*widget = tagIter->second;

	return 1;
}

/// @brief Gets the widget of choice
/// @param widget [out] On success, the name used to reference the widget of choice
/// @return 0 on failure, non-0 for success
/// @note Tested
int UserInterface_GetChoice (Uint32 * widget)
{
	assert(widget != 0);

	if (UserInterface::eNullWidget == UserInterface::Get().mChoice) return 0;

	assert(UserInterface_WasInit());

	*widget = UserInterface::Get().mChoice;

	return 1;
}

/// @brief Gets the index data for the current event
/// @param index [out] On success, the index datum
/// @return 0 on failure, non-0 for success
/// @note Function will fail if not called from a process event handler during an index event
/// @note Tested
int UserInterface_GetEventIndex (Uint32 * index)
{
	assert(index != 0);

	UserInterface & UI = UserInterface::Get();

	if (UI.mEventType != UserInterface::eIndexEvent) return 0;

	*index = UI.mEvent.mIndex;

	return 1;
}

/// @brief Gets the range data for the current event
/// @param start [out] On success, the range datum's start value
/// @param count [out] On success, the range datum's count value
/// @return 0 on failure, non-0 for success
/// @note Function will fail if not called from a process event handler during a range event
/// @note Tested
int UserInterface_GetEventRange (Uint32 * start, Uint32 * count)
{
	assert(start != 0);
	assert(count != 0);

	UserInterface & UI = UserInterface::Get();

	if (UI.mEventType != UserInterface::eRangeEvent) return 0;

	*start = UI.mEvent.mRange.mStart;
	*count = UI.mEvent.mRange.mCount;

	return 1;
}

/// @brief Gets the point data for the current event
/// @param fX [out] On success, the point datum's x coordinate, in [0,1]
/// @param fY [out] On success, the point datum's y coordinate, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Function will fail if not called from a process event handler during a point event
/// @note Tested
int UserInterface_GetEventPoint (float * fX, float * fY)
{
	assert(fX != 0);
	assert(fY != 0);

	UserInterface & UI = UserInterface::Get();

	if (UI.mEventType != UserInterface::ePointEvent) return 0;

	*fX = UI.mEvent.mPoint.mX;
	*fY = UI.mEvent.mPoint.mY;

	return 1;
}

/// @brief Shuts down the user interface manager, restoring it to its original state; also,
///		   performs garbage collection on all widgets, pane layers, and tags
/// @note Tested
void UserInterface_QuitSystem (void)
{
	UserInterface & UI = UserInterface::Get();

	/////////////////////////////////////////////////////////////////////////////////////
	// We want to clean up any widgets that have not been disposed of. We also clear the
	// input state in the process.
	/////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 widget = 0; widget < UI.mWidgets.size(); ++widget)
	{
		if (UI.mWidgets[widget] != 0) Widget_Destroy(widget);
	}

	assert(UserInterface::eNullWidget == UI.mChoice);

	////////////////////////////////////////////////////////////////////////////////////
	// We want to clean up any layers that have not been disposed of. We also clear the 
	// frame in the process.
	////////////////////////////////////////////////////////////////////////////////////
	for (Uint32 layer = 0; layer < UI.mLayers.size(); ++layer)
	{
		if (UI.mLayers[layer] != 0) PaneLayer_Destroy(layer);
	}

	assert(UI.mFrame.empty());

	//////////////////////////////////////////////////////////////////////////////
	// We need to restore the UI manager to a state from which it may be properly
	// reinitialized. Thus, we empty out its vectors, lists, and maps.
	//////////////////////////////////////////////////////////////////////////////
	UI.mWidgets.clear();
	UI.mFreeWidgets.clear();
	UI.mWidgetTags.clear();
	UI.mLayers.clear();
	UI.mFreeLayers.clear();
	UI.mLayerTags.clear();

	/////////////////////////////////////////////////////
	// Prevent use of the system without initialization.
	/////////////////////////////////////////////////////
	UI.mStatus[UserInterface::eInitialized] = false;
}

/// @brief Indicates whether a slot in the frame is valid
/// @param slot Index of frame slot
/// @return A boolean indicating slot validity
/// @note Tested
SDL_bool UserInterface_IsFrameSlotValid (Uint32 slot)
{
	if (slot >= UserInterface::Get().mFrame.size()) return SDL_FALSE;

	assert(UserInterface_WasInit());

	return SDL_TRUE;
}

/// @brief Indicates whether the user interface manager was initialized
/// @return A boolean indicating whether initialization occurred
/// @note Tested
SDL_bool UserInterface_WasInit (void)
{
	if (!UserInterface::Get().mStatus[UserInterface::eInitialized]) return SDL_FALSE;

	return SDL_TRUE;
}