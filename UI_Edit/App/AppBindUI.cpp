#include "AppGeneral.h"
#include "../UserInterface/Button.h"
#include "../UserInterface/Checkbox.h"
#include "../UserInterface/Listbox.h"
#include "../UserInterface/Pane.h"
#include "../UserInterface/PaneItem.h"
#include "../UserInterface/PaneLayer.h"
#include "../UserInterface/Radiobox.h"
#include "../UserInterface/Slider.h"
#include "../UserInterface/Textbox.h"
#include "../UserInterface/UserInterface.h"
#include "../UserInterface/Widget.h"
#include "../UserInterface/WidgetEvent.h"
#include <cstdio>
#include <cstdlib>

/// General draw lookup function 
static void Draw (Uint32 name, void * app)
{
	lua_State * state = static_cast<lua_State*>(app);

	lua_getglobal(state, "DrawCall");
	lua_pushnumber(state, name);
	lua_pushlightuserdata(state, app);
	lua_pcall(state, 2, 0, 0);
}

/// General hit test lookup function 
static void HitTest (Uint32 name, float fCursorX, float fCursorY, void * app)
{
	lua_State * state = static_cast<lua_State*>(app);

	lua_getglobal(state, "HitTestCall");
	lua_pushnumber(state, name);
	lua_pushnumber(state, fCursorX);
	lua_pushnumber(state, fCursorY);
	lua_pushlightuserdata(state, app);
	lua_pcall(state, 4, 0, 0);
}

/// General process event lookup function
static void ProcessEvent (Uint32 name, WidgetEventType type, void * app)
{
	lua_State * state = static_cast<lua_State*>(app);

	lua_getglobal(state, "ProcessEventCall");
	lua_pushnumber(state, name);
	lua_pushnumber(state, type);
	lua_pushlightuserdata(state, app);
	lua_pcall(state, 3, 0, 0);
}

// General fit lookup function
static lua_Number FitBody (Uint32 name, float fCursorX, float fCursorY, void * app)
{
	lua_State * state = static_cast<lua_State*>(app);

	lua_getglobal(state, "FitCall");
	lua_pushnumber(state, name);
	lua_pushnumber(state, fCursorX);
	lua_pushnumber(state, fCursorY);
	lua_pushlightuserdata(state, app);
	lua_pcall(state, 4, 1, 0);

	lua_Number number = lua_tonumber(state, -1);

	lua_pop(state, 1);

	return number;
}

static Uint32 FitU (Uint32 name, float fCursorX, float fCursorY, void * app)
{
	return static_cast<Uint32>(FitBody(name, fCursorX, fCursorY, app));
}

static float FitF (Uint32 name, float fCursorX, float fCursorY, void * app)
{
	return static_cast<float>(FitBody(name, fCursorX, fCursorY, app));
}

static void FitXY (Uint32 name, float fCursorX, float fCursorY, void * app, float * fX, float * fY)
{
	lua_State * state = static_cast<lua_State*>(app);
	lua_getglobal(state, "FitCall");
	lua_pushnumber(state, name);
	lua_pushnumber(state, fCursorX);
	lua_pushnumber(state, fCursorY);
	lua_pushlightuserdata(state, app);
	lua_pcall(state, 4, 2, 0);

	*fX = F(state, -2);
	*fY = F(state, -1);

	lua_pop(state, 2);
}

/// Body of a function generally used to create an object
static int Create (lua_State * L, int (*func)(Uint32 *))
{
	Count(L, 0);

	Uint32 name;
	
	if (func(&name) == 0) lua_pushnil(L);

	else
	{
		lua_pushnumber(L, name);

		Widget_SetDraw(name, Draw);
		Widget_SetHitTest(name, HitTest);
		Widget_SetProcessEvent(name, ProcessEvent);

		if (func == Listbox_Create) Listbox_SetFitBestItem(name, FitU);
		if (func == Textbox_Create) Textbox_SetFitBestSpot(name, FitU);
		if (func == Slider_Create) Slider_SetFitBestOffset(name, FitF);
		if (func == Pane_Create) Pane_SetFitBestXY(name, FitXY);
	}

	return 1;
}

/// Body of a function generally used to run on one argument
static int Run (lua_State * L, int (*func)(Uint32))
{
	Count(L, 1);

	func(U(L, 1));

	return 0;
}

static int Run (lua_State * L, int (*func)(void))
{
	Count(L, 0);

	func();

	return 0;
}

static int Run (lua_State * L, void (*func)(void))
{
	Count(L, 0);

	func();

	return 0;
}

/// Body of a function generally used to tag an object
static int SetTag (lua_State * L, int (*func)(Uint32, wchar_t const *))
{
	Count(L, 2);

	wchar_t Tag[256];	mbstowcs(Tag, S(L, 2), 512);

	func(U(L, 1), Tag);

	return 0;
}

/// Body of a function generally used to get an object's tag
static int GetTag (lua_State * L, int (*func)(Uint32, wchar_t *))
{
	Count(L, 1);

	wchar_t TagW[256];

	if (func(U(L, 1), TagW) == 0) lua_pushnil(L);

	else
	{
		char TagA[256];	wcstombs(TagA, TagW, 256);

		lua_pushstring(L, TagA);
	}

	return 1;
}

/// Body of a function generally used to signal an object
static int Signal (lua_State * L, void (*func)(Uint32))
{
	Count(L, 1);

	func(U(L, 1));

	return 0;
}

/// Body of a function generally used to set a boolean argument
static int SetBoolean (lua_State * L, int (*func)(Uint32, SDL_bool))
{
	Count(L, 2);

	func(U(L, 1), B(L, 2));

	return 0;
}

static int SetBoolean (lua_State * L, int (*func)(Uint32, Uint32, SDL_bool))
{
	Count(L, 3);

	func(U(L, 1), U(L, 2), B(L, 3));

	return 0;
}

/// Body of a function generally used to get a boolean result
static int GetBoolean (lua_State * L, SDL_bool (*func)(Uint32))
{
	Count(L, 1);

	lua_pushboolean(L, func(U(L, 1)));

	return 1;
}

