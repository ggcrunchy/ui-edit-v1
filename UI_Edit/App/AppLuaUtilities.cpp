#include "AppGeneral.h"
#include <iostream>

// @brief Posts an error and prints a string
void Post (lua_State * L, char const * message)
{
	for (int level = 0; ; ++level)
	{
		lua_Debug debug = { 0 };

		if (lua_getstack(L, level, &debug) == 0) break;

		lua_getinfo(L, "Sl", &debug);

		std::cerr << "Level " << level << std::endl;
		std::cerr << "source: " << debug.source << std::endl;
		std::cerr << "short_src: " << debug.short_src << std::endl;
		std::cerr << "what: " << debug.what << std::endl;
		
		if (debug.currentline != -1)
		{
			std::cerr << "currentline: " << debug.currentline << std::endl;
			std::cerr << "linedefined: " << debug.linedefined << std::endl;
		}

		if (debug.name != 0)
		{
			std::cerr << "name: " << debug.name << std::endl;
			std::cerr << "namewhat: " << debug.namewhat << std::endl;
		}

		std::cerr << "nups: " << debug.nups << std::endl;
	}

	std::cout << message << std::endl;

	lua_pushstring(L, message);
	lua_error(L);
}

/// @brief Verifies that a Lua C function is given the correct number of arguments
void Count (lua_State * L, int count)
{
	CountIn(L, count, count);
}

/// @brief Verifies that a Lua C function is given a valid number of arguments
void CountIn (lua_State * L, int min, int max)
{
	int size = lua_gettop(L);

	if (size >= min && size <= max) return;
#ifndef NDEBUG
	if (size < min) Post(L, "Invalid argument count: too few arguments.");

	else Post(L, "Invalid argument count: too many arguments.");
#endif // NDEBUG
}

/// @brief Validates and returns a Uint32 argument
Uint32 U (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<Uint32>(lua_tonumber(L, index));
}

/// @brief Validates and returns a Uint8 argument
Uint8 U8 (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<Uint8>(lua_tonumber(L, index));
}

/// @brief Validates and returns a Uint16 argument
Uint16 U16 (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<Uint16>(lua_tonumber(L, index));
}

/// @brief Validates and returns a Sint32 argument
Sint32 S32 (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<Sint32>(lua_tonumber(L, index));
}

/// @brief Validates and returns a Sint16 argument
Sint16 S16 (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<Sint16>(lua_tonumber(L, index));
}

/// @brief Validates and returns an int argument
int I (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<int>(lua_tonumber(L, index));
}

/// @brief Validates and return a float argument
float F (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isnumber(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a number.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<float>(lua_tonumber(L, index));
}

/// Validates and returns an SDL_bool argument
SDL_bool B (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isboolean(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a boolean.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return static_cast<SDL_bool>(lua_toboolean(L, index));
}

/// @brief Validates and returns a void * argument
void * UD (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isuserdata(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a userdata.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return lua_touserdata(L, index);
}

/// @brief Validates and returns a char const * argument
char const * S (lua_State * L, int index)
{
#ifndef NDEBUG
	if (!lua_isstring(L, index))
	{
		char Buf[64];	sprintf(Buf, "Argument %i is not a string.", index);

		Post(L, Buf);
	}
#endif // NDEBUG
	return lua_tostring(L, index);
}

/// @brief NOP Lua C function
int NOP (lua_State * L)
{
	return 0;
}