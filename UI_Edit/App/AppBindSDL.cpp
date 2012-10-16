/*
** Lua binding: SDL
** Generated automatically by tolua 5.0a on 03/05/04 14:31:36.
*/
#include <SDL/SDL.h>
#include <tolua.h>
#include "AppGeneral.h"

SDL_Event Event;	SDL_Event *	SDL_Event_get (void) { return &Event; }

Uint8 U8Buffer[2][128];

int U8Buffer_Load (lua_State * L)
{
	Uint8 * pBuffer = U8Buffer[U(L, 1) - 1];

	int count = lua_gettop(L);

	for (int index = 2; index <= count; ++index) pBuffer[index - 2] = U8(L, index);

	lua_pushlightuserdata(L, pBuffer);

	return 1;
}

#undef SDL_SaveBMP
int SDL_SaveBMP(SDL_Surface* surface, const char* file)
{
	return SDL_SaveBMP_RW(surface, SDL_RWFromFile(file, "wb"), 1);
}

#undef SDL_LoadBMP
SDL_Surface* SDL_LoadBMP(const char* file)
{
	return SDL_LoadBMP_RW(SDL_RWFromFile(file, "rb"), 1);
}

SDL_Rect Rect;	SDL_Rect * SDL_Rect_get (void) { return &Rect; }

/* function to register type */
static void tolua_reg_types  (lua_State * L)
{
	tolua_usertype(L, "Color");
	tolua_usertype(L, "JoyHatEvent");
	tolua_usertype(L, "Joystick");
	tolua_usertype(L, "ResizeEvent");
	tolua_usertype(L, "Palette");
	tolua_usertype(L, "FILE");
	tolua_usertype(L, "RWops");
	tolua_usertype(L, "keysym");
	tolua_usertype(L, "SysWMEvent");
	tolua_usertype(L, "ActiveEvent");
	tolua_usertype(L, "VideoInfo");
	tolua_usertype(L, "Cursor");
	tolua_usertype(L, "Rect");
	tolua_usertype(L, "PixelFormat");
	tolua_usertype(L, "Surface");
	tolua_usertype(L, "JoyButtonEvent");
	tolua_usertype(L, "JoyAxisEvent");
	tolua_usertype(L, "KeyboardEvent");
	tolua_usertype(L, "Event");
	tolua_usertype(L, "MouseMotionEvent");
	tolua_usertype(L, "ExposeEvent");
	tolua_usertype(L, "QuitEvent");
	tolua_usertype(L, "JoyBallEvent");
	tolua_usertype(L, "MouseButtonEvent");
	tolua_usertype(L, "WMcursor");
	tolua_usertype(L, "UserEvent");
	tolua_usertype(L, "Overlay");
}

/* function: bit_test */
static int LDL_SDL_bit_test00 (lua_State * L)
{
	int test = I(L, 2);

	lua_pushboolean(L, (I(L, 1) & test) == test);

	return 1;
}

/* function: bit_or */
static int LDL_SDL_bit_or00 (lua_State * L)
{
	lua_pushnumber(L, I(L, 1) | I(L, 2));

	return 1;
}

/* function: bit_and */
static int LDL_SDL_bit_and00 (lua_State * L)
{
	lua_pushnumber(L, I(L, 1) & I(L, 2));

	return 1;
}

/* function: bit_not */
static int LDL_SDL_bit_not00 (lua_State * L)
{
	lua_pushnumber(L, ~I(L, 1));

	return 1;
}

/* function: bit_xor */
static int LDL_SDL_bit_xor00 (lua_State * L)
{
	lua_pushnumber(L, I(L, 1) ^ I(L, 2));

	return 1;
}

/* function: SDL_GetError */
static int LDL_SDL_SDL_GetError00 (lua_State * L)
{
	lua_pushstring(L, SDL_GetError());

	return 1;
}

/* function: SDL_ClearError */
static int LDL_SDL_SDL_ClearError00 (lua_State * L)
{
	SDL_ClearError();
	
	return 0;
}

/* function: SDL_GetTicks */
static int LDL_SDL_SDL_GetTicks00 (lua_State * L)
{
	lua_pushnumber(L, SDL_GetTicks());

	return 1;
}

/* function: SDL_Delay */
static int LDL_SDL_SDL_Delay00 (lua_State * L)
{
	SDL_Delay(U(L, 1));

	return 0;
}

/* function: SDL_NumJoysticks */
static int LDL_SDL_SDL_NumJoysticks00 (lua_State * L)
{
	lua_pushnumber(L, SDL_NumJoysticks());

	return 1;
}

/* function: SDL_JoystickName */
static int LDL_SDL_SDL_JoystickName00 (lua_State * L)
{
	lua_pushstring(L, SDL_JoystickName(I(L, 1)));

	return 1;
}

/* function: SDL_JoystickOpen */
static int LDL_SDL_SDL_JoystickOpen00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_JoystickOpen(I(L, 1)), "Joystick");

	return 1;
}

/* function: SDL_JoystickOpened */
static int LDL_SDL_SDL_JoystickOpened00 (lua_State * L)
{
	lua_pushnumber(L, SDL_JoystickOpened(I(L, 1)));

	return 1;
}

/* function: SDL_JoystickIndex */
static int LDL_SDL_SDL_JoystickIndex00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickIndex(joystick));

	return 1;
}

/* function: SDL_JoystickNumAxes */
static int LDL_SDL_SDL_JoystickNumAxes00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickNumAxes(joystick));

	return 1;
}

/* function: SDL_JoystickNumBalls */
static int LDL_SDL_SDL_JoystickNumBalls00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickNumBalls(joystick));

	return 1;
}

/* function: SDL_JoystickNumHats */
static int LDL_SDL_SDL_JoystickNumHats00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickNumHats(joystick));

	return 1;
}

/* function: SDL_JoystickNumButtons */
static int LDL_SDL_SDL_JoystickNumButtons00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickNumButtons(joystick));

	return 1;
}

/* function: SDL_JoystickUpdate */
static int LDL_SDL_SDL_JoystickUpdate00 (lua_State * L)
{
	SDL_JoystickUpdate();

	return 0;
}

/* function: SDL_JoystickEventState */
static int LDL_SDL_SDL_JoystickEventState00 (lua_State * L)
{
	lua_pushnumber(L, SDL_JoystickEventState(I(L, 1)));

	return 1;
}

/* function: SDL_JoystickGetAxis */
static int LDL_SDL_SDL_JoystickGetAxis00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickGetAxis(joystick, I(L, 2)));

	return 1;
}

/* function: SDL_JoystickGetHat */
static int LDL_SDL_SDL_JoystickGetHat00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickGetHat(joystick, I(L, 2)));

	return 1;
}

/* function: SDL_JoystickGetBall */
static int LDL_SDL_SDL_JoystickGetBall00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	int dx = I(L, 3), dy = I(L, 4);

	lua_pushnumber(L, SDL_JoystickGetBall(joystick, I(L, 2), &dx, &dy));
	lua_pushnumber(L, dx);
	lua_pushnumber(L, dy);

	return 3;
}

/* function: SDL_JoystickGetButton */
static int LDL_SDL_SDL_JoystickGetButton00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_JoystickGetButton(joystick, I(L, 2)));

	return 1;
}

/* function: SDL_JoystickClose */
static int LDL_SDL_SDL_JoystickClose00 (lua_State * L)
{
	SDL_Joystick * joystick = static_cast<SDL_Joystick*>(tolua_tousertype(L, 1, 0));

	SDL_JoystickClose(joystick);

	return 0;
}

/* get function: scancode of class  SDL_keysym */
/* get function: scancode of class  SDL_keysym */
static int tolua_get_SDL_scancode (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->scancode);

	return 1;
}

/* set function: scancode of class  SDL_keysym */
static int Let_SDL_keysym_SDL_scancode (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	self->scancode = U8(L, 2);

	return 0;
}

/* get function: sym of class  SDL_keysym */
/* get function: sym of class  SDL_keysym */
static int tolua_get_SDL_sym (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->sym);

	return 1;
}

/* set function: sym of class  SDL_keysym */
static int Let_SDL_keysym_SDL_sym (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	self->sym = static_cast<SDLKey>(I(L, 2));

	return 0;
}

/* get function: mod of class  SDL_keysym */
/* get function: mod of class  SDL_keysym */
static int tolua_get_SDL_mod (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->mod);

	return 1;
}

/* set function: mod of class  SDL_keysym */
static int Let_SDL_keysym_SDL_mod (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	self->mod = static_cast<SDLMod>(I(L, 2));

	return 0;
}

/* get function: unicode of class  SDL_keysym */
/* get function: unicode of class  SDL_keysym */
static int tolua_get_SDL_unicode (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->unicode);

	return 1;
}

/* set function: unicode of class  SDL_keysym */
static int Let_SDL_keysym_SDL_unicode (lua_State * L)
{
	SDL_keysym * self = static_cast<SDL_keysym*>(tolua_tousertype(L, 1, 0));

	self->unicode = U16(L, 2);

	return 0;
}

/* function: SDL_EnableUNICODE */
static int LDL_SDL_SDL_EnableUNICODE00 (lua_State * L)
{
	lua_pushnumber(L, SDL_EnableUNICODE(I(L, 1)));

	return 1;
}

/* function: SDL_EnableKeyRepeat */
static int LDL_SDL_SDL_EnableKeyRepeat00 (lua_State * L)
{
	lua_pushnumber(L, SDL_EnableKeyRepeat(I(L, 1), I(L, 2)));

	return 1;
}

/* function: SDL_GetModState */
static int LDL_SDL_SDL_GetModState00 (lua_State * L)
{
	lua_pushnumber(L, SDL_GetModState());

	return 1;
}

/* function: SDL_SetModState */
static int LDL_SDL_SDL_SetModState00 (lua_State * L)
{
	SDL_SetModState(static_cast<SDLMod>(I(L, 1)));

	return 0;
}

/* function: SDL_GetKeyName */
static int LDL_SDL_SDL_GetKeyName00 (lua_State * L)
{
	lua_pushstring(L, SDL_GetKeyName(static_cast<SDLKey>(I(L, 1))));

	return 1;
}

/* function: SDL_GetMouseState */
static int LDL_SDL_SDL_GetMouseState00 (lua_State * L)
{
	int x = I(L, 1);
	int y = I(L, 2);

	lua_pushnumber(L, SDL_GetMouseState(&x, &y));
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	return 3;
}

/* function: SDL_GetRelativeMouseState */
static int LDL_SDL_SDL_GetRelativeMouseState00 (lua_State * L)
{
	int x = I(L, 1);
	int y = I(L, 2);

	lua_pushnumber(L, SDL_GetRelativeMouseState(&x, &y));
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	return 3;
}

/* function: SDL_WarpMouse */
static int LDL_SDL_SDL_WarpMouse00 (lua_State * L)
{
	SDL_WarpMouse(U16(L, 1), U16(L, 2));

	return 0;
}

/* function: SDL_CreateCursor */
static int LDL_SDL_SDL_CreateCursor00 (lua_State * L)
{
	Uint8 * data = static_cast<Uint8*>(UD(L, 1));
	Uint8 * mask = static_cast<Uint8*>(UD(L, 2));
 
	tolua_pushusertype(L, SDL_CreateCursor(data, mask, I(L, 3), I(L, 4), I(L, 5), I(L, 6)), "Cursor");

	return 1;
}

/* function: SDL_SetCursor */
static int LDL_SDL_SDL_SetCursor00 (lua_State * L)
{
	SDL_Cursor * cursor = static_cast<SDL_Cursor*>(tolua_tousertype(L, 1, 0));

	SDL_SetCursor(cursor);

	return 0;
}

/* function: SDL_GetCursor */
static int LDL_SDL_SDL_GetCursor00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_GetCursor(), "Cursor");

	return 1;
}

/* function: SDL_FreeCursor */
static int LDL_SDL_SDL_FreeCursor00 (lua_State * L)
{
	SDL_Cursor* cursor = static_cast<SDL_Cursor*>(tolua_tousertype(L, 1, 0));

	SDL_FreeCursor(cursor);

	return 0;
}

/* function: SDL_ShowCursor */
static int LDL_SDL_SDL_ShowCursor00 (lua_State * L)
{
	lua_pushnumber(L, SDL_ShowCursor(I(L, 1)));

	return 1;
}

/* get function: type of class  SDL_ActiveEvent */
static int tolua_get_SDL_type_Active (lua_State * L)
{
	SDL_ActiveEvent * self = static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_ActiveEvent */
static int Let_SDL_ActiveEvent_SDL_type (lua_State * L)
{
	SDL_ActiveEvent * self = static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: gain of class  SDL_ActiveEvent */
static int tolua_get_SDL_gain (lua_State * L)
{
	SDL_ActiveEvent * self = static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->gain);

	return 1;
}

/* set function: gain of class  SDL_ActiveEvent */
static int Let_SDL_ActiveEvent_SDL_gain (lua_State * L)
{
	SDL_ActiveEvent * self = static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 1, 0));

	self->gain = U8(L, 2);

	return 0;
}

/* get function: state of class  SDL_ActiveEvent */
static int tolua_get_SDL_state_Active (lua_State * L)
{
	SDL_ActiveEvent * self = static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->state);

	return 1;
}

/* set function: state of class  SDL_ActiveEvent */
static int Let_SDL_ActiveEvent_SDL_state (lua_State * L)
{
	SDL_ActiveEvent * self = static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 1, 0));

	self->state = U8(L, 2);

	return 0;
}

/* get function: type of class  SDL_KeyboardEvent */
static int tolua_get_SDL_type_Keyboard (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_KeyboardEvent */
static int Let_SDL_KeyboardEvent_SDL_type (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_KeyboardEvent */
static int tolua_get_SDL_which (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_KeyboardEvent */
static int Let_SDL_KeyboardEvent_SDL_which (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: state of class  SDL_KeyboardEvent */
static int tolua_get_SDL_state_Keyboard (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->state);

	return 1;
}

/* set function: state of class  SDL_KeyboardEvent */
static int Let_SDL_KeyboardEvent_SDL_state (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	self->state = U8(L, 2);

	return 0;
}

/* get function: keysym of class  SDL_KeyboardEvent */
static int tolua_get_SDL_keysym (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->keysym, "keysym");

	return 1;
}

/* set function: keysym of class  SDL_KeyboardEvent */
static int Let_SDL_KeyboardEvent_SDL_keysym (lua_State * L)
{
	SDL_KeyboardEvent * self = static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 1, 0));

	self->keysym = *static_cast<SDL_keysym*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: type of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_type_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_type (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_which_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_which (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: state of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_state_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->state);

	return 1;
}

/* set function: state of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_state (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->state = U8(L, 2);

	return 0;
}

/* get function: x of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_x_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->x);

	return 1;
}

/* set function: x of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_x (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->x = U16(L, 2);

	return 0;
}

/* get function: y of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_y_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	tolua_pushnumber(L, self->y);

	return 1;
}

/* set function: y of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_y (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->y = U16(L, 2);

	return 0;
}

/* get function: xrel of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_xrel_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->xrel);

	return 1;
}

/* set function: xrel of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_xrel (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->xrel = S16(L, 2);

	return 0;
}

/* get function: yrel of class  SDL_MouseMotionEvent */
static int tolua_get_SDL_yrel_MouseMotion (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->yrel);

	return 1;
}