static int GetBoolean (lua_State * L, SDL_bool (*func)(Uint32, Uint32))
{
	Count(L, 2);

	lua_pushboolean(L, func(U(L, 1), U(L, 2)));

	return 1;
}

static int GetBoolean (lua_State * L, SDL_bool (*func)(Uint32, Uint32, SDL_bool))
{
	Count(L, 3);

	lua_pushboolean(L, func(U(L, 1), U(L, 2), B(L, 3)));

	return 1;
}

/// Body of a function generally used to set a Uint32 argument
static int SetUint32 (lua_State * L, int (*func)(Uint32, Uint32))
{
	Count(L, 2);

	func(U(L, 1), U(L, 2));

	return 0;
}

static int SetUint32 (lua_State * L, int (*func)(Uint32, Uint32, Uint32))
{
	Count(L, 3);

	func(U(L, 1), U(L, 2), U(L, 3));

	return 0;
}

/// Body of a function generally used to get a Uint32 result
static int GetUint32 (lua_State * L, int (*func)(Uint32 *))
{
	Count(L, 0);

	Uint32 uint32;

	if (func(&uint32) == 0) lua_pushnil(L);

	else lua_pushnumber(L, uint32);

	return 1;
}

static int GetUint32 (lua_State * L, int (*func)(Uint32, Uint32 *))
{
	Count(L, 1);

	Uint32 uint32;
	
	if (func(U(L, 1), &uint32) == 0) lua_pushnil(L);

	else lua_pushnumber(L, uint32);

	return 1;
}

static int GetUint32 (lua_State * L, int (*func)(Uint32, Uint32, Uint32 *))
{
	Count(L, 2);

	Uint32 uint32;
	
	if (func(U(L, 1), U(L, 2), &uint32) == 0) lua_pushnil(L);

	else lua_pushnumber(L, uint32);

	return 1;
}

static int GetSetUint32 (lua_State * L, int (*func)(Uint32, Uint32, Uint32 *))
{
	Count(L, 3);

	Uint32 uint32 = U(L, 3);
	
	if (func(U(L, 1), U(L, 2), &uint32) == 0) lua_pushnil(L);

	else lua_pushnumber(L, uint32);

	return 1;
}

///
/// Button functions
///
static int ButtonCreate (lua_State * L)
{
	return Create(L, Button_Create);
}

static int ButtonAllowPush (lua_State * L)
{
	return SetBoolean(L, Button_AllowPush);
}

static int ButtonIsPushAllowed (lua_State * L)
{
	return GetBoolean(L, Button_IsPushAllowed);
}

static int ButtonIsPushed (lua_State * L)
{
	return GetBoolean(L, Button_IsPushed);
}

static int ButtonIsValid (lua_State * L)
{
	return GetBoolean(L, Button_IsValid);
}

///
/// Checkbox functions
///
static int CheckboxCreate (lua_State * L)
{
	return Create(L, Checkbox_Create);
}

static int CheckboxCheck (lua_State * L)
{
	return SetBoolean(L, Checkbox_Check);
}

static int CheckboxToggleCheck (lua_State * L)
{
	return Run(L, Checkbox_ToggleCheck);
}

static int CheckboxAllowClick (lua_State * L)
{
	return SetBoolean(L, Checkbox_AllowClick);
}

static int CheckboxIsClickAllowed (lua_State * L)
{
	return GetBoolean(L, Checkbox_IsClickAllowed);
}

static int CheckboxIsChecked (lua_State * L)
{
	return GetBoolean(L, Checkbox_IsChecked);
}

static int CheckboxIsValid (lua_State * L)
{
	return GetBoolean(L, Checkbox_IsValid);
}

///
/// Listbox functions
///
static int ListboxCreate (lua_State * L)
{
	return Create(L, Listbox_Create);
}

static int ListboxGetItemCount (lua_State * L)
{
	return GetUint32(L, Listbox_GetItemCount);
}

static int ListboxSetOffset (lua_State * L)
{
	return SetUint32(L, Listbox_SetOffset);
}

static int ListboxGetOffset (lua_State * L)
{
	return GetUint32(L, Listbox_GetOffset);
}

static int ListboxSetCapacity (lua_State * L)
{
	return SetUint32(L, Listbox_SetCapacity);
}

static int ListboxGetCapacity (lua_State * L)
{
	return GetUint32(L, Listbox_GetCapacity);
}

static int ListboxGetHeldItem (lua_State * L)
{
	return GetUint32(L, Listbox_GetHeldItem);
}

static int ListboxGetInItem (lua_State * L)
{
	return GetUint32(L, Listbox_GetInItem);
}

static int ListboxSetItemContext (lua_State * L)
{
	return SetUint32(L, Listbox_SetItemContext);
}

static int ListboxGetItemContext (lua_State * L)
{
	return GetUint32(L, Listbox_GetItemContext);
}

static int ListboxSelectItem (lua_State * L)
{
	return SetBoolean(L, Listbox_SelectItem);
}

static int ListboxSelectItemRange (lua_State * L)
{
	Count(L, 4);

	Uint32 numItems = U(L, 3);

	if (Listbox_SelectItemRange(U(L, 1), U(L, 2), &numItems, B(L, 4)) == 0) lua_pushnil(L);

	else lua_pushnumber(L, numItems);

	return 1;
}

static int ListboxAddItem (lua_State * L)
{
	return SetUint32(L, Listbox_AddItem);
}

static int ListboxRemoveItem (lua_State * L)
{
	return SetUint32(L, Listbox_RemoveItem);
}

static int ListboxRemoveItemRange (lua_State * L)
{
	return GetSetUint32(L, Listbox_RemoveItemRange);
}

static int ListboxAllowItemClick (lua_State * L)
{
	return SetBoolean(L, Listbox_AllowItemClick);
}

static int ListboxAllowDragOver (lua_State * L)
{
	return SetBoolean(L, Listbox_AllowDragOver);
}

