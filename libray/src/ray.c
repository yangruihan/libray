#include "ray.h"

// SDL
#include <SDL.h>

// SDL GPU
#include <SDL_gpu.h>

// Lua
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "timer/timer_wrap.h"

static lua_State *L;
static bool is_running = true;

static int init_SDL()
{
    GPU_SetDebugLevel(GPU_DEBUG_LEVEL_MAX);

    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG, SDL_TRUE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

    // todo lua boot

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
    GPU_Target *screen = GPU_Init(1280, 720, GPU_DEFAULT_INIT_FLAGS);

    // Main loop
    SDL_Event event;
    while (is_running)
    {
        // Handle events
        while (SDL_PollEvent(&event))
        {
        }

        GPU_Clear(screen);
        GPU_Flip(screen);
        SDL_Delay(1);
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