/* set function: yrel of class  SDL_MouseMotionEvent */
static int Let_SDL_MouseMotionEvent_SDL_yrel (lua_State * L)
{
	SDL_MouseMotionEvent * self = static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 1, 0));

	self->yrel = S16(L, 2);

	return 0;
}

/* get function: type of class  SDL_MouseButtonEvent */
static int tolua_get_SDL_type_MouseButton (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_MouseButtonEvent */
static int Let_SDL_MouseButtonEvent_SDL_type (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_MouseButtonEvent */
static int tolua_get_SDL_which_MouseButton (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_MouseButtonEvent */
static int Let_SDL_MouseButtonEvent_SDL_which (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: button of class  SDL_MouseButtonEvent */
static int tolua_get_SDL_button_MouseButton (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->button);

	return 1;
}

/* set function: button of class  SDL_MouseButtonEvent */
static int Let_SDL_MouseButtonEvent_SDL_button (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->button = U8(L, 2);

	return 0;
}

/* get function: state of class  SDL_MouseButtonEvent */
static int tolua_get_SDL_state_MouseButton (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->state);

	return 1;
}

/* set function: state of class  SDL_MouseButtonEvent */
static int Let_SDL_MouseButtonEvent_SDL_state (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->state = U8(L, 2);

	return 0;
}

/* get function: x of class  SDL_MouseButtonEvent */
static int tolua_get_SDL_x_MouseButton (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->x);

	return 1;
}

/* set function: x of class  SDL_MouseButtonEvent */
static int Let_SDL_MouseButtonEvent_SDL_x (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->x = U16(L, 2);

	return 0;
}

/* get function: y of class  SDL_MouseButtonEvent */
static int tolua_get_SDL_y_MouseButton (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->y);

	return 1;
}

/* set function: y of class  SDL_MouseButtonEvent */
static int Let_SDL_MouseButtonEvent_SDL_y (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->y = U16(L, 2);

	return 0;
}

/* get function: type of class  SDL_JoyAxisEvent */
static int tolua_get_SDL_type_JoyAxis (lua_State * L)
{
	SDL_MouseButtonEvent * self = static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_JoyAxisEvent */
static int Let_SDL_JoyAxisEvent_SDL_type (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_JoyAxisEvent */
static int tolua_get_SDL_which_JoyAxis (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_JoyAxisEvent */
static int Let_SDL_JoyAxisEvent_SDL_which (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: axis of class  SDL_JoyAxisEvent */
static int tolua_get_SDL_axis (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->axis);

	return 1;
}

/* set function: axis of class  SDL_JoyAxisEvent */
static int Let_SDL_JoyAxisEvent_SDL_axis (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	self->axis = U8(L, 2);

	return 0;
}

/* get function: value of class  SDL_JoyAxisEvent */
static int tolua_get_SDL_value_JoyAxis (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->value);

	return 1;
}

/* set function: value of class  SDL_JoyAxisEvent */
static int Let_SDL_JoyAxisEvent_SDL_value (lua_State * L)
{
	SDL_JoyAxisEvent * self = static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 1, 0));

	self->value = S16(L, 2);

	return 0;
}

/* get function: type of class  SDL_JoyBallEvent */
static int tolua_get_SDL_type_JoyBall (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_JoyBallEvent */
static int Let_SDL_JoyBallEvent_SDL_type (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_JoyBallEvent */
static int tolua_get_SDL_which_JoyBall (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_JoyBallEvent */
static int Let_SDL_JoyBallEvent_SDL_which (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: ball of class  SDL_JoyBallEvent */
static int tolua_get_SDL_ball (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->ball);

	return 1;
}

/* set function: ball of class  SDL_JoyBallEvent */
static int Let_SDL_JoyBallEvent_SDL_ball (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	self->ball = U8(L, 2);

	return 0;
}

/* get function: xrel of class  SDL_JoyBallEvent */
static int tolua_get_SDL_xrel_JoyBall (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->xrel);

	return 1;
}

/* set function: xrel of class  SDL_JoyBallEvent */
static int Let_SDL_JoyBallEvent_SDL_xrel (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	self->xrel = S16(L, 2);

	return 0;
}

/* get function: yrel of class  SDL_JoyBallEvent */
static int tolua_get_SDL_yrel_JoyBall (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->yrel);

	return 1;
}

/* set function: yrel of class  SDL_JoyBallEvent */
static int Let_SDL_JoyBallEvent_SDL_yrel (lua_State * L)
{
	SDL_JoyBallEvent * self = static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 1, 0));

	self->yrel = S16(L, 2);

	return 0;
}

/* get function: type of class  SDL_JoyHatEvent */
static int tolua_get_SDL_type_JoyHat (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_JoyHatEvent */
static int Let_SDL_JoyHatEvent_SDL_type (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_JoyHatEvent */
static int tolua_get_SDL_which_JoyHat (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_JoyHatEvent */
static int Let_SDL_JoyHatEvent_SDL_which (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: hat of class  SDL_JoyHatEvent */
static int tolua_get_SDL_hat (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->hat);

	return 1;
}

/* set function: hat of class  SDL_JoyHatEvent */
static int Let_SDL_JoyHatEvent_SDL_hat (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	self->hat = U8(L, 2);

	return 0;
}

/* get function: value of class  SDL_JoyHatEvent */
static int tolua_get_SDL_value_JoyHat (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->value);

	return 1;
}

/* set function: value of class  SDL_JoyHatEvent */
static int Let_SDL_JoyHatEvent_SDL_value (lua_State * L)
{
	SDL_JoyHatEvent * self = static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 1, 0));

	self->value = U8(L, 2);

	return 0;
}

/* get function: type of class  SDL_JoyButtonEvent */
static int tolua_get_SDL_type_JoyButton (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_JoyButtonEvent */
static int Let_SDL_JoyButtonEvent_SDL_type (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: which of class  SDL_JoyButtonEvent */
static int tolua_get_SDL_which_JoyButton (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->which);

	return 1;
}

/* set function: which of class  SDL_JoyButtonEvent */
static int Let_SDL_JoyButtonEvent_SDL_which (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->which = U8(L, 2);

	return 0;
}

/* get function: button of class  SDL_JoyButtonEvent */
static int tolua_get_SDL_button_JoyButton (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->button);

	return 1;
}

/* set function: button of class  SDL_JoyButtonEvent */
static int Let_SDL_JoyButtonEvent_SDL_button (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->button = U8(L, 2);

	return 0;
}

/* get function: state of class  SDL_JoyButtonEvent */
static int tolua_get_SDL_state_JoyButton (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->state);

	return 1;
}

/* set function: state of class  SDL_JoyButtonEvent */
static int Let_SDL_JoyButtonEvent_SDL_state (lua_State * L)
{
	SDL_JoyButtonEvent * self = static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 1, 0));

	self->state = U8(L, 2);

	return 0;
}

/* get function: type of class  SDL_ResizeEvent */
static int tolua_get_SDL_type_Resize (lua_State * L)
{
	SDL_ResizeEvent * self = static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_ResizeEvent */
static int Let_SDL_ResizeEvent_SDL_type (lua_State * L)
{
	SDL_ResizeEvent * self = static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: w of class  SDL_ResizeEvent */
static int tolua_get_SDL_w_Resize (lua_State * L)
{
	SDL_ResizeEvent * self = static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->w);

	return 1;
}

/* set function: w of class  SDL_ResizeEvent */
static int Let_SDL_ResizeEvent_SDL_w (lua_State * L)
{
	SDL_ResizeEvent * self = static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 1, 0));

	self->w = I(L, 2);

	return 0;
}

/* get function: h of class  SDL_ResizeEvent */
static int tolua_get_SDL_h_Resize (lua_State * L)
{
	SDL_ResizeEvent * self = static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->h);

	return 1;
}

/* set function: h of class  SDL_ResizeEvent */
static int Let_SDL_ResizeEvent_SDL_h (lua_State * L)
{
	SDL_ResizeEvent * self = static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 1, 0));

	self->h = I(L, 2);

	return 0;
}

/* get function: type of class  SDL_ExposeEvent */
static int tolua_get_SDL_type_Expose (lua_State * L)
{
	SDL_ExposeEvent * self = static_cast<SDL_ExposeEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_ExposeEvent */
static int Let_SDL_ExposeEvent_SDL_type (lua_State * L)
{
	SDL_ExposeEvent * self = static_cast<SDL_ExposeEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: type of class  SDL_QuitEvent */
static int tolua_get_SDL_type_Quit (lua_State * L)
{
	SDL_QuitEvent * self = static_cast<SDL_QuitEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_QuitEvent */
static int Let_SDL_QuitEvent_SDL_type (lua_State * L)
{
	SDL_QuitEvent * self = static_cast<SDL_QuitEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: type of class  SDL_UserEvent */
static int tolua_get_SDL_type_User (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_UserEvent */
static int Let_SDL_UserEvent_SDL_type (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: code of class  SDL_UserEvent */
static int tolua_get_SDL_code (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->code);

	return 1;
}

/* set function: code of class  SDL_UserEvent */
static int Let_SDL_UserEvent_SDL_code (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	self->code = I(L, 2);

	return 0;
}

/* get function: data1 of class  SDL_UserEvent */
static int tolua_get_SDL_data1 (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushlightuserdata(L, self->data1);

	return 1;
}

/* set function: data1 of class  SDL_UserEvent */
static int Let_SDL_UserEvent_SDL_data1 (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	self->data1 = UD(L, 2);

	return 0;
}

/* get function: data2 of class  SDL_UserEvent */
static int tolua_get_SDL_data2 (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	lua_pushlightuserdata(L, self->data2);

	return 1;
}

/* set function: data2 of class  SDL_UserEvent */
static int Let_SDL_UserEvent_SDL_data2 (lua_State * L)
{
	SDL_UserEvent * self = static_cast<SDL_UserEvent*>(tolua_tousertype(L, 1, 0));

	self->data2 = UD(L, 2);

	return 0;
}

/* get function: type of class  SDL_Event */
static int tolua_get_SDL_type_Event (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->type);

	return 1;
}

/* set function: type of class  SDL_Event */
static int Let_SDL_Event_SDL_type (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->type = U8(L, 2);

	return 0;
}

/* get function: active of class  SDL_Event */
static int tolua_get_SDL_active (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->active, "ActiveEvent");

	return 1;
}

/* set function: active of class  SDL_Event */
static int Let_SDL_Event_SDL_active (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->active = *static_cast<SDL_ActiveEvent*>(tolua_tousertype(L, 2, 0));

	return 0;
}

/* get function: key of class  SDL_Event */
static int tolua_get_SDL_key (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->key, "KeyboardEvent");

	return 1;
}

/* set function: key of class  SDL_Event */
static int Let_SDL_Event_SDL_key (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->key = *static_cast<SDL_KeyboardEvent*>(tolua_tousertype(L, 2, 0));

	return 0;
}

/* get function: motion of class  SDL_Event */
static int tolua_get_SDL_motion (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->motion, "MouseMotionEvent");

	return 1;
}

/* set function: motion of class  SDL_Event */
static int Let_SDL_Event_SDL_motion (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->motion = *static_cast<SDL_MouseMotionEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: button of class  SDL_Event */
static int tolua_get_SDL_button (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->button, "MouseButtonEvent");

	return 1;
}

/* set function: button of class  SDL_Event */
static int Let_SDL_Event_SDL_button (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->button = *static_cast<SDL_MouseButtonEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: jaxis of class  SDL_Event */
static int tolua_get_SDL_jaxis (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, (void*)&self->jaxis, "JoyAxisEvent");

	return 1;
}

/* set function: jaxis of class  SDL_Event */
static int Let_SDL_Event_SDL_jaxis (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->jaxis = *static_cast<SDL_JoyAxisEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: jball of class  SDL_Event */
static int tolua_get_SDL_jball (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->jball, "JoyBallEvent");

	return 1;
}

/* set function: jball of class  SDL_Event */
static int Let_SDL_Event_SDL_jball (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->jball = *static_cast<SDL_JoyBallEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: jhat of class  SDL_Event */
static int tolua_get_SDL_jhat (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->jhat, "JoyHatEvent");

	return 1;
}

/* set function: jhat of class  SDL_Event */
static int Let_SDL_Event_SDL_jhat (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->jhat = *static_cast<SDL_JoyHatEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: jbutton of class  SDL_Event */
static int tolua_get_SDL_jbutton (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->jbutton, "JoyButtonEvent");

	return 1;
}

/* set function: jbutton of class  SDL_Event */
static int Let_SDL_Event_SDL_jbutton (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->jbutton = *static_cast<SDL_JoyButtonEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: resize of class  SDL_Event */
static int tolua_get_SDL_resize (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->resize, "ResizeEvent");

	return 1;
}

/* set function: resize of class  SDL_Event */
static int Let_SDL_Event_SDL_resize (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->resize = *static_cast<SDL_ResizeEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: expose of class  SDL_Event */
static int tolua_get_SDL_expose (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->expose, "ExposeEvent");

	return 1;
}

/* set function: expose of class  SDL_Event */
static int Let_SDL_Event_SDL_expose (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->expose = *static_cast<SDL_ExposeEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: quit of class  SDL_Event */
static int tolua_get_SDL_quit (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->quit, "QuitEvent");

	return 1;
}

/* set function: quit of class  SDL_Event */
static int Let_SDL_Event_SDL_quit (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->quit = *static_cast<SDL_QuitEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: user of class  SDL_Event */
static int tolua_get_SDL_user (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->user, "UserEvent");

	return 1;
}

/* set function: user of class  SDL_Event */
static int Let_SDL_Event_SDL_user (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->user = *static_cast<SDL_UserEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: syswm of class  SDL_Event */
static int tolua_get_SDL_syswm (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, &self->syswm, "SysWMEvent");

	return 1;
}

/* set function: syswm of class  SDL_Event */
static int Let_SDL_Event_SDL_syswm (lua_State * L)
{
	SDL_Event * self = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	self->syswm = *static_cast<SDL_SysWMEvent*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* function: SDL_Event_new */
static int LDL_SDL_SDL_Event_get00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_Event_get(), "Event");

	return 1;
}