static int ListboxSetFitBestItem (lua_State * L)
{
	Count(L, 2);

	Listbox_SetFitBestItem(U(L, 1), static_cast<Uint32(*)(Uint32,float,float,void*)>(UD(L, 2)));

	return 0;
}

static int ListboxSignalCursorOverItem (lua_State * L)
{
	return Signal(L, Listbox_SignalCursorOverItem);
}

static int ListboxIsItemClickAllowed (lua_State * L)
{
	return GetBoolean(L, Listbox_IsItemClickAllowed);
}

static int ListboxIsDragOverAllowed (lua_State * L)
{
	return GetBoolean(L, Listbox_IsDragOverAllowed);
}

static int ListboxIsItemSelected (lua_State * L)
{
	return GetBoolean(L, Listbox_IsItemSelected);
}

static int ListboxIsItemValid (lua_State * L)
{
	return GetBoolean(L, Listbox_IsItemValid);
}

static int ListboxIsValid (lua_State * L)
{
	return GetBoolean(L, Listbox_IsValid);
}

///
/// Pane functions
///
static int PaneCreate (lua_State * L)
{
	return Create(L, Pane_Create);
}

static int PaneAddItem (lua_State * L)
{
	Count(L, 6);

	Pane_AddItem(U(L, 1), U(L, 2), F(L, 3), F(L, 4), F(L, 5), F(L, 6));

	return 0;
}

static int PaneRemoveFromLayer (lua_State * L)
{
	return Run(L, Pane_RemoveFromLayer);
}

static int PaneGetLayer (lua_State * L)
{
	return GetUint32(L, Pane_GetLayer);
}

static int PaneGetItemCount (lua_State * L)
{
	return GetUint32(L, Pane_GetItemCount);
}

static int PaneRemoveFocusChainItem (lua_State * L)
{
	return SetUint32(L, Pane_RemoveFocusChainItem);
}

static int PaneClearFocusChain (lua_State * L)
{
	return Run(L, Pane_ClearFocusChain);
}

static int PaneLoadFocusChain (lua_State * L)
{
	CountIn(L, 2, 65);

	int count = lua_gettop(L);

	Uint32 stash[64];

	for (int index = 2; index < count; ++index) stash[index - 2] = U(L, index);

	Pane_LoadFocusChain(U(L, 1), stash, static_cast<Uint32>(count - 2), B(L, count));

	return 0;
}

static int PaneSwapFocusChainItems (lua_State * L)
{
	return SetUint32(L, Pane_SwapFocusChainItems);
}

static int PaneGetFocusChainItem (lua_State * L)
{
	return GetUint32(L, Pane_GetFocusChainItem);
}

static int PaneGetFocusChainItemCount (lua_State * L)
{
	return GetUint32(L, Pane_GetFocusChainItemCount);
}

static int PaneSetFocusSlot (lua_State * L)
{
	return SetUint32(L, Pane_SetFocusSlot);
}

static int PaneGetFocusSlot (lua_State * L)
{
	return GetUint32(L, Pane_GetFocusSlot);
}

static int PaneGetFocusPriorSlot (lua_State * L)
{
	return GetUint32(L, Pane_GetFocusPriorSlot);
}

static int PaneGetFocusNextSlot (lua_State * L)
{
	return GetUint32(L, Pane_GetFocusNextSlot);
}

static int PaneAllowDrag (lua_State * L)
{
	return SetBoolean(L, Pane_AllowDrag);
}

static int PaneSetFitBestXY (lua_State * L)
{
	Count(L, 2);

	Pane_SetFitBestXY(U(L, 1), static_cast<void(*)(Uint32,float,float,void*,float*,float*)>(UD(L, 2)));

	return 0;
}

static int PaneIsCaught (lua_State * L)
{
	return GetBoolean(L, Pane_IsCaught);
}

static int PaneIsDragAllowed (lua_State * L)
{
	return GetBoolean(L, Pane_IsDragAllowed);
}

static int PaneIsFocusChainSlotValid (lua_State * L)
{
	return GetBoolean(L, Pane_IsFocusChainSlotValid);
}

static int PaneIsLoaded (lua_State * L)
{
	return GetBoolean(L, Pane_IsLoaded);
}

static int PaneIsValid (lua_State * L)
{
	return GetBoolean(L, Pane_IsValid);
}

///
/// PaneItem functions
///
static int PaneItemRemoveFromPane (lua_State * L)
{
	return Run(L, PaneItem_RemoveFromPane);
}

static int PaneItemGetPane (lua_State * L)
{
	return GetUint32(L, PaneItem_GetPane);
}

static int PaneItemGetFocusChainSlot (lua_State * L)
{
	return GetUint32(L, PaneItem_GetFocusChainSlot);
}

static int PaneItemIsFocusChainItem (lua_State * L)
{
	return GetBoolean(L, PaneItem_IsFocusChainItem);
}

static int PaneItemIsLoaded (lua_State * L)
{
	return GetBoolean(L, PaneItem_IsLoaded);
}

static int PaneItemIsValid (lua_State * L)
{
	return GetBoolean(L, PaneItem_IsValid);
}

///
/// PaneLayer functions
///
static int PaneLayerCreate (lua_State * L)
{
	return Create(L, PaneLayer_Create);
}

static int PaneLayerDestroy (lua_State * L)
{
	return Run(L, PaneLayer_Destroy);
}

static int PaneLayerAddPane (lua_State * L)
{
	Count(L, 6);

	PaneLayer_AddPane(U(L, 1), U(L, 2), F(L, 3), F(L, 4), F(L, 5), F(L, 6));

	return 0;
}

static int PaneLayerSetTag (lua_State * L)
{
	return SetTag(L, PaneLayer_SetTag);
}

static int PaneLayerGetTag (lua_State * L)
{
	return GetTag(L, PaneLayer_GetTag);
}

static int PaneLayerUntag (lua_State * L)
{
	return Run(L, PaneLayer_Untag);
}

static int PaneLayerGetSlot (lua_State * L)
{
	return GetUint32(L, PaneLayer_GetSlot);
}

static int PaneLayerGetPaneCount (lua_State * L)
{
	return GetUint32(L, PaneLayer_GetPaneCount);
}

