/// @file
/// Interface for general widgets

#include "Pane_Imp.h"
#include "PaneItem_Imp.h"
#include "UserInterface_Imp.h"
#include "Widget_Imp.h"
#include "Pane.h"
#include "UserInterface.h"
#include "Widget.h"
#include <iostream>
#include <cassert>

/// @brief Terminates a widget instance
/// @param name Name used to reference the widget
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_Destroy (Uint32 name)
{
	if (!Widget_IsValid(name)) return 0;

	UserInterface & UI = UserInterface::Get();

	////////////////////////////////////////////////////////////////////////////////
	// If this is the widget of choice, we clear the input state, since it would be
	// invalid after destruction.
	////////////////////////////////////////////////////////////////////////////////
	if (name == UI.mChoice) UserInterface_ClearInput();

	/////////////////////////////////////////////////////////////////////////////////
	// We invoke the widget's destructor. The derived-type widget destructor will be
	// called, cleaning up before freeing its own memory. We then add the widget
	// name to the list of free widgets, and nullify the spot to preserve validity.
	/////////////////////////////////////////////////////////////////////////////////
	delete UI.mWidgets[name];

	UI.mFreeWidgets.push_back(name);

	UI.mWidgets[name] = 0;

	return 1;
}

/// @brief Sets the tag of a widget
/// @param name Name used to reference the widget
/// @param tag Unicode tag to associate with widget
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_SetTag (Uint32 name, wchar_t const * tag)
{
	assert(tag != 0);

	if (!Widget_IsValid(name)) return 0;

	UserInterface & UI = UserInterface::Get();

	///////////////////////////////////////////////////////////////////////////////////////
	// We first remove any tag currently associated with the widget. We then check whether
	// the tag itself is in use. If it is, we indicate that the widget associated with it
	// no longer acknowledges it.
	///////////////////////////////////////////////////////////////////////////////////////
	Widget_Untag(name);

	std::map<std::basic_string<wchar_t>, Uint32>::iterator item = UI.mWidgetTags.find(tag);
	
	if (item != UI.mWidgetTags.end())
	{
		assert(UI.mWidgets[item->second] != 0);

		UI.mWidgets[item->second]->mStatus[Widget::eTagged] = false;
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// We now associate the name with the tag. In order to facilitate easy disassociation
	// at a later time, we cache an iterator into the tag map. Finally, we indicate that
	// this widget is tagged.
	//////////////////////////////////////////////////////////////////////////////////////
	UI.mWidgetTags[tag] = name;

	UI.mWidgets[name]->mTagPos = UI.mWidgetTags.find(tag);

	UI.mWidgets[name]->mStatus[Widget::eTagged] = true;

	return 1;
}

/// @brief Gets the tag of a widget
/// @param name Name used to reference the widget
/// @param tag [out] On success, the Unicode tag associated with the widget
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_GetTag (Uint32 name, wchar_t * tag)
{
	assert(tag != 0);

	if (!Widget_IsTagged(name)) return 0;

	std::basic_string<wchar_t> const & rTag = Widget::Get(name).mTagPos->first;

	rTag.copy(tag, rTag.size());

	tag[rTag.size()] = 0;

	return 1;
}

/// @brief Removes the tag, if any, from a widget
/// @param name Name used to reference the widget
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_Untag (Uint32 name)
{
	if (!Widget_IsValid(name)) return 0;

	UserInterface & UI = UserInterface::Get();

	//////////////////////////////////////////////////////////////////////////////////////
	// We remove the tag mapped to the widget, and indicate that it is untagged. If there
	// is no tag, this is a NOP.
	//////////////////////////////////////////////////////////////////////////////////////
	if (UI.mWidgets[name]->mStatus[Widget::eTagged])
	{
		UI.mWidgetTags.erase(UI.mWidgets[name]->mTagPos);

		UI.mWidgets[name]->mStatus[Widget::eTagged] = false;
	}

	return 1;
}

/// @brief Sets the relative coordinates of a loaded widget; coordinates and dimensions are
///		   clamped so x, y, x + w, y + h lie in [0,1]
/// @param name Name used to reference the widget
/// @param fX Relative x coordinate, in [0,1]
/// @param fY Relative y coordinate, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_SetXY (Uint32 name, float fX, float fY)
{
	if (!Widget_IsLoaded(name)) return 0;
	if (fX >= 1.0f) return 0;
	if (fY >= 1.0f) return 0;

	Widget & widget = Widget::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// We ensure that the coordinates will not cause the widget to lie outside the region
	// into which it is loaded. We then assign the coordinates.
	//////////////////////////////////////////////////////////////////////////////////////
	if (fX < 0.0f) fX = 0.0f;
	if (fX + widget.mW > 1.0f) fX = 1.0f - widget.mW;
	if (fY < 0.0f) fY = 0.0f;
	if (fY + widget.mH > 1.0f) fY = 1.0f - widget.mH;

	widget.mX = fX;
	widget.mY = fY;

	return 1;
}

/// @brief Sets the relative dimensions of a loaded widget; dimensions are clamped so that
///		   x + w, y + h lie in [0,1]
/// @param name Name used to reference the widget
/// @param fW Relative width, in [0,1]
/// @param fH Relative height, in [0,1]
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_SetWH (Uint32 name, float fW, float fH)
{
	if (!Widget_IsLoaded(name)) return 0;
	if (fW <= 0.0f) return 0;
	if (fH <= 0.0f) return 0;

	Widget & widget = Widget::Get(name);

	/////////////////////////////////////////////////////////////////////////////////////
	// We ensure that the dimensions will not cause the widget to lie outside the region
	// into which it is loaded. We then assign the dimensions.
	/////////////////////////////////////////////////////////////////////////////////////
	if (widget.mX + fW > 1.0f) fW = 1.0f - widget.mX;
	if (widget.mY + fH > 1.0f) fH = 1.0f - widget.mY;

	widget.mW = fW;
	widget.mH = fH;

	return 1;
}

/// @brief Gets the relative coordinates and dimensions of a loaded widget
/// @param name Name used to reference the widget
/// @param fX [out-optional] On success, relative x coordinate, in [0,1]
/// @param fY [out-optional] On success, relative y coordinate, in [0,1]
/// @param fW [out-optional] On success, relative width, in [0,1]
/// @param fH [out-optional] On success, relative height, in [0,1]
/// @param bGlobal If true, coordinates are global (relevant for pane items)
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_GetXYWH (Uint32 name, float * fX, float * fY, float * fW, float * fH, SDL_bool bGlobal)
{
	if (!Widget_IsLoaded(name)) return 0;

	Widget & widget = Widget::Get(name);

	//////////////////////////////////////////////////////////////////////////////////////
	// If we request global values and our widget is a pane item, we first ensure that it
	// is loaded into a pane. We then scale its coordinates by the pane's dimensions and
	// translate by the pane's coordinates; we scale its dimensions by those of the pane.
	//////////////////////////////////////////////////////////////////////////////////////
	if (widget.mType != Widget::ePane && bGlobal)
	{
		PaneItem & item = PaneItem::Get(name);

		if (PaneItem::eNoPane == item.mPane) return 0;

		Pane & pane = Pane::Get(item.mPane);

		if (fX != 0) *fX = pane.mX + widget.mX * pane.mW;		
		if (fY != 0) *fY = pane.mY + widget.mY * pane.mH;
		if (fW != 0) *fW = pane.mW * widget.mW;
		if (fH != 0) *fH = pane.mH * widget.mH;
	}

	//////////////////////////////////////////////////////////////////////////////////////
	// If we do not request global values or the widget is a pane, we supply the widget's
	// local coordinates and dimensions.
	//////////////////////////////////////////////////////////////////////////////////////
	else
	{
		if (fX != 0) *fX = widget.mX;
		if (fY != 0) *fY = widget.mY;
		if (fW != 0) *fW = widget.mW;
		if (fH != 0) *fH = widget.mH;
	}

	return 1;
}

/// @brief Installs a widget's draw handler
/// @param name Name used to reference the widget
/// @param draw The draw handler
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_SetDraw (Uint32 name, void (*draw)(Uint32, void *))
{
	if (!Widget_IsValid(name)) return 0;
	
	Widget::Get(name).mDraw = draw;

	return 1;
}

/// @brief Installs a widget's hit test handler
/// @param name Name used to reference the widget
/// @param hitTest The hit test handler
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_SetHitTest (Uint32 name, void (*hitTest)(Uint32, float, float, void *))
{
	if (!Widget_IsValid(name)) return 0;
	
	Widget::Get(name).mHitTest = hitTest;

	return 1;
}

/// @brief Installs a widget's process event handler
/// @param name Name used to reference the widget
/// @param processEvent The process event handler
/// @return 0 on failure, non-0 for success
/// @note Tested
int Widget_SetProcessEvent (Uint32 name, void (*processEvent)(Uint32, enum _WidgetEventType, void *))
{
	if (!Widget_IsValid(name)) return 0;
	
	Widget::Get(name).mProcessEvent = processEvent;

	return 1;
}

/// @brief Used to signal that the cursor is over a widget
/// @note Function will NOP if not called from a hit test callback during input propagation
/// @note Tested
void Widget_SignalCursorOver (void)
{
	UserInterface & UI = UserInterface::Get();

	if (UserInterface::eNullWidget == UI.mCurrentHit) return;

	Widget::Get(UI.mCurrentHit).mStatus[Widget::eUnder] = true;
}

/// @brief Indicates whether a widget is grabbed
/// @param name Name used to reference the widget
/// @return A boolean indicating whether the widget is grabbed
/// @note Tested
SDL_bool Widget_IsGrabbed (Uint32 name)
{
	if (!Widget_IsValid(name)) return SDL_FALSE;
	if (!Widget::Get(name).mStatus[Widget::eHeld]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a widget is entered
/// @param name Name used to reference the widget
/// @return A boolean indicating whether the widget is entered
/// @note Tested
SDL_bool Widget_IsEntered (Uint32 name)
{
	if (!Widget_IsValid(name)) return SDL_FALSE;
	if (!Widget::Get(name).mStatus[Widget::eIn]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a widget is tagged
/// @param name Name used to reference the widget
/// @return A boolean indicating whether the widget is tagged
/// @note Tested
SDL_bool Widget_IsTagged (Uint32 name)
{
	if (!Widget_IsValid(name)) return SDL_FALSE;
	if (!Widget::Get(name).mStatus[Widget::eTagged]) return SDL_FALSE;
	
	return SDL_TRUE;
}

/// @brief Indicates whether a widget is loaded: for panes, into a pane layer; for pane
///		   items, into a pane
/// @param name Name used to reference the widget
/// @return A boolean indicating whether the widget is loaded
/// @note Tested
SDL_bool Widget_IsLoaded (Uint32 name)
{
	/////////////////////////////////////////////////////////////////////////////////////
	// A pane is loaded if its layer reference is not null; a pane item is loaded if its
	// pane reference is not null.
	/////////////////////////////////////////////////////////////////////////////////////
	if (!Widget_IsValid(name)) return SDL_FALSE;

	if (Widget::ePane == Widget::Get(name).mType)
	{
		if (Pane::eNoLayer == Pane::Get(name).mLayer) return SDL_FALSE;
	}

	else
	{
		if (PaneItem::eNoPane == PaneItem::Get(name).mPane) return SDL_FALSE;
	}

	return SDL_TRUE;
}

/// @brief Indicates whether a name corresponds to a valid widget
/// @param name Name used to reference the widget
/// @return A boolean indicating name validity
/// @note Tested
SDL_bool Widget_IsValid (Uint32 name)
{
	//////////////////////////////////////////////////////////////////////////////////
	// A widget name is invalid if it is out of range of the user interface manager's 
	// widget vector or there is no entry corresponding to its name in said vector.
	//////////////////////////////////////////////////////////////////////////////////
	if (name >= UserInterface::Get().mWidgets.size()) return SDL_FALSE;
	if (0 == UserInterface::Get().mWidgets[name]) return SDL_FALSE;

	assert(UserInterface_WasInit());
	assert(name != UserInterface::eNullWidget);

	return SDL_TRUE;
}