/* function: SDL_PumpEvents */
static int LDL_SDL_SDL_PumpEvents00 (lua_State * L)
{
	SDL_PumpEvents();

	return 0;
}

/* function: SDL_PeepEvents */
static int LDL_SDL_SDL_PeepEvents00 (lua_State * L)
{
	SDL_Event * events = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_PeepEvents(events, I(L, 2), static_cast<SDL_eventaction>(I(L, 3)), U(L, 4)));

	return 1;
}

/* function: SDL_PollEvent */
static int LDL_SDL_SDL_PollEvent00 (lua_State * L)
{
	SDL_Event * event = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_PollEvent(event));

	return 1;
}

/* function: SDL_WaitEvent */
static int LDL_SDL_SDL_WaitEvent00 (lua_State * L)
{
	SDL_Event * event = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_WaitEvent(event));

	return 1;
}

/* function: SDL_PushEvent */
static int LDL_SDL_SDL_PushEvent00 (lua_State * L)
{
	SDL_Event * event = static_cast<SDL_Event*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_PushEvent(event));

	return 1;
}

/* get function: x of class  SDL_Rect */
static int tolua_get_SDL_x_Rect (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->x);

	return 1;
}

/* set function: x of class  SDL_Rect */
static int Let_SDL_Rect_SDL_x (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	self->x = S16(L, 2);

	return 0;
}

/* get function: y of class  SDL_Rect */
static int tolua_get_SDL_y_Rect (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->y);

	return 1;
}

/* set function: y of class  SDL_Rect */
static int Let_SDL_Rect_SDL_y (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	self->y = S16(L, 2);

	return 0;
}

/* get function: w of class  SDL_Rect */
static int tolua_get_SDL_w_Rect (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->w);

	return 1;
}

/* set function: w of class  SDL_Rect */
static int Let_SDL_Rect_SDL_w (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	self->w = U16(L, 2);

	return 0;
}

/* get function: h of class  SDL_Rect */
static int tolua_get_SDL_h_Rect (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->h);

	return 1;
}

/* set function: h of class  SDL_Rect */
static int Let_SDL_Rect_SDL_h (lua_State * L)
{
	SDL_Rect * self = static_cast<SDL_Rect*>(tolua_tousertype(L, 1, 0));

	self->h = U16(L, 2);

	return 0;
}

/* function: SDL_Rect_get */
static int LDL_SDL_SDL_Rect_get00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_Rect_get(), "Rect");

	return 1;
}

/* get function: r of class  SDL_Color */
static int tolua_get_SDL_r (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	tolua_pushnumber(L, self->r);

	return 1;
}

/* set function: r of class  SDL_Color */
static int Let_SDL_Color_SDL_r (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	self->r = U8(L, 2);

	return 0;
}

/* get function: g of class  SDL_Color */
static int tolua_get_SDL_g (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->g);

	return 1;
}

/* set function: g of class  SDL_Color */
static int Let_SDL_Color_SDL_g (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	self->g = U8(L, 2);

	return 0;
}

/* get function: b of class  SDL_Color */
static int tolua_get_SDL_b (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->b);

	return 1;
}

/* set function: b of class  SDL_Color */
static int Let_SDL_Color_SDL_b (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	self->b = U8(L, 2);

	return 0;
}

/* get function: unused of class  SDL_Color */
static int tolua_get_SDL_unused (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->unused);

	return 1;
}

/* set function: unused of class  SDL_Color */
static int Let_SDL_Color_SDL_unused (lua_State * L)
{
	SDL_Color * self = static_cast<SDL_Color*>(tolua_tousertype(L, 1, 0));

	self->unused = U8(L, 2);

	return 0;
}

/* get function: ncolors of class  SDL_Palette */
static int tolua_get_SDL_ncolors (lua_State * L)
{
	SDL_Palette * self = static_cast<SDL_Palette*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->ncolors);

	return 1;
}

/* set function: ncolors of class  SDL_Palette */
static int Let_SDL_Palette_SDL_ncolors (lua_State * L)
{
	SDL_Palette * self = static_cast<SDL_Palette*>(tolua_tousertype(L, 1, 0));

	self->ncolors = I(L, 2);

	return 0;
}

/* get function: colors of class  SDL_Palette */
static int tolua_get_SDL_colors_ptr (lua_State * L)
{
	SDL_Palette * self = static_cast<SDL_Palette*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, self->colors, "Color");

	return 1;
}

/* set function: colors of class  SDL_Palette */
static int Let_SDL_Palette_SDL_colors_ptr (lua_State * L)
{
	SDL_Palette * self = static_cast<SDL_Palette*>(tolua_tousertype(L, 1, 0));

	self->colors = static_cast<SDL_Color*>(tolua_tousertype(L, 2, 0));

	return 0;
}

/* get function: palette of class  SDL_PixelFormat */
static int tolua_get_SDL_palette_ptr (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, self->palette, "Palette");

	return 1;
}

/* set function: palette of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_palette_ptr (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->palette = static_cast<SDL_Palette*>(tolua_tousertype(L, 2,0));

	return 0;
}

/* get function: BitsPerPixel of class  SDL_PixelFormat */
static int tolua_get_SDL_BitsPerPixel (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->BitsPerPixel);

	return 1;
}

/* set function: BitsPerPixel of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_BitsPerPixel (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->BitsPerPixel = U8(L, 2);

	return 0;
}

/* get function: BytesPerPixel of class  SDL_PixelFormat */
static int tolua_get_SDL_BytesPerPixel (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->BytesPerPixel);

	return 1;
}

/* set function: BytesPerPixel of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_BytesPerPixel (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->BytesPerPixel = U8(L, 2);

	return 0;
}

/* get function: Rloss of class  SDL_PixelFormat */
static int tolua_get_SDL_Rloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Rloss);

	return 1;
}

/* set function: Rloss of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Rloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Rloss = U8(L, 2);

	return 0;
}

/* get function: Gloss of class  SDL_PixelFormat */
static int tolua_get_SDL_Gloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Gloss);

	return 1;
}

/* set function: Gloss of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Gloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Gloss = U8(L, 2);

	return 0;
}

/* get function: Bloss of class  SDL_PixelFormat */
static int tolua_get_SDL_Bloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Bloss);

	return 1;
}

/* set function: Bloss of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Bloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Bloss = U8(L, 2);

	return 0;
}

/* get function: Aloss of class  SDL_PixelFormat */
static int tolua_get_SDL_Aloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Aloss);

	return 1;
}

/* set function: Aloss of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Aloss (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Aloss = U8(L, 2);

	return 0;
}

/* get function: Rshift of class  SDL_PixelFormat */
static int tolua_get_SDL_Rshift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Rshift);

	return 1;
}

/* set function: Rshift of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Rshift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Rshift = U8(L, 2);

	return 0;
}

/* get function: Gshift of class  SDL_PixelFormat */
static int tolua_get_SDL_Gshift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Gshift);

	return 1;
}

/* set function: Gshift of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Gshift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Gshift = U8(L, 2);

	return 0;
}

/* get function: Bshift of class  SDL_PixelFormat */
static int tolua_get_SDL_Bshift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Bshift);

	return 1;
}

/* set function: Bshift of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Bshift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Bshift = U8(L, 2);

	return 0;
}

/* get function: Ashift of class  SDL_PixelFormat */
static int tolua_get_SDL_Ashift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Ashift);

	return 1;
}

/* set function: Ashift of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Ashift (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Ashift = U8(L, 2);

	return 0;
}

/* get function: Rmask of class  SDL_PixelFormat */
static int tolua_get_SDL_Rmask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Rmask);

	return 1;
}

/* set function: Rmask of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Rmask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Rmask = U(L, 2);

	return 0;
}

/* get function: Gmask of class  SDL_PixelFormat */
static int tolua_get_SDL_Gmask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Gmask);

	return 1;
}

/* set function: Gmask of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Gmask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Gmask = U(L, 2);

	return 0;
}

/* get function: Bmask of class  SDL_PixelFormat */
static int tolua_get_SDL_Bmask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Bmask);

	return 1;
}

/* set function: Bmask of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Bmask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Bmask = U(L, 2);

	return 0;
}

/* get function: Amask of class  SDL_PixelFormat */
static int tolua_get_SDL_Amask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->Amask);

	return 1;
}

/* set function: Amask of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_Amask (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->Amask = U(L, 2);

	return 0;
}

/* get function: colorkey of class  SDL_PixelFormat */
static int tolua_get_SDL_colorkey (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->colorkey);

	return 1;
}

/* set function: colorkey of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_colorkey (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->colorkey = U(L, 2);

	return 0;
}

/* get function: alpha of class  SDL_PixelFormat */
static int tolua_get_SDL_alpha (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->alpha);

	return 1;
}

/* set function: alpha of class  SDL_PixelFormat */
static int Let_SDL_PixelFormat_SDL_alpha (lua_State * L)
{
	SDL_PixelFormat * self = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	self->alpha = U8(L, 2);

	return 0;
}

/* get function: flags of class  SDL_Surface */
static int tolua_get_SDL_flags (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->flags);

	return 1;
}

/* set function: flags of class  SDL_Surface */
static int Let_SDL_Surface_SDL_flags (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	self->flags = U(L, 2);

	return 0;
}

/* get function: format of class  SDL_Surface */
static int tolua_get_SDL_format_ptr (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, self->format, "PixelFormat");

	return 1;
}

/* set function: format of class  SDL_Surface */
static int Let_SDL_Surface_SDL_format_ptr (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	self->format = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 2, 0));

	return 0;
}

/* get function: w of class  SDL_Surface */
static int tolua_get_SDL_w_Surface (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->w);

	return 1;
}

/* set function: w of class  SDL_Surface */
static int Let_SDL_Surface_SDL_w (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	self->w = I(L, 2);

	return 0;
}

/* get function: h of class  SDL_Surface */
static int tolua_get_SDL_h_Surface (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->h);

	return 1;
}

/* set function: h of class  SDL_Surface */
static int Let_SDL_Surface_SDL_h (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	self->h = I(L, 2);

	return 0;
}

/* get function: pitch of class  SDL_Surface */
static int tolua_get_SDL_pitch (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->pitch);

	return 1;
}

/* set function: pitch of class  SDL_Surface */
static int Let_SDL_Surface_SDL_pitch (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	self->pitch = U16(L, 2);

	return 0;
}

/* get function: pixels of class  SDL_Surface */
static int tolua_get_SDL_pixels (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushlightuserdata(L, self->pixels);

	return 1;
}

/* set function: pixels of class  SDL_Surface */
static int Let_SDL_Surface_SDL_pixels (lua_State * L)
{
	SDL_Surface * self = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	self->pixels = UD(L, 2);

	return 0;
}

/* get function: hw_available of class  SDL_VideoInfo */
static int tolua_get_SDL_hw_available (lua_State * L)
{
	SDL_VideoInfo * self = static_cast<SDL_VideoInfo*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->hw_available);

	return 1;
}

/* set function: hw_available of class  SDL_VideoInfo */
static int Let_SDL_VideoInfo_SDL_hw_available (lua_State * L)
{
	SDL_VideoInfo * self = static_cast<SDL_VideoInfo*>(tolua_tousertype(L, 1, 0));

	self->hw_available = U(L, 2);

	return 0;
}

/* get function: video_mem of class  SDL_VideoInfo */
static int tolua_get_SDL_video_mem (lua_State * L)
{
	SDL_VideoInfo * self = static_cast<SDL_VideoInfo*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, self->video_mem);

	return 1;
}

/* set function: video_mem of class  SDL_VideoInfo */
static int Let_SDL_VideoInfo_SDL_video_mem (lua_State * L)
{
	SDL_VideoInfo * self = static_cast<SDL_VideoInfo*>(tolua_tousertype(L, 1, 0));

	self->video_mem = U(L, 2);

	return 0;
}

/* get function: vfmt of class  SDL_VideoInfo */
static int tolua_get_SDL_vfmt_ptr (lua_State * L)
{
	SDL_VideoInfo * self = static_cast<SDL_VideoInfo*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, self->vfmt, "PixelFormat");

	return 1;
}

/* set function: vfmt of class  SDL_VideoInfo */
static int Let_SDL_VideoInfo_SDL_vfmt_ptr (lua_State * L)
{
	SDL_VideoInfo * self = static_cast<SDL_VideoInfo*>(tolua_tousertype(L, 1, 0));

	self->vfmt = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 2, 0));

	return 0;
}

/* function: SDL_VideoInit */
static int LDL_SDL_SDL_VideoInit00 (lua_State * L)
{
	lua_pushnumber(L, SDL_VideoInit(S(L, 1), U(L, 2)));

	return 1;
}

/* function: SDL_VideoQuit */
static int LDL_SDL_SDL_VideoQuit00 (lua_State * L)
{
	SDL_VideoQuit();

	return 0;
}

/* function: SDL_VideoDriverName */
static int LDL_SDL_SDL_VideoDriverName00 (lua_State * L)
{
	lua_pushstring(L, SDL_VideoDriverName(const_cast<char*>(S(L, 1)), I(L, 2)));

	return 1;
}

/* function: SDL_GetVideoSurface */
static int LDL_SDL_SDL_GetVideoSurface00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_GetVideoSurface(), "Surface");

	return 1;
}

/* function: SDL_GetVideoInfo */
static int LDL_SDL_SDL_GetVideoInfo00 (lua_State * L)
{
	tolua_pushusertype(L, (void*)SDL_GetVideoInfo(), "const SDL_VideoInfo");

	return 1;
}

/* function: SDL_VideoModeOK */
static int LDL_SDL_SDL_VideoModeOK00 (lua_State * L)
{
	lua_pushnumber(L, SDL_VideoModeOK(I(L, 1), I(L, 2), I(L, 3), U(L, 4)));

	return 1;
}

/* function: SDL_SetVideoMode */
static int LDL_SDL_SDL_SetVideoMode00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_SetVideoMode(I(L, 1), I(L, 2), I(L, 3), U(L, 4)), "Surface");

	return 1;
}

/* function: SDL_UpdateRects */
static int LDL_SDL_SDL_UpdateRects00 (lua_State * L)
{
	SDL_Surface * screen = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * rects = static_cast<SDL_Rect*>(tolua_tousertype(L, 3, 0));

	SDL_UpdateRects(screen, I(L, 2), rects);

	return 0;
}

/* function: SDL_UpdateRect */
static int LDL_SDL_SDL_UpdateRect00 (lua_State * L)
{
	SDL_Surface * screen = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	SDL_UpdateRect(screen, S32(L, 2), S32(L, 3), S32(L, 4), S32(L, 5));

	return 0;
}

/* function: SDL_Flip */
static int LDL_SDL_SDL_Flip00 (lua_State * L)
{
	SDL_Surface * screen = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_Flip(screen));

	return 1;
}