static int PaneLayerIsLoaded (lua_State * L)
{
	return GetBoolean(L, PaneLayer_IsLoaded);
}

static int PaneLayerIsTagged (lua_State * L)
{
	return GetBoolean(L, PaneLayer_IsTagged);
}

static int PaneLayerIsValid (lua_State * L)
{
	return GetBoolean(L, PaneLayer_IsValid);
}

///
/// Radiobox functions
///
static int RadioboxCreate (lua_State * L)
{
	return Create(L, Radiobox_Create);
}

static int RadioboxSetup (lua_State * L)
{
	return SetUint32(L, Radiobox_Setup);
}

static int RadioboxGetOptionCount (lua_State * L)
{
	return GetUint32(L, Radiobox_GetOptionCount);
}

static int RadioboxSetChoice (lua_State * L)
{
	return SetUint32(L, Radiobox_SetChoice);
}

static int RadioboxGetChoice (lua_State * L)
{
	return GetUint32(L, Radiobox_GetChoice);
}

static int RadioboxGetHeldOption (lua_State * L)
{
	return GetUint32(L, Radiobox_GetHeldOption);
}

static int RadioboxGetInOption (lua_State * L)
{
	return GetUint32(L, Radiobox_GetInOption);
}

static int RadioboxAllowClick (lua_State * L)
{
	return SetBoolean(L, Radiobox_AllowClick);
}

static int RadioboxSignalCursorOverOption (lua_State * L)
{
	return Signal(L, Radiobox_SignalCursorOverOption);
}

static int RadioboxIsClickAllowed (lua_State * L)
{
	return GetBoolean(L, Radiobox_IsClickAllowed);
}

static int RadioboxIsOptionValid (lua_State * L)
{
	return GetBoolean(L, Radiobox_IsOptionValid);
}

static int RadioboxIsValid (lua_State * L)
{
	return GetBoolean(L, Radiobox_IsValid);
}

///
/// Slider functions
///
static int SliderCreate (lua_State * L)
{
	return Create(L, Slider_Create);
}

static int SliderSetOffset (lua_State * L)
{
	Count(L, 2);

	Slider_SetOffset(U(L, 1), F(L, 2));

	return 0;
}

static int SliderGetOffset (lua_State * L)
{
	Count(L, 1);

	float offset;

	if (Slider_GetOffset(U(L, 1), &offset) == 0) lua_pushnil(L);

	else lua_pushnumber(L, offset);

	return 1;
}

static int SliderAllowSnap (lua_State * L)
{
	return SetBoolean(L, Slider_AllowSnap);
}

static int SliderAllowThumbDrag (lua_State * L)
{
	return SetBoolean(L, Slider_AllowThumbDrag);
}

static int SliderSetFitBestOffset (lua_State * L)
{
	Count(L, 2);

	Slider_SetFitBestOffset(U(L, 1), static_cast<float(*)(Uint32,float,float,void*)>(UD(L, 2)));

	return 0;
}

static int SliderSignalCursorOverThumb (lua_State * L)
{
	return Run(L, Slider_SignalCursorOverThumb);
}

static int SliderIsThumbGrabbed (lua_State * L)
{
	return GetBoolean(L, Slider_IsThumbGrabbed);
}

static int SliderIsThumbEntered (lua_State * L)
{
	return GetBoolean(L, Slider_IsThumbEntered);
}

static int SliderIsSnapAllowed (lua_State * L)
{
	return GetBoolean(L, Slider_IsSnapAllowed);
}

static int SliderIsThumbDragAllowed (lua_State * L)
{
	return GetBoolean(L, Slider_IsThumbDragAllowed);
}

static int SliderIsThumbCaught (lua_State * L)
{
	 return GetBoolean(L, Slider_IsThumbCaught);
}

static int SliderIsValid (lua_State * L)
{
	return GetBoolean(L, Slider_IsValid);
}

///
/// Textbox functions
///
static int TextboxCreate (lua_State * L)
{
	return Create(L, Textbox_Create);
}

static int TextboxSetOffset (lua_State * L)
{
	return SetUint32(L, Textbox_SetOffset);
}

static int TextboxGetOffset (lua_State * L)
{
	return GetUint32(L, Textbox_GetOffset);
}

static int TextboxSetCursor (lua_State * L)
{
	return SetUint32(L, Textbox_SetCursor);
}

static int TextboxGetCursor (lua_State * L)
{
	return GetUint32(L, Textbox_GetCursor);
}

static int TextboxGetHeldSpot (lua_State * L)
{
	return GetUint32(L, Textbox_GetHeldSpot);
}

static int TextboxSetMaxCharCount (lua_State * L)
{
	return SetUint32(L, Textbox_SetMaxCharCount);
}

static int TextboxGetMaxCharCount (lua_State * L)
{
	return GetUint32(L, Textbox_GetMaxCharCount);
}

static int TextboxGetCharCount  (lua_State * L)
{
	return GetUint32(L, Textbox_GetCharCount);
}

static int TextboxGetSelectStart  (lua_State * L)
{
	return GetUint32(L, Textbox_GetSelectStart);
}

static int TextboxGetSelectCount  (lua_State * L)
{
	return GetUint32(L, Textbox_GetSelectCount);
}

static int TextboxSetChar (lua_State * L)
{
	Count(L, 4);

	wchar_t Char;	mbtowc(&Char, S(L, 3), 2);

	Textbox_SetChar(U(L, 1), U(L, 2), Char, B(L, 4));

	return 0;
}

static int TextboxGetChar (lua_State * L)
{
	Count(L, 2);

	wchar_t CharW;	if (Textbox_GetChar(U(L, 1), U(L, 2), &CharW) == 0) lua_pushnil(L);

	else
	{
		char CharA[2] = {0};	wctomb(CharA, CharW);

		lua_pushstring(L, CharA);
	}

	return 1;
}

static int TextboxDeleteChar (lua_State * L)
{
	return SetUint32(L, Textbox_DeleteChar);
}

