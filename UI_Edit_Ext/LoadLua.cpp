#include "UI_Edit_Ext.h"
#include <iostream>
#include <cassert>
extern "C" 
{
#include <lualib.h>
#include <lauxlib.h>
}

static int SetupGraphics (lua_State * L)
{
	int width = static_cast<int>(lua_tonumber(L, 1));
	int height = static_cast<int>(lua_tonumber(L, 2));
	int bpp = static_cast<int>(lua_tonumber(L, 3));
	SDL_bool bFullScreen = static_cast<SDL_bool>(lua_toboolean(L, 4));

	SetupGraphics(width, height, bpp, bFullScreen);

	return 0;
}

static int CloseGraphics (lua_State * L)
{
	CloseGraphics();

	return 0;
}

static int SetVideoMode (lua_State * L)
{
	int width = static_cast<int>(lua_tonumber(L, 1));
	int height = static_cast<int>(lua_tonumber(L, 2));
	int bpp = static_cast<int>(lua_tonumber(L, 3));
	SDL_bool bFullScreen = static_cast<SDL_bool>(lua_toboolean(L, 4));

	SetVideoMode(width, height, bpp, bFullScreen);

	return 0;
}

static int GetVideoSize (lua_State * L)
{
	Uint32 width, height;	GetVideoSize(&width, &height);

	lua_pushnumber(L, width);
	lua_pushnumber(L, height);

	return 2;
}

static int PrepareFrame (lua_State * L)
{
	PrepareFrame();

	return 0;
}

static int DrawFrame (lua_State * L)
{
	DrawFrame();

	return 0;
}

static int ReloadImage (lua_State * L)
{
	ReloadImage(lua_tostring(L, 1));

	return 0;
}

static int LoadPicture (lua_State * L)
{
	char const * name = lua_tostring(L, 1);
	float fS0 = static_cast<float>(lua_tonumber(L, 2));
	float fT0 = static_cast<float>(lua_tonumber(L, 3));
	float fS1 = static_cast<float>(lua_tonumber(L, 4));
	float fT1 = static_cast<float>(lua_tonumber(L, 5));

	Picture_h picture;

	if (LoadPicture(name, fS0, fT0, fS1, fT1, &picture) == 0) lua_pushnil(L);

	else lua_pushlightuserdata(L, picture);

	return 1;
}

static int DrawPicture (lua_State * L)
{
	Picture_h picture = lua_touserdata(L, 1);
	float fX = static_cast<float>(lua_tonumber(L, 2));
	float fY = static_cast<float>(lua_tonumber(L, 3));
	float fW = static_cast<float>(lua_tonumber(L, 4));
	float fH = static_cast<float>(lua_tonumber(L, 5));

	DrawPicture(picture, fX, fY, fW, fH);

	return 0;
}

static int UnloadPicture (lua_State * L)
{
	UnloadPicture(lua_touserdata(L, 1));

	return 0;
}

static int LoadFont (lua_State * L)
{
	char const * name = lua_tostring(L, 1);
	int size = static_cast<int>(lua_tonumber(L, 2));

	Font_h font;

	if (LoadFont(name, size, &font) == 0) lua_pushnil(L);

	else lua_pushlightuserdata(L, font);

	return 1;
}

static int UnloadFont (lua_State * L)
{
	UnloadFont(lua_touserdata(L, 1));

	return 0;
}

static int GetTextSize (lua_State * L)
{
	Font_h font = lua_touserdata(L, 1);
	char const * text = lua_tostring(L, 2);

	int w, h;	GetTextSize(font, text, &w, &h);

	lua_pushnumber(L, w);
	lua_pushnumber(L, h);

	return 2;
}

static int LoadTextImage (lua_State * L)
{
	Font_h font = lua_touserdata(L, 1);
	char const * text = lua_tostring(L, 2);
	
	SDL_Color color;

	color.r = static_cast<Uint8>(lua_tonumber(L, 3));
	color.g = static_cast<Uint8>(lua_tonumber(L, 4));
	color.b = static_cast<Uint8>(lua_tonumber(L, 5));

	TextImage_h textImage;

	if (LoadTextImage(font, text, color, &textImage) == 0) lua_pushnil(L);

	else lua_pushlightuserdata(L, textImage);

	return 1;
}

static int DrawTextImage (lua_State * L)
{
	TextImage_h textImage = lua_touserdata(L, 1);
	float fX = static_cast<float>(lua_tonumber(L, 2));
	float fY = static_cast<float>(lua_tonumber(L, 3));
	float fW = static_cast<float>(lua_tonumber(L, 4));
	float fH = static_cast<float>(lua_tonumber(L, 5));

	DrawTextImage(textImage, fX, fY, fW, fH);

	return 0;
}