/* function: SDL_SetGamma */
static int LDL_SDL_SDL_SetGamma00 (lua_State * L)
{
	lua_pushnumber(L, SDL_SetGamma(F(L, 1), F(L, 2), F(L, 3)));

	return 1;
}

/* function: SDL_SetGammaRamp */
static int LDL_SDL_SDL_SetGammaRamp00 (lua_State * L)
{
	Uint16 r = U16(L, 1);
	Uint16 g = U16(L, 2);
	Uint16 b = U16(L, 3);

	lua_pushnumber(L, SDL_SetGammaRamp(&r, &g, &b));
	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);

	return 4;
}

/* function: SDL_GetGammaRamp */
static int LDL_SDL_SDL_GetGammaRamp00 (lua_State * L)
{
	Uint16 r = U16(L, 1);
	Uint16 g = U16(L, 2);
	Uint16 b = U16(L, 3);

	lua_pushnumber(L, SDL_GetGammaRamp(&r, &g, &b));
	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);

	return 4;
}

/* function: SDL_SetColors */
static int LDL_SDL_SDL_SetColors00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Color * colors = static_cast<SDL_Color*>(tolua_tousertype(L, 2, 0));

	lua_pushnumber(L, SDL_SetColors(surface, colors, I(L, 3), I(L, 4)));

	return 1;
}

/* function: SDL_SetPalette */
static int LDL_SDL_SDL_SetPalette00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Color * colors = static_cast<SDL_Color*>(tolua_tousertype(L, 3, 0));

	lua_pushnumber(L, SDL_SetPalette(surface, I(L, 2), colors, I(L, 4), I(L, 5)));

	return 1;
}

/* function: SDL_MapRGB */
static int LDL_SDL_SDL_MapRGB00 (lua_State * L)
{
	SDL_PixelFormat * format = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_MapRGB(format, U8(L, 2), U8(L, 3), U8(L, 4)));

	return 1;
}

/* function: SDL_MapRGBA */
static int LDL_SDL_SDL_MapRGBA00 (lua_State * L)
{
	SDL_PixelFormat * format = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_MapRGBA(format, U8(L, 2), U8(L, 3), U8(L, 4), U8(L, 5)));

	return 1;
}

/* function: SDL_GetRGB */
static int LDL_SDL_SDL_GetRGB00 (lua_State * L)
{
	SDL_PixelFormat * fmt = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 2, 0));

	Uint8 r = U8(L, 3);
	Uint8 g = U8(L, 4);
	Uint8 b = U8(L, 5);

	SDL_GetRGB(U(L, 1), fmt, &r, &g, &b);

	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);

	return 3;
}

/* function: SDL_GetRGBA */
static int LDL_SDL_SDL_GetRGBA00 (lua_State * L)
{
	SDL_PixelFormat * fmt = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 2, 0));

	Uint8 r = U8(L, 3);
	Uint8 g = U8(L, 4);
	Uint8 b = U8(L, 5);
	Uint8 a = U8(L, 6);

	SDL_GetRGBA(U(L, 1), fmt, &r, &g, &b, &a);

	lua_pushnumber(L, r);
	lua_pushnumber(L, g);
	lua_pushnumber(L, b);
	lua_pushnumber(L, a);

	return 4;
}

/* function: SDL_CreateRGBSurface */
static int LDL_SDL_SDL_CreateRGBSurface00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_CreateRGBSurface(U(L, 1), I(L, 2), I(L, 3), I(L, 4), U(L, 5), U(L, 6), U(L, 7), U(L, 8)), "Surface");

	return 1;
}

/* function: SDL_CreateRGBSurfaceFrom */
static int LDL_SDL_SDL_CreateRGBSurfaceFrom00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_CreateRGBSurfaceFrom(UD(L, 1), I(L, 2), I(L, 3), I(L, 4), I(L, 5), U(L, 6), U(L, 7), U(L, 8), U(L, 9)), "Surface");

	return 1;
}

/* function: SDL_FreeSurface */
static int LDL_SDL_SDL_FreeSurface00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	SDL_FreeSurface(surface);

	return 0;
}

/* function: SDL_LockSurface */
static int LDL_SDL_SDL_LockSurface00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_LockSurface(surface));

	return 1;
}

/* function: SDL_UnlockSurface */
static int LDL_SDL_SDL_UnlockSurface00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	SDL_UnlockSurface(surface);

	return 0;
}

/* function: SDL_LoadBMP_RW */
static int LDL_SDL_SDL_LoadBMP_RW00 (lua_State * L)
{
	SDL_RWops* src = static_cast<SDL_RWops*>(tolua_tousertype(L, 1,0 ));

	tolua_pushusertype(L, SDL_LoadBMP_RW(src, I(L, 2)), "Surface");

	return 1;
}

/* function: SDL_LoadBMP */
static int LDL_SDL_SDL_LoadBMP00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_LoadBMP(S(L, 1)), "Surface");

	return 1;
}

/* function: SDL_SaveBMP_RW */
static int LDL_SDL_SDL_SaveBMP_RW00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_RWops* dst = static_cast<SDL_RWops*>(tolua_tousertype(L, 2, 0));

	lua_pushnumber(L, SDL_SaveBMP_RW(surface, dst, I(L, 3)));

	return 1;
}

/* function: SDL_SaveBMP */
static int LDL_SDL_SDL_SaveBMP00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_SaveBMP(surface, S(L, 2)));

	return 1;
}

/* function: SDL_SetColorKey */
static int LDL_SDL_SDL_SetColorKey00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_SetColorKey(surface, U(L, 2), U(L, 3)));

	return 1;
}

/* function: SDL_SetAlpha */
static int LDL_SDL_SDL_SetAlpha00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_SetAlpha(surface, U(L, 2), U8(L, 3)));

	return 1;
}

/* function: SDL_SetClipRect */
static int LDL_SDL_SDL_SetClipRect00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * rect = static_cast<SDL_Rect*>(tolua_tousertype(L, 2,0));

	lua_pushnumber(L, SDL_SetClipRect(surface, rect));

	return 1;
}

/* function: SDL_GetClipRect */
static int LDL_SDL_SDL_GetClipRect00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * rect = static_cast<SDL_Rect*>(tolua_tousertype(L, 2,0));

	SDL_GetClipRect(surface, rect);

	return 0;
}

/* function: SDL_ConvertSurface */
static int LDL_SDL_SDL_ConvertSurface00 (lua_State * L)
{
	SDL_Surface * src = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_PixelFormat * fmt = static_cast<SDL_PixelFormat*>(tolua_tousertype(L, 2, 0));

	tolua_pushusertype(L, SDL_ConvertSurface(src, fmt, U(L, 3)), "Surface");

	return 1;
}

/* function: SDL_UpperBlit */
static int LDL_SDL_SDL_UpperBlit00 (lua_State * L)
{
	SDL_Surface * src = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * srcrect = static_cast<SDL_Rect*>(tolua_tousertype(L, 2, 0));
	SDL_Surface * dst = static_cast<SDL_Surface*>(tolua_tousertype(L, 3, 0));
	SDL_Rect * dstrect = static_cast<SDL_Rect*>(tolua_tousertype(L, 4, 0));

	lua_pushnumber(L, SDL_UpperBlit(src, srcrect, dst, dstrect));

	return 1;
}

/* function: SDL_LowerBlit */
static int LDL_SDL_SDL_LowerBlit00 (lua_State * L)
{
	SDL_Surface * src = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * srcrect = static_cast<SDL_Rect*>(tolua_tousertype(L, 2, 0));
	SDL_Surface * dst = static_cast<SDL_Surface*>(tolua_tousertype(L, 3, 0));
	SDL_Rect * dstrect = static_cast<SDL_Rect*>(tolua_tousertype(L, 4, 0));

	lua_pushnumber(L, SDL_LowerBlit(src, srcrect, dst, dstrect));

	return 1;
}

/* function: SDL_FillRect */
static int LDL_SDL_SDL_FillRect00 (lua_State * L)
{
	SDL_Surface * dst = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * dstrect = static_cast<SDL_Rect*>(tolua_tousertype(L, 2, 0));

	lua_pushnumber(L, SDL_FillRect(dst, dstrect, U(L, 3)));

	return 1;
}

/* function: SDL_DisplayFormat */
static int LDL_SDL_SDL_DisplayFormat00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, SDL_DisplayFormat(surface), "Surface");

	return 1;
}

/* function: SDL_DisplayFormatAlpha */
static int LDL_SDL_SDL_DisplayFormatAlpha00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, SDL_DisplayFormatAlpha(surface), "Surface");

	return 1;
}

/* function: SDL_CreateYUVOverlay */
static int LDL_SDL_SDL_CreateYUVOverlay00 (lua_State * L)
{
	SDL_Surface * display = static_cast<SDL_Surface*>(tolua_tousertype(L, 4, 0));

	tolua_pushusertype(L, SDL_CreateYUVOverlay(I(L, 1), I(L, 2), U(L, 3), display), "Overlay");

	return 1;
}

/* function: SDL_LockYUVOverlay */
static int LDL_SDL_SDL_LockYUVOverlay00 (lua_State * L)
{
	SDL_Overlay * overlay = static_cast<SDL_Overlay*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_LockYUVOverlay(overlay));

	return 1;
}

/* function: SDL_UnlockYUVOverlay */
static int LDL_SDL_SDL_UnlockYUVOverlay00 (lua_State * L)
{
	SDL_Overlay * overlay = static_cast<SDL_Overlay*>(tolua_tousertype(L, 1, 0));

	SDL_UnlockYUVOverlay(overlay);

	return 0;
}

/* function: SDL_DisplayYUVOverlay */
static int LDL_SDL_SDL_DisplayYUVOverlay00 (lua_State * L)
{
	SDL_Overlay * overlay = static_cast<SDL_Overlay*>(tolua_tousertype(L, 1, 0));
	SDL_Rect * dstrect = static_cast<SDL_Rect*>(tolua_tousertype(L, 2, 0));

	lua_pushnumber(L, SDL_DisplayYUVOverlay(overlay, dstrect));

	return 1;
}

/* function: SDL_FreeYUVOverlay */
static int LDL_SDL_SDL_FreeYUVOverlay00 (lua_State * L)
{
	SDL_Overlay * overlay = static_cast<SDL_Overlay*>(tolua_tousertype(L, 1, 0));

	SDL_FreeYUVOverlay(overlay);

	return 0;
}

/* function: SDL_GL_LoadLibrary */
static int LDL_SDL_SDL_GL_LoadLibrary00 (lua_State * L)
{
	lua_pushnumber(L, SDL_GL_LoadLibrary(S(L, 1)));

	return 1;
}

/* function: SDL_GL_GetProcAddress */
static int LDL_SDL_SDL_GL_GetProcAddress00 (lua_State * L)
{
	lua_pushlightuserdata(L, SDL_GL_GetProcAddress(S(L, 1)));

	return 1;
}

/* function: SDL_GL_SetAttribute */
static int LDL_SDL_SDL_GL_SetAttribute00 (lua_State * L)
{
	lua_pushnumber(L, SDL_GL_SetAttribute(static_cast<SDL_GLattr>(I(L, 1)), I(L, 2)));

	return 1;
}

/* function: SDL_GL_GetAttribute */
static int LDL_SDL_SDL_GL_GetAttribute00 (lua_State * L)
{
	int value = I(L, 2);

	lua_pushnumber(L, SDL_GL_GetAttribute(static_cast<SDL_GLattr>(I(L, 1)), &value));
	lua_pushnumber(L, value);

	return 2;
}

/* function: SDL_GL_SwapBuffers */
static int LDL_SDL_SDL_GL_SwapBuffers00 (lua_State * L)
{
	SDL_GL_SwapBuffers();

	return 0;
}

/* function: SDL_GL_UpdateRects */
static int LDL_SDL_SDL_GL_UpdateRects00 (lua_State * L)
{
	SDL_Rect * rects = static_cast<SDL_Rect*>(tolua_tousertype(L, 2, 0));

	SDL_GL_UpdateRects(I(L, 1), rects);

	return 0;
}

/* function: SDL_GL_Lock */
static int LDL_SDL_SDL_GL_Lock00 (lua_State * L)
{
	SDL_GL_Lock();

	return 0;
}

/* function: SDL_GL_Unlock */
static int LDL_SDL_SDL_GL_Unlock00 (lua_State * L)
{
	SDL_GL_Unlock();

	return 0;
}

/* function: SDL_WM_SetCaption */
static int LDL_SDL_SDL_WM_SetCaption00 (lua_State * L)
{
	SDL_WM_SetCaption(S(L, 1), S(L, 2));

	return 0;
}

/* function: SDL_WM_GetCaption */
static int LDL_SDL_SDL_WM_GetCaption00 (lua_State * L)
{
	char Buf[512], * pTitle = Buf + 0, * pIcon = Buf + 256;
	
	SDL_WM_GetCaption(&pTitle, &pIcon);

	lua_pushstring(L, pTitle);
	lua_pushstring(L, pIcon);

	return 2;
}

/* function: SDL_WM_SetIcon */
static int LDL_SDL_SDL_WM_SetIcon00 (lua_State * L)
{
	SDL_Surface * icon = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));
	Uint8 mask = U8(L, 2);

	SDL_WM_SetIcon(icon, &mask);

	lua_pushnumber(L, mask);

	return 1;
}

/* function: SDL_WM_IconifyWindow */
static int LDL_SDL_SDL_WM_IconifyWindow00 (lua_State * L)
{
	lua_pushnumber(L, SDL_WM_IconifyWindow());

	return 1;
}

/* function: SDL_WM_ToggleFullScreen */
static int LDL_SDL_SDL_WM_ToggleFullScreen00 (lua_State * L)
{
	SDL_Surface * surface = static_cast<SDL_Surface*>(tolua_tousertype(L, 1, 0));

	lua_pushnumber(L, SDL_WM_ToggleFullScreen(surface));

	return 1;
}

/* function: SDL_WM_GrabInput */
static int LDL_SDL_SDL_WM_GrabInput00 (lua_State * L)
{
	lua_pushnumber(L, SDL_WM_GrabInput(static_cast<SDL_GrabMode>(I(L, 1))));

	return 1;
}

/* function: SDL_RWFromFile */
static int LDL_SDL_SDL_RWFromFile00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_RWFromFile(S(L, 1), S(L, 2)), "RWops");

	return 1;
}

/* function: SDL_RWFromFP */
static int LDL_SDL_SDL_RWFromFP00 (lua_State * L)
{
	FILE * fp = static_cast<FILE*>(tolua_tousertype(L, 1, 0));

	tolua_pushusertype(L, SDL_RWFromFP(fp, I(L, 2)), "RWops");

	return 1;
}