static int TextboxSetSubstr (lua_State * L)
{
	Count(L, 5);

	wchar_t StrW[256];	mbstowcs(StrW, S(L, 3), 512);

	Uint32 count = U(L, 4);

	if (Textbox_SetSubstr(U(L, 1), U(L, 2), StrW, &count, B(L, 5)) == 0) lua_pushnil(L);

	else lua_pushnumber(L, count);

	return 1;
}

static int TextboxGetSubstr (lua_State * L)
{
	Count(L, 3);

	wchar_t StrW[256];

	Uint32 count = U(L, 3);

	if (Textbox_GetSubstr(U(L, 1), U(L, 2), StrW, &count) == 0) lua_pushnil(L);

	else
	{
		char StrA[256];	wcstombs(StrA, StrW, 256);

		lua_pushstring(L, StrA);
		lua_pushnumber(L, count);
	}

	return lua_gettop(L) - 3;
}

static int TextboxDeleteSubstr (lua_State * L)
{
	return GetSetUint32(L, Textbox_DeleteSubstr);
}

static int TextboxSelectChar (lua_State * L)
{
	return SetUint32(L, Textbox_SelectChar);
}

static int TextboxSelectSubstr (lua_State * L)
{
	return GetSetUint32(L, Textbox_SelectSubstr);
}

static int TextboxGetSelectionSubstr (lua_State * L)
{
	Count(L, 1);

	wchar_t StrW[256];	Textbox_GetSelectionSubstr(U(L, 1), StrW);

	char StrA[256];	wcstombs(StrA, StrW, 256);

	lua_pushstring(L, StrA);

	return 1;
}

static int TextboxRemoveSelection (lua_State * L)
{
	return Run(L, Textbox_RemoveSelection);
}

static int TextboxAllowSpotClick (lua_State * L)
{
	return SetBoolean(L, Textbox_AllowSpotClick);
}

static int TextboxAllowDragOver (lua_State * L)
{
	return SetBoolean(L, Textbox_AllowDragOver);
}

static int TextboxSetFitBestSpot (lua_State * L)
{
	Count(L, 2);

	Textbox_SetFitBestSpot(U(L, 1), static_cast<Uint32(*)(Uint32,float,float,void*)>(UD(L,2)));

	return 0;
}

static int TextboxSignalCursorOverSpot (lua_State * L)
{
	return Signal(L, Textbox_SignalCursorOverSpot);
}

static int TextboxIsSpotClickAllowed (lua_State * L)
{
	return GetBoolean(L, Textbox_IsSpotClickAllowed);
}

static int TextboxIsDragOverAllowed (lua_State * L)
{
	return GetBoolean(L, Textbox_IsDragOverAllowed);
}

static int TextboxIsSpotValid (lua_State * L)
{
	return GetBoolean(L, Textbox_IsSpotValid);
}

static int TextboxIsValid (lua_State * L)
{
	return GetBoolean(L, Textbox_IsValid);
}

///
/// UserInterface functions
///
static int UserInterfaceInitSystem (lua_State * L)
{
	return Run(L, UserInterface_InitSystem);
}

static int UserInterfacePropagateInput (lua_State * L)
{
	Count(L, 3);

	int count = lua_gettop(L);

	UserInterface_PropagateInput(F(L, 1), F(L, 2), B(L, 3), L);

	return 0;
}

static int UserInterfaceClearInput (lua_State * L)
{
	return Run(L, UserInterface_ClearInput);
}

static int UserInterfaceDraw (lua_State * L)
{
	Count(L, 0);

	UserInterface_Draw(L);

	return 0;
}

static int UserInterfaceRemoveFrameLayer (lua_State * L)
{
	return Run(L, UserInterface_RemoveFrameLayer);
}

static int UserInterfaceClearFrameLayers (lua_State * L)
{
	return Run(L, UserInterface_ClearFrameLayers);
}

static int UserInterfaceLoadFrameLayers (lua_State * L)
{
	CountIn(L, 0, 63);

	int count = lua_gettop(L);

	Uint32 stash[64];

	for (int index = 1; index <= count; ++index) stash[index - 1] = U(L, index);

	UserInterface_LoadFrameLayers(stash, static_cast<Uint32>(count));

	return 0;
}

static int UserInterfaceSwapFrameLayers (lua_State * L)
{
	return SetUint32(L, UserInterface_SwapFrameLayers);
}

static int UserInterfaceGetFrameLayer (lua_State * L)
{
	return GetUint32(L, UserInterface_GetFrameLayer);
}

static int UserInterfaceGetFrameSize (lua_State * L)
{
	return GetUint32(L, UserInterface_GetFrameSize);
}

static int UserInterfaceFindLayer (lua_State * L)
{
	Count(L, 1);

	wchar_t Tag[256];	mbstowcs(Tag, S(L, 1), 512);

	Uint32 layer;
	
	if (UserInterface_FindLayer(Tag, &layer) == 0) lua_pushnil(L);

	lua_pushnumber(L, layer);

	return 1;
}

static int UserInterfaceFindWidget (lua_State * L)
{
	Count(L, 1);

	wchar_t Tag[256];	mbstowcs(Tag, S(L, 1), 512);

	Uint32 widget;
	
	if (UserInterface_FindWidget(Tag, &widget) == 0) lua_pushnil(L);

	else lua_pushnumber(L, widget);

	return 1;
}

static int UserInterfaceGetChoice (lua_State * L)
{
	return GetUint32(L, UserInterface_GetChoice);
}

static int UserInterfaceGetEventIndex (lua_State * L)
{
	return GetUint32(L, UserInterface_GetEventIndex);
}

static int UserInterfaceGetEventRange (lua_State * L)
{
	Count(L, 0);

	Uint32 start, count;
	
	if (UserInterface_GetEventRange(&start, &count) == 0) lua_pushnil(L);

	else
	{
		lua_pushnumber(L, start);
		lua_pushnumber(L, count);
	}

	return lua_gettop(L);
}