static int DrawClippedTextImage (lua_State * L)
{
	TextImage_h textImage = lua_touserdata(L, 1);
	float fX = static_cast<float>(lua_tonumber(L, 2));
	float fY = static_cast<float>(lua_tonumber(L, 3));
	float fW = static_cast<float>(lua_tonumber(L, 4));
	float fH = static_cast<float>(lua_tonumber(L, 5));
	float fMW = static_cast<float>(lua_tonumber(L, 6));
	float fMH = static_cast<float>(lua_tonumber(L, 7));

	DrawClippedTextImage(textImage, fX, fY, fW, fH, fMW, fMH);

	return 0;
}

static int UnloadTextImage (lua_State * L)
{
	UnloadTextImage(lua_touserdata(L, 1));

	return 0;
}

static int DrawBox (lua_State * L)
{
	float fX = static_cast<float>(lua_tonumber(L, 1));
	float fY = static_cast<float>(lua_tonumber(L, 2));
	float fW = static_cast<float>(lua_tonumber(L, 3));
	float fH = static_cast<float>(lua_tonumber(L, 4));
	float fR = static_cast<float>(lua_tonumber(L, 5));
	float fG = static_cast<float>(lua_tonumber(L, 6));
	float fB = static_cast<float>(lua_tonumber(L, 7));

	DrawBox(fX, fY, fW, fH, fR, fG, fB);

	return 0;
}

static int DrawLine (lua_State * L)
{
	float fSX = static_cast<float>(lua_tonumber(L, 1));
	float fSY = static_cast<float>(lua_tonumber(L, 2));
	float fEX = static_cast<float>(lua_tonumber(L, 3));
	float fEY = static_cast<float>(lua_tonumber(L, 4));
	float fR = static_cast<float>(lua_tonumber(L, 5));
	float fG = static_cast<float>(lua_tonumber(L, 6));
	float fB = static_cast<float>(lua_tonumber(L, 7));

	DrawLine(fSX, fSY, fEX, fEY, fR, fG, fB);

	return 0;
}

static int DrawGrid (lua_State * L)
{
	float fX = static_cast<float>(lua_tonumber(L, 1));
	float fY = static_cast<float>(lua_tonumber(L, 2));
	float fW = static_cast<float>(lua_tonumber(L, 3));
	float fH = static_cast<float>(lua_tonumber(L, 4));

	Uint32 xCuts = static_cast<Uint32>(lua_tonumber(L, 5));
	Uint32 yCuts = static_cast<Uint32>(lua_tonumber(L, 6));

	DrawGrid(fX, fY, fW, fH, xCuts, yCuts);

	return 0;
}


static int Print (lua_State * L)
{
	std::cerr << lua_tostring(L, 1) << std::endl;

	return 0;
}

///
/// 
///
static const luaL_reg RenderFuncs[] = {
	{ "SetupGraphics", SetupGraphics },
	{ "CloseGraphics", CloseGraphics },
	{ "SetVideoMode", SetVideoMode },
	{ "GetVideoSize", GetVideoSize },
	{ "PrepareFrame", PrepareFrame },
	{ "DrawFrame", DrawFrame },
	{ "ReloadImage", ReloadImage },
	{ "LoadPicture", LoadPicture },
	{ "DrawPicture", DrawPicture },
	{ "UnloadPicture", UnloadPicture },
	{ "LoadFont", LoadFont },
	{ "UnloadFont", UnloadFont },
	{ "GetTextSize", GetTextSize },
	{ "LoadTextImage", LoadTextImage },
	{ "DrawTextImage", DrawTextImage },
	{ "DrawClippedTextImage", DrawClippedTextImage },
	{ "UnloadTextImage", UnloadTextImage },
	{ "DrawBox", DrawBox },
	{ "DrawLine", DrawLine },
	{ "DrawGrid", DrawGrid },
	{ 0, 0 }
};

///
///
///
static const luaL_reg MessageFuncs[] = {
	{ "Print", Print },
	{ 0, 0 }
};

/// @brief
/// @param state
/// @return
DECLSPEC int LoadLuaFunctions (lua_State * state)
{
	assert(state != 0);

	luaL_openlib(state, "Render", RenderFuncs, 0);
	luaL_openlib(state, "Message", MessageFuncs, 0);

	return 1;
}