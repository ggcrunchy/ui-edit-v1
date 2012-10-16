#include <SDL/SDL_main.h>
#include "AppGeneral.h"

int main (int argc, char * argv[])
{
	////////////////////////////////////////////////////////////////////////////////////
	// Create a Lua virtual machine, load its standard libraries, populate it with some
	// useful tools(UI, SDL, dirent), and load the dynamic library routines.
	////////////////////////////////////////////////////////////////////////////////////
	lua_State * VM = lua_open();

	luaopen_base(VM);
	luaopen_table(VM);
	luaopen_io(VM);
	luaopen_string(VM);
	luaopen_math(VM);
	luaopen_debug(VM);

	BindUI(VM);
	BindSDL(VM);
	BindDirent(VM);

	LoadLuaFunctions(VM);

	//////////////////////////////////////////////////////////
	// Boot and run the application, and close Lua when done.
	//////////////////////////////////////////////////////////
	lua_dofile(VM, "Scripts/Boot.txt");
	lua_close(VM);

	return 0;
}