static int UserInterfaceGetEventPoint (lua_State * L)
{
	Count(L, 0);

	float fX, fY;
	
	if (UserInterface_GetEventPoint(&fX, &fY) == 0) lua_pushnil(L);

	else
	{
		lua_pushnumber(L, fX);
		lua_pushnumber(L, fY);
	}

	return lua_gettop(L);
}

static int UserInterfaceQuitSystem (lua_State * L)
{
	return Run(L, UserInterface_QuitSystem);
}

static int UserInterfaceIsFrameSlotValid (lua_State * L)
{
	return GetBoolean(L, UserInterface_IsFrameSlotValid);
}

static int UserInterfaceWasInit (lua_State * L)
{
	Count(L, 0);

	lua_pushboolean(L, UserInterface_WasInit());

	return 1;
}

///
/// Widget functions
///
static int WidgetDestroy (lua_State * L)
{
	return Run(L, Widget_Destroy);
}

static int WidgetSetTag (lua_State * L)
{
	return SetTag(L, Widget_SetTag);
}

static int WidgetGetTag (lua_State * L)
{
	return GetTag(L, Widget_GetTag);
}

static int WidgetUntag (lua_State * L)
{
	return Run(L, Widget_Untag);
}

static int WidgetSetXY (lua_State * L)
{
	Count(L, 3);

	Widget_SetXY(U(L, 1), F(L, 2), F(L, 3));

	return 0;
}

static int WidgetSetWH (lua_State * L)
{
	Count(L, 3);

	Widget_SetWH(U(L, 1), F(L, 2), F(L, 3));

	return 0;
}

static int WidgetGetXYWH (lua_State * L)
{
	Count(L, 2);

	float x, y, w, h;

	if (Widget_GetXYWH(U(L, 1), &x, &y, &w, &h, B(L, 2)) == 0) lua_pushnil(L);

	else
	{
		lua_pushnumber(L, x);
		lua_pushnumber(L, y);
		lua_pushnumber(L, w);
		lua_pushnumber(L, h);
	}

	return lua_gettop(L) - 2;
}

static int WidgetSetDraw (lua_State * L)
{
	Count(L, 2);

	Widget_SetDraw(U(L, 1), static_cast<void(*)(Uint32,void*)>(UD(L, 2)));

	return 0;
}

static int WidgetSetHitTest (lua_State * L)
{
	Count(L, 2);

	Widget_SetHitTest(U(L, 1), static_cast<void(*)(Uint32,float,float,void*)>(UD(L, 2)));

	return 0;
}

static int WidgetSetProcessEvent (lua_State * L)
{
	Count(L, 2);

	Widget_SetProcessEvent(U(L, 1), static_cast<void(*)(Uint32,enum _WidgetEventType,void*)>(UD(L, 2)));

	return 0;
}

static int WidgetSignalCursorOver (lua_State * L)
{
	return Run(L, Widget_SignalCursorOver);
}

static int WidgetIsGrabbed (lua_State * L)
{
	return GetBoolean(L, Widget_IsGrabbed);
}

static int WidgetIsEntered (lua_State * L)
{
	return GetBoolean(L, Widget_IsEntered);
}

static int WidgetIsTagged (lua_State * L)
{
	return GetBoolean(L, Widget_IsTagged);
}

static int WidgetIsLoaded (lua_State * L)
{
	return GetBoolean(L, Widget_IsLoaded);
}

static int WidgetIsValid (lua_State * L)
{
	return GetBoolean(L, Widget_IsValid);
}

///
/// Function tables
///
static const luaL_reg ButtonFuncs[] = {
	{ "Create", ButtonCreate },
	{ "AllowPush", ButtonAllowPush },
	{ "IsPushAllowed", ButtonIsPushAllowed },
	{ "IsPushed", ButtonIsPushed },
	{ "IsValid", ButtonIsValid },
	{ 0, 0 }
};

static const luaL_reg CheckboxFuncs[] = {
	{ "Create", CheckboxCreate },
	{ "Check", CheckboxCheck },
	{ "ToggleCheck", CheckboxToggleCheck },
	{ "AllowClick", CheckboxAllowClick },
	{ "IsClickAllowed", CheckboxIsClickAllowed },
	{ "IsChecked", CheckboxIsChecked },
	{ "IsValid", CheckboxIsValid },
	{ 0, 0 }
};

static const luaL_reg ListboxFuncs[] = {
	{ "Create", ListboxCreate },
	{ "GetItemCount", ListboxGetItemCount },
	{ "SetOffset", ListboxSetOffset },
	{ "GetOffset", ListboxGetOffset },
	{ "SetCapacity", ListboxSetCapacity },
	{ "GetCapacity", ListboxGetCapacity },
	{ "GetHeldItem", ListboxGetHeldItem },
	{ "GetInItem", ListboxGetInItem },
	{ "SetItemContext", ListboxSetItemContext },
	{ "GetItemContext", ListboxGetItemContext },
	{ "SelectItem", ListboxSelectItem },
	{ "SelectItemRange", ListboxSelectItemRange },
	{ "AddItem", ListboxAddItem },
	{ "RemoveItem", ListboxRemoveItem },
	{ "RemoveItemRange", ListboxRemoveItemRange },
	{ "AllowItemClick", ListboxAllowItemClick },
	{ "AllowDragOver", ListboxAllowDragOver },
	{ "SetFitBestItem", ListboxSetFitBestItem },
	{ "SignalCursorOverItem", ListboxSignalCursorOverItem },
	{ "IsItemClickAllowed", ListboxIsItemClickAllowed },
	{ "IsDragOverAllowed", ListboxIsDragOverAllowed },
	{ "IsItemSelected", ListboxIsItemSelected },
	{ "IsItemValid", ListboxIsItemValid },
	{ "IsValid", ListboxIsValid },
	{ 0, 0 }
};