/* function: SDL_RWFromMem */
static int LDL_SDL_SDL_RWFromMem00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_RWFromMem(UD(L, 1), I(L, 2)), "RWops");

	return 1;
}

/* function: SDL_AllocRW */
static int LDL_SDL_SDL_AllocRW00 (lua_State * L)
{
	tolua_pushusertype(L, SDL_AllocRW(), "RWops");

	return 1;
}

/* function: SDL_FreeRW */
static int LDL_SDL_SDL_FreeRW00 (lua_State * L)
{
	SDL_RWops* area = static_cast<SDL_RWops*>(tolua_tousertype(L, 1, 0));

	SDL_FreeRW(area);

	return 0;
}

/* function: SDL_Init */
static int LDL_SDL_SDL_Init00 (lua_State * L)
{
	lua_pushnumber(L, SDL_Init(U(L, 1)));

	return 1;
}

/* function: SDL_InitSubSystem */
static int LDL_SDL_SDL_InitSubSystem00 (lua_State * L)
{
	lua_pushnumber(L, SDL_InitSubSystem(U(L, 1)));

	return 1;
}

/* function: SDL_QuitSubSystem */
static int LDL_SDL_SDL_QuitSubSystem00 (lua_State * L)
{
	SDL_QuitSubSystem(U(L, 1));

	return 0;
}

/* function: SDL_WasInit */
static int LDL_SDL_SDL_WasInit00 (lua_State * L)
{
	lua_pushnumber(L, SDL_WasInit(U(L, 1)));

	return 1;
}

/* function: SDL_Quit */
static int LDL_SDL_SDL_Quit00 (lua_State * L)
{
	SDL_Quit();

	return 0;
}

