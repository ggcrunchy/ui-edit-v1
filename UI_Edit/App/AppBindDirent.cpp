#include <dirent.h>
#include <tolua.h>
#include "AppGeneral.h"

static DIR * D (lua_State * L)
{
	if (!tolua_isusertype(L, 1, "DIR", 0, 0)) return 0;

	return static_cast<DIR*>(tolua_tousertype(L, 1, 0));
}

static struct dirent * E (lua_State * L)
{
	if (!tolua_isusertype(L, 1, "struct dirent", 0, 0)) return 0;

	return static_cast<struct dirent*>(tolua_tousertype(L, 1, 0));
}

static int OpenDir (lua_State * L)
{
	DIR * dir = opendir(S(L, 1));

	if (dir != 0) tolua_pushusertype(L, dir, "DIR");

	else lua_pushnil(L);

	return 1;
}

static int ReadDir (lua_State * L)
{
	struct dirent * entry = readdir(D(L));

	if (entry != 0) tolua_pushusertype(L, entry, "struct dirent");

	else lua_pushnil(L);

	return 1;
}

static int CloseDir (lua_State * L)
{
	DIR * dir = D(L);

	if (dir != 0) closedir(dir);

	return 0;
}

static int RewindDir (lua_State * L)
{
	DIR * dir = D(L);

	if (dir != 0) rewinddir(dir);

	return 0;
}

static int TellDir (lua_State * L)
{
	DIR * dir = D(L);

	if (dir != 0)
	{
		long index = telldir(dir);

		lua_pushnumber(L, index);
	}

	else lua_pushnil(L);

	return 1;
}

static int SeekDir (lua_State * L)
{
	DIR * dir = D(L);

	if (dir != 0 && lua_isnumber(L, 2)) seekdir(dir, static_cast<long>(lua_tonumber(L, 2)));

	return 0;
}

static int DirentGet_d_namlen (lua_State * L)
{
	struct dirent * entry = E(L);

	if (entry != 0) lua_pushnumber(L, entry->d_namlen);

	else lua_pushnil(L);

	return 1;
}

static int DirentGet_d_name (lua_State * L)
{
	struct dirent * entry = E(L);

	if (entry != 0) lua_pushstring(L, entry->d_name);

	else lua_pushnil(L);

	return 1;
}

static int DirentNOP (lua_State * L)
{
	return 0;
}

/// @brief Binds dirent to the scripting system
void BindDirent (lua_State * L)
{
	tolua_open(L);
	tolua_usertype(L, "DIR");
	tolua_usertype(L, "struct dirent");
	tolua_module(L, 0, 0);
	tolua_beginmodule(L, 0);
	tolua_module(L, "dirent", 0);
	tolua_beginmodule(L, "dirent");
	tolua_cclass(L, "DIR", "DIR", "", 0);
	tolua_beginmodule(L, "DIR");
	tolua_endmodule(L);
	tolua_cclass(L, "struct dirent", "struct dirent", "", 0);
	tolua_beginmodule(L, "struct dirent");
	tolua_variable(L, "d_namlen", DirentGet_d_namlen, DirentNOP);
	tolua_variable(L, "d_name", DirentGet_d_name, DirentNOP);
	tolua_endmodule(L);
	tolua_function(L, "open", OpenDir);
	tolua_function(L, "read", ReadDir);
	tolua_function(L, "close", CloseDir);
	tolua_function(L, "rewind", RewindDir);
	tolua_function(L, "tell", TellDir);
	tolua_function(L, "seek", SeekDir);
	tolua_endmodule(L);
	tolua_endmodule(L);
}
