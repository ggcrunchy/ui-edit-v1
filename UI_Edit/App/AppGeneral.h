#ifndef APP_APP_GENERAL_H
#define APP_APP_GENERAL_H

#include <SDL/SDL_types.h>
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#include "../../UI_Edit_Ext/UI_Edit_Ext.h"

void BindUI (lua_State * L);
void BindSDL (lua_State * L);
void BindDirent (lua_State * L);

void Count (lua_State * L, int count);
void CountIn (lua_State * L, int min, int max);
Uint32 U (lua_State * L, int index);
Uint8 U8 (lua_State * L, int index);
Uint16 U16 (lua_State * L, int index);
Sint32 S32 (lua_State * L, int index);
Sint16 S16 (lua_State * L, int index);
int I (lua_State * L, int index);
float F (lua_State * L, int index);
SDL_bool B (lua_State * L, int index);
void * UD (lua_State * L, int index);
char const * S (lua_State * L, int index);
int NOP (lua_State * L);

#endif // APP_APP_GENERAL_H