static const luaL_reg PaneFuncs[] = {
	{ "Create", PaneCreate },
	{ "AddItem", PaneAddItem },
	{ "RemoveFromLayer", PaneRemoveFromLayer },
	{ "GetLayer", PaneGetLayer },
	{ "GetItemCount", PaneGetItemCount },
	{ "RemoveFocusChainItem", PaneRemoveFocusChainItem },
	{ "ClearFocusChain", PaneClearFocusChain },
	{ "LoadFocusChain", PaneLoadFocusChain },
	{ "SwapFocusChainItems", PaneSwapFocusChainItems },
	{ "GetFocusChainItem", PaneGetFocusChainItem },
	{ "GetFocusChainItemCount", PaneGetFocusChainItemCount },
	{ "SetFocusSlot", PaneSetFocusSlot },
	{ "GetFocusSlot", PaneGetFocusSlot },
	{ "GetFocusPriorSlot", PaneGetFocusPriorSlot },
	{ "GetFocusNextSlot", PaneGetFocusNextSlot },
	{ "AllowDrag", PaneAllowDrag },
	{ "SetFitBestXY", PaneSetFitBestXY },
	{ "IsCaught", PaneIsCaught },
	{ "IsDragAllowed", PaneIsDragAllowed },
	{ "IsFocusChainSlotValid", PaneIsFocusChainSlotValid },
	{ "IsLoaded", PaneIsLoaded },
	{ "IsValid", PaneIsValid },
	{ 0, 0 }
};

static const luaL_reg PaneItemFuncs[] = {
	{ "RemoveFromPane", PaneItemRemoveFromPane },
	{ "GetPane", PaneItemGetPane },
	{ "GetFocusChainSlot", PaneItemGetFocusChainSlot },
	{ "IsFocusChainItem", PaneItemIsFocusChainItem },
	{ "IsLoaded", PaneItemIsLoaded },
	{ "IsValid", PaneItemIsValid },
	{ 0, 0 }
};

static const luaL_reg PaneLayerFuncs[] = {
	{ "Create", PaneLayerCreate },
	{ "Destroy", PaneLayerDestroy },
	{ "AddPane", PaneLayerAddPane },
	{ "SetTag", PaneLayerSetTag },
	{ "GetTag", PaneLayerGetTag },
	{ "Untag", PaneLayerUntag },
	{ "GetSlot", PaneLayerGetSlot },
	{ "GetPaneCount", PaneLayerGetPaneCount },
	{ "IsLoaded", PaneLayerIsLoaded },
	{ "IsTagged", PaneLayerIsTagged },
	{ "IsValid", PaneLayerIsValid },
	{ 0, 0 }
};

static const luaL_reg RadioboxFuncs[] = {
	{ "Create", RadioboxCreate },
	{ "Setup", RadioboxSetup },
	{ "GetOptionCount", RadioboxGetOptionCount },
	{ "SetChoice", RadioboxSetChoice },
	{ "GetChoice", RadioboxGetChoice },
	{ "GetHeldOption", RadioboxGetHeldOption },
	{ "GetInOption", RadioboxGetInOption },
	{ "AllowClick", RadioboxAllowClick },
	{ "SignalCursorOverOption", RadioboxSignalCursorOverOption },
	{ "IsClickAllowed", RadioboxIsClickAllowed },
	{ "IsOptionValid", RadioboxIsOptionValid },
	{ "IsValid", RadioboxIsValid },
	{ 0, 0 }
};

static const luaL_reg SliderFuncs[] = {
	{ "Create", SliderCreate },
	{ "SetOffset", SliderSetOffset },
	{ "GetOffset", SliderGetOffset },
	{ "AllowSnap", SliderAllowSnap },
	{ "AllowThumbDrag", SliderAllowThumbDrag },
	{ "SetFitBestOffset", SliderSetFitBestOffset },
	{ "SignalCursorOverThumb", SliderSignalCursorOverThumb },
	{ "IsThumbGrabbed", SliderIsThumbGrabbed },
	{ "IsThumbEntered", SliderIsThumbEntered },
	{ "IsSnapAllowed", SliderIsSnapAllowed },
	{ "IsThumbDragAllowed", SliderIsThumbDragAllowed },
	{ "IsThumbCaught", SliderIsThumbCaught },
	{ "IsValid", SliderIsValid },
	{ 0, 0 }
};

static const luaL_reg TextboxFuncs[] = {
	{ "Create", TextboxCreate },
	{ "SetOffset", TextboxSetOffset },
	{ "GetOffset", TextboxGetOffset },
	{ "SetCursor", TextboxSetCursor },
	{ "GetCursor", TextboxGetCursor },
	{ "GetHeldSpot", TextboxGetHeldSpot },
	{ "SetMaxCharCount", TextboxSetMaxCharCount },
	{ "GetMaxCharCount", TextboxGetMaxCharCount },
	{ "GetCharCount", TextboxGetCharCount },
	{ "GetSelectStart", TextboxGetSelectStart },
	{ "GetSelectCount", TextboxGetSelectCount },
	{ "SetChar", TextboxSetChar },
	{ "GetChar", TextboxGetChar },
	{ "DeleteChar", TextboxDeleteChar },
	{ "SetSubstr", TextboxSetSubstr },
	{ "GetSubstr", TextboxGetSubstr },
	{ "DeleteSubstr", TextboxDeleteSubstr },
	{ "SelectChar", TextboxSelectChar },
	{ "SelectSubstr", TextboxSelectSubstr },
	{ "GetSelectionSubstr", TextboxGetSelectionSubstr },
	{ "RemoveSelection", TextboxRemoveSelection },
	{ "AllowSpotClick", TextboxAllowSpotClick },
	{ "AllowDragOver", TextboxAllowDragOver },
	{ "SetFitBestSpot", TextboxSetFitBestSpot },
	{ "SignalCursorOverSpot", TextboxSignalCursorOverSpot },
	{ "IsSpotClickAllowed", TextboxIsSpotClickAllowed },
	{ "IsDragOverAllowed", TextboxIsDragOverAllowed },
	{ "IsSpotValid", TextboxIsSpotValid },
	{ "IsValid", TextboxIsValid },
	{ 0, 0 }
};

