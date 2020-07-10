#include "timer_wrap.h"

#include "timer.h"
#include "common/log.h"
#include "common/lua_ex.h"

DEFINE_LUA_FUNC(step)
{
    lua_pushnumber(L, timer_step(ray_get_timer()));
    return 1;
}

DEFINE_LUA_FUNC(get_delta)
{
    lua_pushnumber(L, timer_get_delta(ray_get_timer()));
    return 1;
}

DEFINE_LUA_FUNC(get_fps)
{
    lua_pushnumber(L, timer_get_fps(ray_get_timer()));
    return 1;
}

DEFINE_LUA_FUNC(get_average_delta)
{
    lua_pushnumber(L, timer_get_average_delta(ray_get_timer()));
    return 1;
}

DEFINE_LUA_FUNC(sleep)
{
    timer_sleep(luaL_checknumber(L, 1));
    return 0;
}

DEFINE_LUA_FUNC(get_time)
{
    lua_pushnumber(L, timer_get_time());
    return 1;
}

static const luaL_Reg functions[] =
{
    {"step", step},
    {"getDelta", get_delta},
    {"getFPS", get_fps},
    {"getAverageDelta", get_average_delta},
    {"sleep", sleep},
    {"getTime", get_time},
    {NULL, NULL}
};

int lua_open_ray_timer(lua_State* L)
{
    timer* t = ray_get_timer();
    if (!t)
    {
        RAY_LOG_FATAL("Lua open ray timer error, timer is nullptr");
        return 0;
    }

    wrapped_module w;
    w.module = (module*)t;
    w.functions = functions;
    w.types = 0;

    return luar_register_module(L, w);
}
