#include "ray.h"

// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "timer/timer_wrap.h"

static lua_State* L;

static int init_lua()
{
    // create lua vm
    L = luaL_newstate();

    // open lua builtin libs
    luaL_openlibs(L);

    // create ray global table
    lua_newtable(L);
    lua_setglobal(L, "ray");

    // load timer lib
    lua_open_ray_timer(L);

    return 0;
}

static int init()
{
    return init_lua();
}

static int main_loop()
{
    lua_getglobal(L, "require");
    lua_pushstring(L, "scripts.ray.boot");
    lua_call(L, 1, 1);

    lua_newthread(L);
    lua_pushvalue(L, -2);
    const int stack_pos = lua_gettop(L);

    while (lua_resume(L, NULL, 0) == LUA_YIELD)
        lua_pop(L, lua_gettop(L) - stack_pos);
    
    lua_pop(L, 2);
    return 0;
}

static int clear()
{
    lua_close(L);
    return 0;
}

int ray_start()
{
    init();

    main_loop();

    clear();

    return 0;
}
