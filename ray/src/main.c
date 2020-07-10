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

    lua_getglobal(L, "require");
    lua_pushstring(L, "scripts.boot");
    lua_call(L, 1, 1);

    lua_newthread(L);
    lua_pushvalue(L, -2);
    int stackpos = lua_gettop(L);
    while (lua_resume(L, NULL, 0) == LUA_YIELD)
        lua_pop(L, lua_gettop(L) - stackpos);

    lua_close(L);
    return 0;
}