/// @brief Binds SDL to the scripting system
void BindSDL (lua_State * L)
{
	tolua_open(L);
	tolua_reg_types(L);
	tolua_module(L,NULL,0);
	tolua_beginmodule(L,NULL);
	tolua_module(L,"SDL",0);
	tolua_beginmodule(L,"SDL");
	tolua_function(L,"U8LoadBuffer",U8Buffer_Load);
	tolua_function(L,"Test",LDL_SDL_bit_test00);
	tolua_function(L,"Or",LDL_SDL_bit_or00);
	tolua_function(L,"And",LDL_SDL_bit_and00);
	tolua_function(L,"Not",LDL_SDL_bit_not00);
	tolua_function(L,"Xor",LDL_SDL_bit_xor00);
	tolua_constant(L,"FALSE",SDL_FALSE);
	tolua_constant(L,"TRUE",SDL_TRUE);
	tolua_constant(L,"PRESSED",SDL_PRESSED);
	tolua_constant(L,"RELEASED",SDL_RELEASED);
	tolua_function(L,"GetError",LDL_SDL_SDL_GetError00);
	tolua_function(L,"ClearError",LDL_SDL_SDL_ClearError00);
	tolua_constant(L,"TIMESLICE",SDL_TIMESLICE);
	tolua_constant(L,"TIMER_RESOLUTION",TIMER_RESOLUTION);
	tolua_function(L,"GetTicks",LDL_SDL_SDL_GetTicks00);
	tolua_function(L,"Delay",LDL_SDL_SDL_Delay00);
	tolua_cclass(L,"Joystick","Joystick","",NULL);
	tolua_beginmodule(L,"Joystick");
	tolua_endmodule(L);
	tolua_function(L,"NumJoysticks",LDL_SDL_SDL_NumJoysticks00);
	tolua_function(L,"JoystickName",LDL_SDL_SDL_JoystickName00);
	tolua_function(L,"JoystickOpen",LDL_SDL_SDL_JoystickOpen00);
	tolua_function(L,"JoystickOpened",LDL_SDL_SDL_JoystickOpened00);
	tolua_function(L,"JoystickIndex",LDL_SDL_SDL_JoystickIndex00);
	tolua_function(L,"JoystickNumAxes",LDL_SDL_SDL_JoystickNumAxes00);
	tolua_function(L,"JoystickNumBalls",LDL_SDL_SDL_JoystickNumBalls00);
	tolua_function(L,"JoystickNumHats",LDL_SDL_SDL_JoystickNumHats00);
	tolua_function(L,"JoystickNumButtons",LDL_SDL_SDL_JoystickNumButtons00);
	tolua_function(L,"JoystickUpdate",LDL_SDL_SDL_JoystickUpdate00);
	tolua_function(L,"JoystickEventState",LDL_SDL_SDL_JoystickEventState00);
	tolua_function(L,"JoystickGetAxis",LDL_SDL_SDL_JoystickGetAxis00);
	tolua_constant(L,"HAT_CENTERED",SDL_HAT_CENTERED);
	tolua_constant(L,"HAT_UP",SDL_HAT_UP);
	tolua_constant(L,"HAT_RIGHT",SDL_HAT_RIGHT);
	tolua_constant(L,"HAT_DOWN",SDL_HAT_DOWN);
	tolua_constant(L,"HAT_LEFT",SDL_HAT_LEFT);
	tolua_constant(L,"HAT_RIGHTUP",SDL_HAT_RIGHTUP);
	tolua_constant(L,"HAT_RIGHTDOWN",SDL_HAT_RIGHTDOWN);
	tolua_constant(L,"HAT_LEFTUP",SDL_HAT_LEFTUP);
	tolua_constant(L,"HAT_LEFTDOWN",SDL_HAT_LEFTDOWN);
	tolua_function(L,"JoystickGetHat",LDL_SDL_SDL_JoystickGetHat00);
	tolua_function(L,"JoystickGetBall",LDL_SDL_SDL_JoystickGetBall00);
	tolua_function(L,"JoystickGetButton",LDL_SDL_SDL_JoystickGetButton00);
	tolua_function(L,"JoystickClose",LDL_SDL_SDL_JoystickClose00);
	tolua_constant(L,"K_UNKNOWN",SDLK_UNKNOWN);
	tolua_constant(L,"K_FIRST",SDLK_FIRST);
	tolua_constant(L,"K_BACKSPACE",SDLK_BACKSPACE);
	tolua_constant(L,"K_TAB",SDLK_TAB);
	tolua_constant(L,"K_CLEAR",SDLK_CLEAR);
	tolua_constant(L,"K_RETURN",SDLK_RETURN);
	tolua_constant(L,"K_PAUSE",SDLK_PAUSE);
	tolua_constant(L,"K_ESCAPE",SDLK_ESCAPE);
	tolua_constant(L,"K_SPACE",SDLK_SPACE);
	tolua_constant(L,"K_EXCLAIM",SDLK_EXCLAIM);
	tolua_constant(L,"K_QUOTEDBL",SDLK_QUOTEDBL);
	tolua_constant(L,"K_HASH",SDLK_HASH);
	tolua_constant(L,"K_DOLLAR",SDLK_DOLLAR);
	tolua_constant(L,"K_AMPERSAND",SDLK_AMPERSAND);
	tolua_constant(L,"K_QUOTE",SDLK_QUOTE);
	tolua_constant(L,"K_LEFTPAREN",SDLK_LEFTPAREN);
	tolua_constant(L,"K_RIGHTPAREN",SDLK_RIGHTPAREN);
	tolua_constant(L,"K_ASTERISK",SDLK_ASTERISK);
	tolua_constant(L,"K_PLUS",SDLK_PLUS);
	tolua_constant(L,"K_COMMA",SDLK_COMMA);
	tolua_constant(L,"K_MINUS",SDLK_MINUS);
	tolua_constant(L,"K_PERIOD",SDLK_PERIOD);
	tolua_constant(L,"K_SLASH",SDLK_SLASH);
	tolua_constant(L,"K_0",SDLK_0);
	tolua_constant(L,"K_1",SDLK_1);
	tolua_constant(L,"K_2",SDLK_2);
	tolua_constant(L,"K_3",SDLK_3);
	tolua_constant(L,"K_4",SDLK_4);
	tolua_constant(L,"K_5",SDLK_5);
	tolua_constant(L,"K_6",SDLK_6);
	tolua_constant(L,"K_7",SDLK_7);
	tolua_constant(L,"K_8",SDLK_8);
	tolua_constant(L,"K_9",SDLK_9);
	tolua_constant(L,"K_COLON",SDLK_COLON);
	tolua_constant(L,"K_SEMICOLON",SDLK_SEMICOLON);
	tolua_constant(L,"K_LESS",SDLK_LESS);
	tolua_constant(L,"K_EQUALS",SDLK_EQUALS);
	tolua_constant(L,"K_GREATER",SDLK_GREATER);
	tolua_constant(L,"K_QUESTION",SDLK_QUESTION);
	tolua_constant(L,"K_AT",SDLK_AT);
	tolua_constant(L,"K_LEFTBRACKET",SDLK_LEFTBRACKET);
	tolua_constant(L,"K_BACKSLASH",SDLK_BACKSLASH);
	tolua_constant(L,"K_RIGHTBRACKET",SDLK_RIGHTBRACKET);
	tolua_constant(L,"K_CARET",SDLK_CARET);
	tolua_constant(L,"K_UNDERSCORE",SDLK_UNDERSCORE);
	tolua_constant(L,"K_BACKQUOTE",SDLK_BACKQUOTE);
	tolua_constant(L,"K_a",SDLK_a);
	tolua_constant(L,"K_b",SDLK_b);
	tolua_constant(L,"K_c",SDLK_c);
	tolua_constant(L,"K_d",SDLK_d);
	tolua_constant(L,"K_e",SDLK_e);
	tolua_constant(L,"K_f",SDLK_f);
	tolua_constant(L,"K_g",SDLK_g);
	tolua_constant(L,"K_h",SDLK_h);
	tolua_constant(L,"K_i",SDLK_i);
	tolua_constant(L,"K_j",SDLK_j);
	tolua_constant(L,"K_k",SDLK_k);
	tolua_constant(L,"K_l",SDLK_l);
	tolua_constant(L,"K_m",SDLK_m);
	tolua_constant(L,"K_n",SDLK_n);
	tolua_constant(L,"K_o",SDLK_o);
	tolua_constant(L,"K_p",SDLK_p);
	tolua_constant(L,"K_q",SDLK_q);
	tolua_constant(L,"K_r",SDLK_r);
	tolua_constant(L,"K_s",SDLK_s);
	tolua_constant(L,"K_t",SDLK_t);
	tolua_constant(L,"K_u",SDLK_u);
	tolua_constant(L,"K_v",SDLK_v);
	tolua_constant(L,"K_w",SDLK_w);
	tolua_constant(L,"K_x",SDLK_x);
	tolua_constant(L,"K_y",SDLK_y);
	tolua_constant(L,"K_z",SDLK_z);
	tolua_constant(L,"K_DELETE",SDLK_DELETE);
	tolua_constant(L,"K_WORLD_0",SDLK_WORLD_0);
	tolua_constant(L,"K_WORLD_1",SDLK_WORLD_1);
	tolua_constant(L,"K_WORLD_2",SDLK_WORLD_2);
	tolua_constant(L,"K_WORLD_3",SDLK_WORLD_3);
	tolua_constant(L,"K_WORLD_4",SDLK_WORLD_4);
	tolua_constant(L,"K_WORLD_5",SDLK_WORLD_5);
	tolua_constant(L,"K_WORLD_6",SDLK_WORLD_6);
	tolua_constant(L,"K_WORLD_7",SDLK_WORLD_7);
	tolua_constant(L,"K_WORLD_8",SDLK_WORLD_8);
	tolua_constant(L,"K_WORLD_9",SDLK_WORLD_9);
	tolua_constant(L,"K_WORLD_10",SDLK_WORLD_10);
	tolua_constant(L,"K_WORLD_11",SDLK_WORLD_11);
	tolua_constant(L,"K_WORLD_12",SDLK_WORLD_12);
	tolua_constant(L,"K_WORLD_13",SDLK_WORLD_13);
	tolua_constant(L,"K_WORLD_14",SDLK_WORLD_14);
	tolua_constant(L,"K_WORLD_15",SDLK_WORLD_15);
	tolua_constant(L,"K_WORLD_16",SDLK_WORLD_16);
	tolua_constant(L,"K_WORLD_17",SDLK_WORLD_17);
	tolua_constant(L,"K_WORLD_18",SDLK_WORLD_18);
	tolua_constant(L,"K_WORLD_19",SDLK_WORLD_19);
	tolua_constant(L,"K_WORLD_20",SDLK_WORLD_20);
	tolua_constant(L,"K_WORLD_21",SDLK_WORLD_21);
	tolua_constant(L,"K_WORLD_22",SDLK_WORLD_22);
	tolua_constant(L,"K_WORLD_23",SDLK_WORLD_23);
	tolua_constant(L,"K_WORLD_24",SDLK_WORLD_24);
	tolua_constant(L,"K_WORLD_25",SDLK_WORLD_25);
	tolua_constant(L,"K_WORLD_26",SDLK_WORLD_26);
	tolua_constant(L,"K_WORLD_27",SDLK_WORLD_27);
	tolua_constant(L,"K_WORLD_28",SDLK_WORLD_28);
	tolua_constant(L,"K_WORLD_29",SDLK_WORLD_29);
	tolua_constant(L,"K_WORLD_30",SDLK_WORLD_30);
	tolua_constant(L,"K_WORLD_31",SDLK_WORLD_31);
	tolua_constant(L,"K_WORLD_32",SDLK_WORLD_32);
	tolua_constant(L,"K_WORLD_33",SDLK_WORLD_33);
	tolua_constant(L,"K_WORLD_34",SDLK_WORLD_34);
	tolua_constant(L,"K_WORLD_35",SDLK_WORLD_35);
	tolua_constant(L,"K_WORLD_36",SDLK_WORLD_36);
	tolua_constant(L,"K_WORLD_37",SDLK_WORLD_37);
	tolua_constant(L,"K_WORLD_38",SDLK_WORLD_38);
	tolua_constant(L,"K_WORLD_39",SDLK_WORLD_39);
	tolua_constant(L,"K_WORLD_40",SDLK_WORLD_40);
	tolua_constant(L,"K_WORLD_41",SDLK_WORLD_41);
	tolua_constant(L,"K_WORLD_42",SDLK_WORLD_42);
	tolua_constant(L,"K_WORLD_43",SDLK_WORLD_43);
	tolua_constant(L,"K_WORLD_44",SDLK_WORLD_44);
	tolua_constant(L,"K_WORLD_45",SDLK_WORLD_45);
	tolua_constant(L,"K_WORLD_46",SDLK_WORLD_46);
	tolua_constant(L,"K_WORLD_47",SDLK_WORLD_47);
	tolua_constant(L,"K_WORLD_48",SDLK_WORLD_48);
	tolua_constant(L,"K_WORLD_49",SDLK_WORLD_49);
	tolua_constant(L,"K_WORLD_50",SDLK_WORLD_50);
	tolua_constant(L,"K_WORLD_51",SDLK_WORLD_51);
	tolua_constant(L,"K_WORLD_52",SDLK_WORLD_52);
	tolua_constant(L,"K_WORLD_53",SDLK_WORLD_53);
	tolua_constant(L,"K_WORLD_54",SDLK_WORLD_54);
	tolua_constant(L,"K_WORLD_55",SDLK_WORLD_55);
	tolua_constant(L,"K_WORLD_56",SDLK_WORLD_56);
	tolua_constant(L,"K_WORLD_57",SDLK_WORLD_57);
	tolua_constant(L,"K_WORLD_58",SDLK_WORLD_58);
	tolua_constant(L,"K_WORLD_59",SDLK_WORLD_59);
	tolua_constant(L,"K_WORLD_60",SDLK_WORLD_60);
	tolua_constant(L,"K_WORLD_61",SDLK_WORLD_61);
	tolua_constant(L,"K_WORLD_62",SDLK_WORLD_62);
	tolua_constant(L,"K_WORLD_63",SDLK_WORLD_63);
	tolua_constant(L,"K_WORLD_64",SDLK_WORLD_64);
	tolua_constant(L,"K_WORLD_65",SDLK_WORLD_65);
	tolua_constant(L,"K_WORLD_66",SDLK_WORLD_66);
	tolua_constant(L,"K_WORLD_67",SDLK_WORLD_67);
	tolua_constant(L,"K_WORLD_68",SDLK_WORLD_68);
	tolua_constant(L,"K_WORLD_69",SDLK_WORLD_69);
	tolua_constant(L,"K_WORLD_70",SDLK_WORLD_70);
	tolua_constant(L,"K_WORLD_71",SDLK_WORLD_71);
	tolua_constant(L,"K_WORLD_72",SDLK_WORLD_72);
	tolua_constant(L,"K_WORLD_73",SDLK_WORLD_73);
	tolua_constant(L,"K_WORLD_74",SDLK_WORLD_74);
	tolua_constant(L,"K_WORLD_75",SDLK_WORLD_75);
	tolua_constant(L,"K_WORLD_76",SDLK_WORLD_76);
	tolua_constant(L,"K_WORLD_77",SDLK_WORLD_77);
	tolua_constant(L,"K_WORLD_78",SDLK_WORLD_78);
	tolua_constant(L,"K_WORLD_79",SDLK_WORLD_79);
	tolua_constant(L,"K_WORLD_80",SDLK_WORLD_80);
	tolua_constant(L,"K_WORLD_81",SDLK_WORLD_81);
	tolua_constant(L,"K_WORLD_82",SDLK_WORLD_82);
	tolua_constant(L,"K_WORLD_83",SDLK_WORLD_83);
	tolua_constant(L,"K_WORLD_84",SDLK_WORLD_84);
	tolua_constant(L,"K_WORLD_85",SDLK_WORLD_85);
	tolua_constant(L,"K_WORLD_86",SDLK_WORLD_86);
	tolua_constant(L,"K_WORLD_87",SDLK_WORLD_87);
	tolua_constant(L,"K_WORLD_88",SDLK_WORLD_88);
	tolua_constant(L,"K_WORLD_89",SDLK_WORLD_89);
	tolua_constant(L,"K_WORLD_90",SDLK_WORLD_90);
	tolua_constant(L,"K_WORLD_91",SDLK_WORLD_91);
	tolua_constant(L,"K_WORLD_92",SDLK_WORLD_92);
	tolua_constant(L,"K_WORLD_93",SDLK_WORLD_93);
	tolua_constant(L,"K_WORLD_94",SDLK_WORLD_94);
	tolua_constant(L,"K_WORLD_95",SDLK_WORLD_95);
	tolua_constant(L,"K_KP0",SDLK_KP0);
	tolua_constant(L,"K_KP1",SDLK_KP1);
	tolua_constant(L,"K_KP2",SDLK_KP2);
	tolua_constant(L,"K_KP3",SDLK_KP3);
	tolua_constant(L,"K_KP4",SDLK_KP4);
	tolua_constant(L,"K_KP5",SDLK_KP5);
	tolua_constant(L,"K_KP6",SDLK_KP6);
	tolua_constant(L,"K_KP7",SDLK_KP7);
	tolua_constant(L,"K_KP8",SDLK_KP8);
	tolua_constant(L,"K_KP9",SDLK_KP9);
	tolua_constant(L,"K_KP_PERIOD",SDLK_KP_PERIOD);
	tolua_constant(L,"K_KP_DIVIDE",SDLK_KP_DIVIDE);
	tolua_constant(L,"K_KP_MULTIPLY",SDLK_KP_MULTIPLY);
	tolua_constant(L,"K_KP_MINUS",SDLK_KP_MINUS);
	tolua_constant(L,"K_KP_PLUS",SDLK_KP_PLUS);
	tolua_constant(L,"K_KP_ENTER",SDLK_KP_ENTER);
	tolua_constant(L,"K_KP_EQUALS",SDLK_KP_EQUALS);
	tolua_constant(L,"K_UP",SDLK_UP);
	tolua_constant(L,"K_DOWN",SDLK_DOWN);
	tolua_constant(L,"K_RIGHT",SDLK_RIGHT);
	tolua_constant(L,"K_LEFT",SDLK_LEFT);
	tolua_constant(L,"K_INSERT",SDLK_INSERT);
	tolua_constant(L,"K_HOME",SDLK_HOME);
	tolua_constant(L,"K_END",SDLK_END);
	tolua_constant(L,"K_PAGEUP",SDLK_PAGEUP);
	tolua_constant(L,"K_PAGEDOWN",SDLK_PAGEDOWN);
	tolua_constant(L,"K_F1",SDLK_F1);
	tolua_constant(L,"K_F2",SDLK_F2);
	tolua_constant(L,"K_F3",SDLK_F3);
	tolua_constant(L,"K_F4",SDLK_F4);
	tolua_constant(L,"K_F5",SDLK_F5);
	tolua_constant(L,"K_F6",SDLK_F6);
	tolua_constant(L,"K_F7",SDLK_F7);
	tolua_constant(L,"K_F8",SDLK_F8);
	tolua_constant(L,"K_F9",SDLK_F9);
	tolua_constant(L,"K_F10",SDLK_F10);
	tolua_constant(L,"K_F11",SDLK_F11);
	tolua_constant(L,"K_F12",SDLK_F12);
	tolua_constant(L,"K_F13",SDLK_F13);
	tolua_constant(L,"K_F14",SDLK_F14);
	tolua_constant(L,"K_F15",SDLK_F15);
	tolua_constant(L,"K_NUMLOCK",SDLK_NUMLOCK);
	tolua_constant(L,"K_CAPSLOCK",SDLK_CAPSLOCK);
	tolua_constant(L,"K_SCROLLOCK",SDLK_SCROLLOCK);
	tolua_constant(L,"K_RSHIFT",SDLK_RSHIFT);
	tolua_constant(L,"K_LSHIFT",SDLK_LSHIFT);
	tolua_constant(L,"K_RCTRL",SDLK_RCTRL);
	tolua_constant(L,"K_LCTRL",SDLK_LCTRL);
	tolua_constant(L,"K_RALT",SDLK_RALT);
	tolua_constant(L,"K_LALT",SDLK_LALT);
	tolua_constant(L,"K_RMETA",SDLK_RMETA);
	tolua_constant(L,"K_LMETA",SDLK_LMETA);
	tolua_constant(L,"K_LSUPER",SDLK_LSUPER);
	tolua_constant(L,"K_RSUPER",SDLK_RSUPER);
	tolua_constant(L,"K_MODE",SDLK_MODE);
	tolua_constant(L,"K_COMPOSE",SDLK_COMPOSE);
	tolua_constant(L,"K_HELP",SDLK_HELP);
	tolua_constant(L,"K_PRINT",SDLK_PRINT);
	tolua_constant(L,"K_SYSREQ",SDLK_SYSREQ);
	tolua_constant(L,"K_BREAK",SDLK_BREAK);
	tolua_constant(L,"K_MENU",SDLK_MENU);
	tolua_constant(L,"K_POWER",SDLK_POWER);
	tolua_constant(L,"K_EURO",SDLK_EURO);
	tolua_constant(L,"K_LAST",SDLK_LAST);
	tolua_constant(L,"KMOD_NONE",KMOD_NONE);
	tolua_constant(L,"KMOD_LSHIFT",KMOD_LSHIFT);
	tolua_constant(L,"KMOD_RSHIFT",KMOD_RSHIFT);
	tolua_constant(L,"KMOD_LCTRL",KMOD_LCTRL);
	tolua_constant(L,"KMOD_RCTRL",KMOD_RCTRL);
	tolua_constant(L,"KMOD_LALT",KMOD_LALT);
	tolua_constant(L,"KMOD_RALT",KMOD_RALT);
	tolua_constant(L,"KMOD_LMETA",KMOD_LMETA);
	tolua_constant(L,"KMOD_RMETA",KMOD_RMETA);
	tolua_constant(L,"KMOD_NUM",KMOD_NUM);
	tolua_constant(L,"KMOD_CAPS",KMOD_CAPS);
	tolua_constant(L,"KMOD_MODE",KMOD_MODE);
	tolua_constant(L,"KMOD_RESERVED",KMOD_RESERVED);
	tolua_constant(L,"KMOD_CTRL",KMOD_CTRL);
	tolua_constant(L,"KMOD_SHIFT",KMOD_SHIFT);
	tolua_constant(L,"KMOD_ALT",KMOD_ALT);
	tolua_constant(L,"KMOD_META",KMOD_META);
	tolua_cclass(L,"keysym","keysym","",NULL);
	tolua_beginmodule(L,"keysym");
	tolua_variable(L,"scancode",tolua_get_SDL_scancode,Let_SDL_keysym_SDL_scancode);
	tolua_variable(L,"sym",tolua_get_SDL_sym,Let_SDL_keysym_SDL_sym);
	tolua_variable(L,"mod",tolua_get_SDL_mod,Let_SDL_keysym_SDL_mod);
	tolua_variable(L,"unicode",tolua_get_SDL_unicode,Let_SDL_keysym_SDL_unicode);
	tolua_endmodule(L);
	tolua_constant(L,"ALL_HOTKEYS",SDL_ALL_HOTKEYS);
	tolua_function(L,"EnableUNICODE",LDL_SDL_SDL_EnableUNICODE00);
	tolua_constant(L,"DEFAULT_REPEAT_DELAY",SDL_DEFAULT_REPEAT_DELAY);
	tolua_constant(L,"DEFAULT_REPEAT_INTERVAL",SDL_DEFAULT_REPEAT_INTERVAL);
	tolua_function(L,"EnableKeyRepeat",LDL_SDL_SDL_EnableKeyRepeat00);
	tolua_function(L,"GetModState",LDL_SDL_SDL_GetModState00);
	tolua_function(L,"SetModState",LDL_SDL_SDL_SetModState00);
	tolua_function(L,"GetKeyName",LDL_SDL_SDL_GetKeyName00);
	tolua_cclass(L,"WMcursor","WMcursor","",NULL);
	tolua_beginmodule(L,"WMcursor");
	tolua_endmodule(L);
	tolua_cclass(L,"Cursor","Cursor","",NULL);
	tolua_beginmodule(L,"Cursor");
	tolua_endmodule(L);
	tolua_function(L,"GetMouseState",LDL_SDL_SDL_GetMouseState00);
	tolua_function(L,"GetRelativeMouseState",LDL_SDL_SDL_GetRelativeMouseState00);
	tolua_function(L,"WarpMouse",LDL_SDL_SDL_WarpMouse00);
	tolua_function(L,"CreateCursor",LDL_SDL_SDL_CreateCursor00);
	tolua_function(L,"SetCursor",LDL_SDL_SDL_SetCursor00);
	tolua_function(L,"GetCursor",LDL_SDL_SDL_GetCursor00);
	tolua_function(L,"FreeCursor",LDL_SDL_SDL_FreeCursor00);
	tolua_function(L,"ShowCursor",LDL_SDL_SDL_ShowCursor00);
	tolua_constant(L,"BUTTON_LEFT",SDL_BUTTON_LEFT);
	tolua_constant(L,"BUTTON_MIDDLE",SDL_BUTTON_MIDDLE);
	tolua_constant(L,"BUTTON_RIGHT",SDL_BUTTON_RIGHT);
	tolua_constant(L,"BUTTON_LMASK",SDL_BUTTON_LMASK);
	tolua_constant(L,"BUTTON_MMASK",SDL_BUTTON_MMASK);
	tolua_constant(L,"BUTTON_RMASK",SDL_BUTTON_RMASK);
	tolua_constant(L,"NOEVENT",SDL_NOEVENT);
	tolua_constant(L,"ACTIVEEVENT",SDL_ACTIVEEVENT);
	tolua_constant(L,"KEYDOWN",SDL_KEYDOWN);
	tolua_constant(L,"KEYUP",SDL_KEYUP);
	tolua_constant(L,"MOUSEMOTION",SDL_MOUSEMOTION);
	tolua_constant(L,"MOUSEBUTTONDOWN",SDL_MOUSEBUTTONDOWN);
	tolua_constant(L,"MOUSEBUTTONUP",SDL_MOUSEBUTTONUP);
	tolua_constant(L,"JOYAXISMOTION",SDL_JOYAXISMOTION);
	tolua_constant(L,"JOYBALLMOTION",SDL_JOYBALLMOTION);
	tolua_constant(L,"JOYHATMOTION",SDL_JOYHATMOTION);
	tolua_constant(L,"JOYBUTTONDOWN",SDL_JOYBUTTONDOWN);
	tolua_constant(L,"JOYBUTTONUP",SDL_JOYBUTTONUP);
	tolua_constant(L,"QUIT",SDL_QUIT);
	tolua_constant(L,"SYSWMEVENT",SDL_SYSWMEVENT);
	tolua_constant(L,"EVENT_RESERVEDA",SDL_EVENT_RESERVEDA);
	tolua_constant(L,"EVENT_RESERVEDB",SDL_EVENT_RESERVEDB);
	tolua_constant(L,"VIDEORESIZE",SDL_VIDEORESIZE);
	tolua_constant(L,"VIDEOEXPOSE",SDL_VIDEOEXPOSE);
	tolua_constant(L,"EVENT_RESERVED2",SDL_EVENT_RESERVED2);
	tolua_constant(L,"EVENT_RESERVED3",SDL_EVENT_RESERVED3);
	tolua_constant(L,"EVENT_RESERVED4",SDL_EVENT_RESERVED4);
	tolua_constant(L,"EVENT_RESERVED5",SDL_EVENT_RESERVED5);
	tolua_constant(L,"EVENT_RESERVED6",SDL_EVENT_RESERVED6);
	tolua_constant(L,"EVENT_RESERVED7",SDL_EVENT_RESERVED7);
	tolua_constant(L,"USEREVENT",SDL_USEREVENT);
	tolua_constant(L,"NUMEVENTS",SDL_NUMEVENTS);
	tolua_constant(L,"ACTIVEEVENTMASK",SDL_ACTIVEEVENTMASK);
	tolua_constant(L,"KEYDOWNMASK",SDL_KEYDOWNMASK);
	tolua_constant(L,"KEYUPMASK",SDL_KEYUPMASK);
	tolua_constant(L,"MOUSEMOTIONMASK",SDL_MOUSEMOTIONMASK);
	tolua_constant(L,"MOUSEBUTTONDOWNMASK",SDL_MOUSEBUTTONDOWNMASK);
	tolua_constant(L,"MOUSEBUTTONUPMASK",SDL_MOUSEBUTTONUPMASK);
	tolua_constant(L,"MOUSEEVENTMASK",SDL_MOUSEEVENTMASK);
	tolua_constant(L,"JOYAXISMOTIONMASK",SDL_JOYAXISMOTIONMASK);
	tolua_constant(L,"JOYBALLMOTIONMASK",SDL_JOYBALLMOTIONMASK);
	tolua_constant(L,"JOYHATMOTIONMASK",SDL_JOYHATMOTIONMASK);
	tolua_constant(L,"JOYBUTTONDOWNMASK",SDL_JOYBUTTONDOWNMASK);
	tolua_constant(L,"JOYBUTTONUPMASK",SDL_JOYBUTTONUPMASK);
	tolua_constant(L,"JOYEVENTMASK",SDL_JOYEVENTMASK);
	tolua_constant(L,"VIDEORESIZEMASK",SDL_VIDEORESIZEMASK);
	tolua_constant(L,"VIDEOEXPOSEMASK",SDL_VIDEOEXPOSEMASK);
	tolua_constant(L,"QUITMASK",SDL_QUITMASK);
	tolua_constant(L,"SYSWMEVENTMASK",SDL_SYSWMEVENTMASK);
	tolua_constant(L,"ALLEVENTS",SDL_ALLEVENTS);
	tolua_cclass(L,"ActiveEvent","ActiveEvent","",NULL);
	tolua_beginmodule(L,"ActiveEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_Active,Let_SDL_ActiveEvent_SDL_type);
	tolua_variable(L,"gain",tolua_get_SDL_gain,Let_SDL_ActiveEvent_SDL_gain);
	tolua_variable(L,"state",tolua_get_SDL_state_Active,Let_SDL_ActiveEvent_SDL_state);
	tolua_endmodule(L);
	tolua_cclass(L,"KeyboardEvent","KeyboardEvent","",NULL);
	tolua_beginmodule(L,"KeyboardEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_Keyboard,Let_SDL_KeyboardEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_KeyboardEvent_SDL_which);
	tolua_variable(L,"state",tolua_get_SDL_state_Keyboard,Let_SDL_KeyboardEvent_SDL_state);
	tolua_variable(L,"keysym",tolua_get_SDL_keysym,Let_SDL_KeyboardEvent_SDL_keysym);
	tolua_endmodule(L);
	tolua_cclass(L,"MouseMotionEvent","MouseMotionEvent","",NULL);
	tolua_beginmodule(L,"MouseMotionEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_MouseMotion,Let_SDL_MouseMotionEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_MouseMotionEvent_SDL_which);
	tolua_variable(L,"state",tolua_get_SDL_state_MouseMotion,Let_SDL_MouseMotionEvent_SDL_state);
	tolua_variable(L,"x",tolua_get_SDL_x_MouseMotion,Let_SDL_MouseMotionEvent_SDL_x);
	tolua_variable(L,"y",tolua_get_SDL_y_MouseMotion,Let_SDL_MouseMotionEvent_SDL_y);
	tolua_variable(L,"xrel",tolua_get_SDL_xrel_MouseMotion,Let_SDL_MouseMotionEvent_SDL_xrel);
	tolua_variable(L,"yrel",tolua_get_SDL_yrel_MouseMotion,Let_SDL_MouseMotionEvent_SDL_yrel);
	tolua_endmodule(L);
	tolua_cclass(L,"MouseButtonEvent","MouseButtonEvent","",NULL);
	tolua_beginmodule(L,"MouseButtonEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_MouseButton,Let_SDL_MouseButtonEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_MouseButtonEvent_SDL_which);
	tolua_variable(L,"button",tolua_get_SDL_button_MouseButton,Let_SDL_MouseButtonEvent_SDL_button);
	tolua_variable(L,"state",tolua_get_SDL_state_MouseButton,Let_SDL_MouseButtonEvent_SDL_state);
	tolua_variable(L,"x",tolua_get_SDL_x_MouseButton,Let_SDL_MouseButtonEvent_SDL_x);
	tolua_variable(L,"y",tolua_get_SDL_y_MouseButton,Let_SDL_MouseButtonEvent_SDL_y);
	tolua_endmodule(L);
	tolua_cclass(L,"JoyAxisEvent","JoyAxisEvent","",NULL);
	tolua_beginmodule(L,"JoyAxisEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_JoyAxis,Let_SDL_JoyAxisEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_JoyAxisEvent_SDL_which);
	tolua_variable(L,"axis",tolua_get_SDL_axis,Let_SDL_JoyAxisEvent_SDL_axis);
	tolua_variable(L,"value",tolua_get_SDL_value_JoyAxis,Let_SDL_JoyAxisEvent_SDL_value);
	tolua_endmodule(L);
	tolua_cclass(L,"JoyBallEvent","JoyBallEvent","",NULL);
	tolua_beginmodule(L,"JoyBallEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_JoyBall,Let_SDL_JoyBallEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_JoyBallEvent_SDL_which);
	tolua_variable(L,"ball",tolua_get_SDL_ball,Let_SDL_JoyBallEvent_SDL_ball);
	tolua_variable(L,"xrel",tolua_get_SDL_xrel_JoyBall,Let_SDL_JoyBallEvent_SDL_xrel);
	tolua_variable(L,"yrel",tolua_get_SDL_yrel_JoyBall,Let_SDL_JoyBallEvent_SDL_yrel);
	tolua_endmodule(L);
	tolua_cclass(L,"JoyHatEvent","JoyHatEvent","",NULL);
	tolua_beginmodule(L,"JoyHatEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_JoyHat,Let_SDL_JoyHatEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_JoyHatEvent_SDL_which);
	tolua_variable(L,"hat",tolua_get_SDL_hat,Let_SDL_JoyHatEvent_SDL_hat);
	tolua_variable(L,"value",tolua_get_SDL_value_JoyHat,Let_SDL_JoyHatEvent_SDL_value);
	tolua_endmodule(L);
	tolua_cclass(L,"JoyButtonEvent","JoyButtonEvent","",NULL);
	tolua_beginmodule(L,"JoyButtonEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_JoyButton,Let_SDL_JoyButtonEvent_SDL_type);
	tolua_variable(L,"which",tolua_get_SDL_which,Let_SDL_JoyButtonEvent_SDL_which);
	tolua_variable(L,"button",tolua_get_SDL_button_JoyButton,Let_SDL_JoyButtonEvent_SDL_button);
	tolua_variable(L,"state",tolua_get_SDL_state_JoyButton,Let_SDL_JoyButtonEvent_SDL_state);
	tolua_endmodule(L);
	tolua_cclass(L,"ResizeEvent","ResizeEvent","",NULL);
	tolua_beginmodule(L,"ResizeEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_Resize,Let_SDL_ResizeEvent_SDL_type);
	tolua_variable(L,"w",tolua_get_SDL_w_Resize,Let_SDL_ResizeEvent_SDL_w);
	tolua_variable(L,"h",tolua_get_SDL_h_Resize,Let_SDL_ResizeEvent_SDL_h);
	tolua_endmodule(L);
	tolua_cclass(L,"ExposeEvent","ExposeEvent","",NULL);
	tolua_beginmodule(L,"ExposeEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_Expose,Let_SDL_ExposeEvent_SDL_type);
	tolua_endmodule(L);
	tolua_cclass(L,"QuitEvent","QuitEvent","",NULL);
	tolua_beginmodule(L,"QuitEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_Quit,Let_SDL_QuitEvent_SDL_type);
	tolua_endmodule(L);
	tolua_cclass(L,"UserEvent","UserEvent","",NULL);
	tolua_beginmodule(L,"UserEvent");
	tolua_variable(L,"type",tolua_get_SDL_type_User,Let_SDL_UserEvent_SDL_type);
	tolua_variable(L,"code",tolua_get_SDL_code,Let_SDL_UserEvent_SDL_code);
	tolua_variable(L,"data1",tolua_get_SDL_data1,Let_SDL_UserEvent_SDL_data1);
	tolua_variable(L,"data2",tolua_get_SDL_data2,Let_SDL_UserEvent_SDL_data2);
	tolua_endmodule(L);
	tolua_cclass(L,"SysWMEvent","SysWMEvent","",NULL);
	tolua_beginmodule(L,"SysWMEvent");
	tolua_endmodule(L);
	tolua_cclass(L,"Event","Event","",NULL);
	tolua_beginmodule(L,"Event");
	tolua_variable(L,"type",tolua_get_SDL_type_Event,Let_SDL_Event_SDL_type);
	tolua_variable(L,"active",tolua_get_SDL_active,Let_SDL_Event_SDL_active);
	tolua_variable(L,"key",tolua_get_SDL_key,Let_SDL_Event_SDL_key);
	tolua_variable(L,"motion",tolua_get_SDL_motion,Let_SDL_Event_SDL_motion);
	tolua_variable(L,"button",tolua_get_SDL_button,Let_SDL_Event_SDL_button);
	tolua_variable(L,"jaxis",tolua_get_SDL_jaxis,Let_SDL_Event_SDL_jaxis);
	tolua_variable(L,"jball",tolua_get_SDL_jball,Let_SDL_Event_SDL_jball);
	tolua_variable(L,"jhat",tolua_get_SDL_jhat,Let_SDL_Event_SDL_jhat);
	tolua_variable(L,"jbutton",tolua_get_SDL_jbutton,Let_SDL_Event_SDL_jbutton);
	tolua_variable(L,"resize",tolua_get_SDL_resize,Let_SDL_Event_SDL_resize);
	tolua_variable(L,"expose",tolua_get_SDL_expose,Let_SDL_Event_SDL_expose);
	tolua_variable(L,"quit",tolua_get_SDL_quit,Let_SDL_Event_SDL_quit);
	tolua_variable(L,"user",tolua_get_SDL_user,Let_SDL_Event_SDL_user);
	tolua_variable(L,"syswm",tolua_get_SDL_syswm,Let_SDL_Event_SDL_syswm);
	tolua_endmodule(L);
	tolua_function(L,"Event_get",LDL_SDL_SDL_Event_get00);
	tolua_function(L,"PumpEvents",LDL_SDL_SDL_PumpEvents00);
	tolua_constant(L,"ADDEVENT",SDL_ADDEVENT);
	tolua_constant(L,"PEEKEVENT",SDL_PEEKEVENT);
	tolua_constant(L,"GETEVENT",SDL_GETEVENT);
	tolua_function(L,"PeepEvents",LDL_SDL_SDL_PeepEvents00);
	tolua_function(L,"PollEvent",LDL_SDL_SDL_PollEvent00);
	tolua_function(L,"WaitEvent",LDL_SDL_SDL_WaitEvent00);
	tolua_function(L,"PushEvent",LDL_SDL_SDL_PushEvent00);
	tolua_constant(L,"QUERY",SDL_QUERY);
	tolua_constant(L,"IGNORE",SDL_IGNORE);
	tolua_constant(L,"DISABLE",SDL_DISABLE);
	tolua_constant(L,"ENABLE",SDL_ENABLE);
	tolua_constant(L,"ALPHA_OPAQUE",SDL_ALPHA_OPAQUE);
	tolua_constant(L,"ALPHA_TRANSPARENT",SDL_ALPHA_TRANSPARENT);
	tolua_cclass(L,"Rect","Rect","",NULL);
	tolua_beginmodule(L,"Rect");
	tolua_variable(L,"x",tolua_get_SDL_x_Rect,Let_SDL_Rect_SDL_x);
	tolua_variable(L,"y",tolua_get_SDL_y_Rect,Let_SDL_Rect_SDL_y);
	tolua_variable(L,"w",tolua_get_SDL_w_Rect,Let_SDL_Rect_SDL_w);
	tolua_variable(L,"h",tolua_get_SDL_h_Rect,Let_SDL_Rect_SDL_h);
	tolua_endmodule(L);
	tolua_function(L,"Rect_get",LDL_SDL_SDL_Rect_get00);
	tolua_cclass(L,"Color","Color","",NULL);
	tolua_beginmodule(L,"Color");
	tolua_variable(L,"r",tolua_get_SDL_r,Let_SDL_Color_SDL_r);
	tolua_variable(L,"g",tolua_get_SDL_g,Let_SDL_Color_SDL_g);
	tolua_variable(L,"b",tolua_get_SDL_b,Let_SDL_Color_SDL_b);
	tolua_variable(L,"unused",tolua_get_SDL_unused,Let_SDL_Color_SDL_unused);
	tolua_endmodule(L);
	tolua_cclass(L,"Palette","Palette","",NULL);
	tolua_beginmodule(L,"Palette");
	tolua_variable(L,"ncolors",tolua_get_SDL_ncolors,Let_SDL_Palette_SDL_ncolors);
	tolua_variable(L,"colors",tolua_get_SDL_colors_ptr,Let_SDL_Palette_SDL_colors_ptr);
	tolua_endmodule(L);
	tolua_cclass(L,"PixelFormat","PixelFormat","",NULL);
	tolua_beginmodule(L,"PixelFormat");
	tolua_variable(L,"palette",tolua_get_SDL_palette_ptr,Let_SDL_PixelFormat_SDL_palette_ptr);
	tolua_variable(L,"BitsPerPixel",tolua_get_SDL_BitsPerPixel,Let_SDL_PixelFormat_SDL_BitsPerPixel);
	tolua_variable(L,"BytesPerPixel",tolua_get_SDL_BytesPerPixel,Let_SDL_PixelFormat_SDL_BytesPerPixel);
	tolua_variable(L,"Rloss",tolua_get_SDL_Rloss,Let_SDL_PixelFormat_SDL_Rloss);
	tolua_variable(L,"Gloss",tolua_get_SDL_Gloss,Let_SDL_PixelFormat_SDL_Gloss);
	tolua_variable(L,"Bloss",tolua_get_SDL_Bloss,Let_SDL_PixelFormat_SDL_Bloss);
	tolua_variable(L,"Aloss",tolua_get_SDL_Aloss,Let_SDL_PixelFormat_SDL_Aloss);
	tolua_variable(L,"Rshift",tolua_get_SDL_Rshift,Let_SDL_PixelFormat_SDL_Rshift);
	tolua_variable(L,"Gshift",tolua_get_SDL_Gshift,Let_SDL_PixelFormat_SDL_Gshift);
	tolua_variable(L,"Bshift",tolua_get_SDL_Bshift,Let_SDL_PixelFormat_SDL_Bshift);
	tolua_variable(L,"Ashift",tolua_get_SDL_Ashift,Let_SDL_PixelFormat_SDL_Ashift);
	tolua_variable(L,"Rmask",tolua_get_SDL_Rmask,Let_SDL_PixelFormat_SDL_Rmask);
	tolua_variable(L,"Gmask",tolua_get_SDL_Gmask,Let_SDL_PixelFormat_SDL_Gmask);
	tolua_variable(L,"Bmask",tolua_get_SDL_Bmask,Let_SDL_PixelFormat_SDL_Bmask);
	tolua_variable(L,"Amask",tolua_get_SDL_Amask,Let_SDL_PixelFormat_SDL_Amask);
	tolua_variable(L,"colorkey",tolua_get_SDL_colorkey,Let_SDL_PixelFormat_SDL_colorkey);
	tolua_variable(L,"alpha",tolua_get_SDL_alpha,Let_SDL_PixelFormat_SDL_alpha);
	tolua_endmodule(L);
	tolua_cclass(L,"Surface","Surface","",NULL);
	tolua_beginmodule(L,"Surface");
	tolua_variable(L,"flags",tolua_get_SDL_flags,Let_SDL_Surface_SDL_flags);
	tolua_variable(L,"format",tolua_get_SDL_format_ptr,Let_SDL_Surface_SDL_format_ptr);
	tolua_variable(L,"w",tolua_get_SDL_w_Surface,Let_SDL_Surface_SDL_w);
	tolua_variable(L,"h",tolua_get_SDL_h_Surface,Let_SDL_Surface_SDL_h);
	tolua_variable(L,"pitch",tolua_get_SDL_pitch,Let_SDL_Surface_SDL_pitch);
	tolua_variable(L,"pixels",tolua_get_SDL_pixels,Let_SDL_Surface_SDL_pixels);
	tolua_endmodule(L);
	tolua_constant(L,"SWSURFACE",SDL_SWSURFACE);
	tolua_constant(L,"HWSURFACE",SDL_HWSURFACE);
	tolua_constant(L,"ASYNCBLIT",SDL_ASYNCBLIT);
	tolua_constant(L,"ANYFORMAT",SDL_ANYFORMAT);
	tolua_constant(L,"HWPALETTE",SDL_HWPALETTE);
	tolua_constant(L,"DOUBLEBUF",SDL_DOUBLEBUF);
	tolua_constant(L,"FULLSCREEN",SDL_FULLSCREEN);
	tolua_constant(L,"OPENGL",SDL_OPENGL);
	tolua_constant(L,"OPENGLBLIT",SDL_OPENGLBLIT);
	tolua_constant(L,"RESIZABLE",SDL_RESIZABLE);
	tolua_constant(L,"NOFRAME",SDL_NOFRAME);
	tolua_constant(L,"HWACCEL",SDL_HWACCEL);
	tolua_constant(L,"SRCCOLORKEY",SDL_SRCCOLORKEY);
	tolua_constant(L,"RLEACCELOK",SDL_RLEACCELOK);
	tolua_constant(L,"RLEACCEL",SDL_RLEACCEL);
	tolua_constant(L,"SRCALPHA",SDL_SRCALPHA);
	tolua_constant(L,"PREALLOC",SDL_PREALLOC);
	tolua_cclass(L,"VideoInfo","VideoInfo","",NULL);
	tolua_beginmodule(L,"VideoInfo");
	tolua_variable(L,"hw_available",tolua_get_SDL_hw_available,Let_SDL_VideoInfo_SDL_hw_available);
	tolua_variable(L,"video_mem",tolua_get_SDL_video_mem,Let_SDL_VideoInfo_SDL_video_mem);
	tolua_variable(L,"vfmt",tolua_get_SDL_vfmt_ptr,Let_SDL_VideoInfo_SDL_vfmt_ptr);
	tolua_endmodule(L);
	tolua_constant(L,"YV12_OVERLAY",SDL_YV12_OVERLAY);
	tolua_constant(L,"IYUV_OVERLAY",SDL_IYUV_OVERLAY);
	tolua_constant(L,"YUY2_OVERLAY",SDL_YUY2_OVERLAY);
	tolua_constant(L,"UYVY_OVERLAY",SDL_UYVY_OVERLAY);
	tolua_constant(L,"YVYU_OVERLAY",SDL_YVYU_OVERLAY);
	tolua_cclass(L,"Overlay","Overlay","",NULL);
	tolua_beginmodule(L,"Overlay");
	tolua_endmodule(L);
	tolua_constant(L,"GL_RED_SIZE",SDL_GL_RED_SIZE);
	tolua_constant(L,"GL_GREEN_SIZE",SDL_GL_GREEN_SIZE);
	tolua_constant(L,"GL_BLUE_SIZE",SDL_GL_BLUE_SIZE);
	tolua_constant(L,"GL_ALPHA_SIZE",SDL_GL_ALPHA_SIZE);
	tolua_constant(L,"GL_BUFFER_SIZE",SDL_GL_BUFFER_SIZE);
	tolua_constant(L,"GL_DOUBLEBUFFER",SDL_GL_DOUBLEBUFFER);
	tolua_constant(L,"GL_DEPTH_SIZE",SDL_GL_DEPTH_SIZE);
	tolua_constant(L,"GL_STENCIL_SIZE",SDL_GL_STENCIL_SIZE);
	tolua_constant(L,"GL_ACCUM_RED_SIZE",SDL_GL_ACCUM_RED_SIZE);
	tolua_constant(L,"GL_ACCUM_GREEN_SIZE",SDL_GL_ACCUM_GREEN_SIZE);
	tolua_constant(L,"GL_ACCUM_BLUE_SIZE",SDL_GL_ACCUM_BLUE_SIZE);
	tolua_constant(L,"GL_ACCUM_ALPHA_SIZE",SDL_GL_ACCUM_ALPHA_SIZE);
	tolua_constant(L,"LOGPAL",SDL_LOGPAL);
	tolua_constant(L,"PHYSPAL",SDL_PHYSPAL);
	tolua_function(L,"VideoInit",LDL_SDL_SDL_VideoInit00);
	tolua_function(L,"VideoQuit",LDL_SDL_SDL_VideoQuit00);
	tolua_function(L,"VideoDriverName",LDL_SDL_SDL_VideoDriverName00);
	tolua_function(L,"GetVideoSurface",LDL_SDL_SDL_GetVideoSurface00);
	tolua_function(L,"GetVideoInfo",LDL_SDL_SDL_GetVideoInfo00);
	tolua_function(L,"VideoModeOK",LDL_SDL_SDL_VideoModeOK00);
	tolua_function(L,"SetVideoMode",LDL_SDL_SDL_SetVideoMode00);
	tolua_function(L,"UpdateRects",LDL_SDL_SDL_UpdateRects00);
	tolua_function(L,"UpdateRect",LDL_SDL_SDL_UpdateRect00);
	tolua_function(L,"Flip",LDL_SDL_SDL_Flip00);
	tolua_function(L,"SetGamma",LDL_SDL_SDL_SetGamma00);
	tolua_function(L,"SetGammaRamp",LDL_SDL_SDL_SetGammaRamp00);
	tolua_function(L,"GetGammaRamp",LDL_SDL_SDL_GetGammaRamp00);
	tolua_function(L,"SetColors",LDL_SDL_SDL_SetColors00);
	tolua_function(L,"SetPalette",LDL_SDL_SDL_SetPalette00);
	tolua_function(L,"MapRGB",LDL_SDL_SDL_MapRGB00);
	tolua_function(L,"MapRGBA",LDL_SDL_SDL_MapRGBA00);
	tolua_function(L,"GetRGB",LDL_SDL_SDL_GetRGB00);
	tolua_function(L,"GetRGBA",LDL_SDL_SDL_GetRGBA00);
	tolua_function(L,"CreateRGBSurface",LDL_SDL_SDL_CreateRGBSurface00);
	tolua_function(L,"CreateRGBSurfaceFrom",LDL_SDL_SDL_CreateRGBSurfaceFrom00);
	tolua_function(L,"FreeSurface",LDL_SDL_SDL_FreeSurface00);
	tolua_function(L,"LockSurface",LDL_SDL_SDL_LockSurface00);
	tolua_function(L,"UnlockSurface",LDL_SDL_SDL_UnlockSurface00);
	tolua_function(L,"LoadBMP_RW",LDL_SDL_SDL_LoadBMP_RW00);
	tolua_function(L,"LoadBMP",LDL_SDL_SDL_LoadBMP00);
	tolua_function(L,"SaveBMP_RW",LDL_SDL_SDL_SaveBMP_RW00);
	tolua_function(L,"SaveBMP",LDL_SDL_SDL_SaveBMP00);
	tolua_function(L,"SetColorKey",LDL_SDL_SDL_SetColorKey00);
	tolua_function(L,"SetAlpha",LDL_SDL_SDL_SetAlpha00);
	tolua_function(L,"SetClipRect",LDL_SDL_SDL_SetClipRect00);
	tolua_function(L,"GetClipRect",LDL_SDL_SDL_GetClipRect00);
	tolua_function(L,"ConvertSurface",LDL_SDL_SDL_ConvertSurface00);
	tolua_function(L,"UpperBlit",LDL_SDL_SDL_UpperBlit00);
	tolua_function(L,"LowerBlit",LDL_SDL_SDL_LowerBlit00);
	tolua_function(L,"FillRect",LDL_SDL_SDL_FillRect00);
	tolua_function(L,"DisplayFormat",LDL_SDL_SDL_DisplayFormat00);
	tolua_function(L,"DisplayFormatAlpha",LDL_SDL_SDL_DisplayFormatAlpha00);
	tolua_function(L,"CreateYUVOverlay",LDL_SDL_SDL_CreateYUVOverlay00);
	tolua_function(L,"LockYUVOverlay",LDL_SDL_SDL_LockYUVOverlay00);
	tolua_function(L,"UnlockYUVOverlay",LDL_SDL_SDL_UnlockYUVOverlay00);
	tolua_function(L,"DisplayYUVOverlay",LDL_SDL_SDL_DisplayYUVOverlay00);
	tolua_function(L,"FreeYUVOverlay",LDL_SDL_SDL_FreeYUVOverlay00);
	tolua_function(L,"GL_LoadLibrary",LDL_SDL_SDL_GL_LoadLibrary00);
	tolua_function(L,"GL_GetProcAddress",LDL_SDL_SDL_GL_GetProcAddress00);
	tolua_function(L,"GL_SetAttribute",LDL_SDL_SDL_GL_SetAttribute00);
	tolua_function(L,"GL_GetAttribute",LDL_SDL_SDL_GL_GetAttribute00);
	tolua_function(L,"GL_SwapBuffers",LDL_SDL_SDL_GL_SwapBuffers00);
	tolua_function(L,"GL_UpdateRects",LDL_SDL_SDL_GL_UpdateRects00);
	tolua_function(L,"GL_Lock",LDL_SDL_SDL_GL_Lock00);
	tolua_function(L,"GL_Unlock",LDL_SDL_SDL_GL_Unlock00);
	tolua_function(L,"WM_SetCaption",LDL_SDL_SDL_WM_SetCaption00);
	tolua_function(L,"WM_GetCaption",LDL_SDL_SDL_WM_GetCaption00);
	tolua_function(L,"WM_SetIcon",LDL_SDL_SDL_WM_SetIcon00);
	tolua_function(L,"WM_IconifyWindow",LDL_SDL_SDL_WM_IconifyWindow00);
	tolua_function(L,"WM_ToggleFullScreen",LDL_SDL_SDL_WM_ToggleFullScreen00);
	tolua_constant(L,"GRAB_QUERY",SDL_GRAB_QUERY);
	tolua_constant(L,"GRAB_OFF",SDL_GRAB_OFF);
	tolua_constant(L,"GRAB_ON",SDL_GRAB_ON);
	tolua_constant(L,"GRAB_FULLSCREEN",SDL_GRAB_FULLSCREEN);
	tolua_function(L,"WM_GrabInput",LDL_SDL_SDL_WM_GrabInput00);
	tolua_constant(L,"MAJOR_VERSION",SDL_MAJOR_VERSION);
	tolua_constant(L,"MINOR_VERSION",SDL_MINOR_VERSION);
	tolua_constant(L,"PATCHLEVEL",SDL_PATCHLEVEL);
	tolua_cclass(L,"FILE","FILE","",NULL);
	tolua_beginmodule(L,"FILE");
	tolua_endmodule(L);
	tolua_cclass(L,"RWops","RWops","",NULL);
	tolua_beginmodule(L,"RWops");
	tolua_endmodule(L);
	tolua_function(L,"RWFromFile",LDL_SDL_SDL_RWFromFile00);
	tolua_function(L,"RWFromFP",LDL_SDL_SDL_RWFromFP00);
	tolua_function(L,"RWFromMem",LDL_SDL_SDL_RWFromMem00);
	tolua_function(L,"AllocRW",LDL_SDL_SDL_AllocRW00);
	tolua_function(L,"FreeRW",LDL_SDL_SDL_FreeRW00);
	tolua_constant(L,"INIT_TIMER",SDL_INIT_TIMER);
	tolua_constant(L,"INIT_AUDIO",SDL_INIT_AUDIO);
	tolua_constant(L,"INIT_VIDEO",SDL_INIT_VIDEO);
	tolua_constant(L,"INIT_CDROM",SDL_INIT_CDROM);
	tolua_constant(L,"INIT_JOYSTICK",SDL_INIT_JOYSTICK);
	tolua_constant(L,"INIT_NOPARACHUTE",SDL_INIT_NOPARACHUTE);
	tolua_constant(L,"INIT_EVENTTHREAD",SDL_INIT_EVENTTHREAD);
	tolua_constant(L,"INIT_EVERYTHING",SDL_INIT_EVERYTHING);
	tolua_function(L,"Init",LDL_SDL_SDL_Init00);
	tolua_function(L,"InitSubSystem",LDL_SDL_SDL_InitSubSystem00);
	tolua_function(L,"QuitSubSystem",LDL_SDL_SDL_QuitSubSystem00);
	tolua_function(L,"WasInit",LDL_SDL_SDL_WasInit00);
	tolua_function(L,"Quit",LDL_SDL_SDL_Quit00);
	tolua_endmodule(L);
	tolua_endmodule(L);
}