static const luaL_reg UIFuncs[] = {
	{ "InitSystem", UserInterfaceInitSystem },
	{ "PropagateInput", UserInterfacePropagateInput },
	{ "ClearInput", UserInterfaceClearInput },
	{ "Draw", UserInterfaceDraw },
	{ "RemoveFrameLayer", UserInterfaceRemoveFrameLayer },
	{ "ClearFrameLayers", UserInterfaceClearFrameLayers },
	{ "LoadFrameLayers", UserInterfaceLoadFrameLayers },
	{ "SwapFrameLayers", UserInterfaceSwapFrameLayers },
	{ "GetFrameLayer", UserInterfaceGetFrameLayer },
	{ "GetFrameSize", UserInterfaceGetFrameSize },
	{ "FindLayer", UserInterfaceFindLayer },
	{ "FindWidget", UserInterfaceFindWidget },
	{ "GetChoice", UserInterfaceGetChoice },
	{ "GetEventIndex", UserInterfaceGetEventIndex },
	{ "GetEventRange", UserInterfaceGetEventRange },
	{ "GetEventPoint", UserInterfaceGetEventPoint },
	{ "QuitSystem", UserInterfaceQuitSystem },
	{ "IsFrameSlotValid", UserInterfaceIsFrameSlotValid },
	{ "WasInit", UserInterfaceWasInit },
	{ 0, 0 }
};

static const luaL_reg WidgetFuncs[] = {
	{ "Destroy", WidgetDestroy },
	{ "SetTag", WidgetSetTag },
	{ "GetTag", WidgetGetTag },
	{ "Untag", WidgetUntag },
	{ "SetXY", WidgetSetXY },
	{ "SetWH", WidgetSetWH },
	{ "GetXYWH", WidgetGetXYWH },
	{ "SetDraw", WidgetSetDraw },
	{ "SetHitTest", WidgetSetHitTest },
	{ "SetProcessEvent", WidgetSetProcessEvent },
	{ "SignalCursorOver", WidgetSignalCursorOver },
	{ "IsGrabbed", WidgetIsGrabbed },
	{ "IsEntered", WidgetIsEntered },
	{ "IsTagged", WidgetIsTagged },
	{ "IsLoaded", WidgetIsLoaded },
	{ "IsValid ", WidgetIsValid },
	{ 0, 0 }
};

///
/// Constant tables
///
static const struct {
	char const * mName;	///< Name attached to constant
	WidgetEventType mEvent;	///< Event value constant
} WidgetEvents[] = {
	{ "WidgetGrab", eWidgetEvent_Grab },
	{ "WidgetDrop", eWidgetEvent_Drop },
	{ "WidgetEnter", eWidgetEvent_Enter },
	{ "WidgetLeave", eWidgetEvent_Leave },
	{ "PaneCatch", ePaneEvent_Catch },
	{ "PaneRelease", ePaneEvent_Release },
	{ "PaneDrag", ePaneEvent_Drag },
	{ "ButtonPush", eButtonEvent_Push },
	{ "ButtonRelease", eButtonEvent_Release },
	{ "CheckboxCheck", eCheckboxEvent_Check },
	{ "CheckboxUncheck", eCheckboxEvent_Uncheck },
	{ "ListboxGrabItem", eListboxEvent_GrabItem },
	{ "ListboxDropItem", eListboxEvent_DropItem },
	{ "ListboxEnterItem", eListboxEvent_EnterItem },
	{ "ListboxLeaveItem", eListboxEvent_LeaveItem },
	{ "ListboxDragOver", eListboxEvent_DragOver },
	{ "RadioboxGrabOption", eRadioboxEvent_GrabOption },
	{ "RadioboxDropOption", eRadioboxEvent_DropOption },
	{ "RadioboxEnterOption", eRadioboxEvent_EnterOption },
	{ "RadioboxLeaveOption", eRadioboxEvent_LeaveOption },
	{ "SliderGrabThumb", eSliderEvent_GrabThumb },
	{ "SliderDropThumb", eSliderEvent_DropThumb },
	{ "SliderEnterThumb", eSliderEvent_EnterThumb },
	{ "SliderLeaveThumb", eSliderEvent_LeaveThumb },
	{ "SliderSnapThumb", eSliderEvent_SnapThumb },
	{ "SliderCatchThumb", eSliderEvent_CatchThumb },
	{ "SliderReleaseThumb", eSliderEvent_ReleaseThumb },
	{ "SliderDragThumb", eSliderEvent_DragThumb },
	{ "TextboxGrabSpot", eTextboxEvent_GrabSpot },
	{ "TextboxDropSpot", eTextboxEvent_DropSpot },
	{ "TextboxDragOver", eTextboxEvent_DragOver }
};

/// @brief Binds the UI system to the LUA scripting system
void BindUI (lua_State * L)
{
	///////////////////////////////////////////////////////////////////////
	// We install tables for each of the components of the user interface.
	///////////////////////////////////////////////////////////////////////
	luaL_openlib(L, "Button", ButtonFuncs, 0);
	luaL_openlib(L, "Checkbox", CheckboxFuncs, 0);
	luaL_openlib(L, "Listbox", ListboxFuncs, 0);
	luaL_openlib(L, "Pane", PaneFuncs, 0);
	luaL_openlib(L, "PaneItem", PaneItemFuncs, 0);
	luaL_openlib(L, "PaneLayer", PaneLayerFuncs, 0);
	luaL_openlib(L, "Radiobox", RadioboxFuncs, 0);
	luaL_openlib(L, "Slider", SliderFuncs, 0);
	luaL_openlib(L, "Textbox", TextboxFuncs, 0);
	luaL_openlib(L, "UI", UIFuncs, 0);
	luaL_openlib(L, "Widget", WidgetFuncs, 0);

	////////////////////////////////////////////////////////////////////
	// We now install the widget event constants into the widget table.
	////////////////////////////////////////////////////////////////////
	for (Uint32 index = 0; index < sizeof(WidgetEvents) / sizeof(WidgetEvents[0]); ++index)
	{
		lua_pushstring(L, WidgetEvents[index].mName);
		lua_pushnumber(L, WidgetEvents[index].mEvent);

		lua_settable(L, -3);
	}
}