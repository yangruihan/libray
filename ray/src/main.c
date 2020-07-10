#define SDL_MAIN_HANDLED

#include <stdio.h>
#include <SDL.h>

// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

int main(int argc, char** argv)
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luaL_dostring(L, "require('scripts.boot')");

    lua_close(L);
    return 0;
}
