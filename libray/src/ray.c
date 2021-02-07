#include "ray.h"

// SDL
#include <SDL.h>

// SDL GPU
#include <SDL_gpu.h>

// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "common/log.h"

#include "timer/timer.h"
#include "timer/timer_wrap.h"

static lua_State *L;
static GPU_Target* screen;
static bool is_running = true;

/**
 * Lua function traceback
 */
static int traceback(lua_State *L)
{
    lua_getglobal(L, "debug");
    lua_getfield(L, -1, "traceback");
    lua_pushvalue(L, 1);
    lua_pushinteger(L, 2);
    lua_call(L, 2, 1);
    return 1;
}

static int call_lua(const char *func_name)
{
    lua_pushcfunction(L, traceback);
    lua_getglobal(L, func_name);

    int ret = lua_pcall(L, 0, 0, lua_gettop(L) - 1);
    if (ret != 0)
    {
        const char *error = lua_tostring(L, -1);

        RAY_LOG_ERROR("Call lua error: %s", error);

        lua_getglobal(L, "ray_error");
        lua_pushstring(L, error);
        lua_pcall(L, 1, 0, 0);
    }

    return ret;
}

static int init_SDL()
{
    GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

    screen = GPU_Init(1280, 720, GPU_DEFAULT_INIT_FLAGS);
    if (!screen)
        return -1;

    return 0;
}

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

    // load boot.lua
    int ret = luaL_dostring(L, "require('scripts.ray.boot')");
    if (ret) 
    {
        RAY_LOG_ERROR("Load boot.lua error: %s", lua_tostring(L, -1));
        return ret;
    }

    return 0;
}

static int init()
{
    init_SDL();

    init_lua();

    return 0;
}

static int main_loop()
{
    // call lua load
    RAY_LOG_INFO("Call ray_load");
    call_lua("ray_load");

    timer *timer = ray_get_timer();

    // main loop
    SDL_Event event;

    SDL_Color color = {.r = 255, .g = 255, .b = 255, .a = 255};

    while (is_running)
    {
        // update timer
        timer_step(timer);

        // handle events
        while (SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
                is_running = false;
            else if(event.type == SDL_KEYDOWN)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                    is_running = false;
            }
        }

        // call lua update
        call_lua("ray_update");

        GPU_ClearRGBA(screen, 255, 0, 255, 255);

        GPU_Line(screen, 320, 200, 300, 240, color);
        GPU_Line(screen, 300, 240, 340, 240, color);
        GPU_Line(screen, 340, 240, 320, 200, color);

        // call lua draw
        call_lua("ray_draw");

        GPU_Flip(screen);

        timer_sleep(0.001);
    }

    return 0;
}

static int clear()
{
    lua_close(L);

    GPU_Quit();

    return 0;
}

int ray_start()
{
    init();

    main_loop();

    clear();

    return 0;
}
