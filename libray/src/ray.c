#include "ray.h"

// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "timer/timer_wrap.h"

static int ray_lua_init(lua_State* L)
{
    lua_open_ray_timer(L);
    return 0;
}

int ray_start()
{
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    lua_newtable(L);
    lua_setglobal(L, "ray");

    ray_lua_init(L);

    lua_getglobal(L, "require");
    lua_pushstring(L, "scripts.ray.boot");
    lua_call(L, 1, 1);

    lua_newthread(L);
    lua_pushvalue(L, -2);
    int stackpos = lua_gettop(L);
    while (lua_resume(L, NULL, 0) == LUA_YIELD)
        lua_pop(L, lua_gettop(L) - stackpos);

    lua_close(L);

    return 0;
}
