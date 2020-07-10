#include "ray.h"

#include "timer/timer_wrap.h"

int ray_lua_init(lua_State* L)
{
    lua_open_ray_timer(L);
    return 0;
}
