#ifndef LIBRAY_LUA_EX_H_
#define LIBRAY_LUA_EX_H_

#include "lauxlib.h"
#include "common/module.h"

#define DEFINE_LUA_FUNC(func_name) \
    static int func_name(lua_State* L)

typedef struct
{
    module* module;
    const luaL_Reg* functions;
    const lua_CFunction* types;
} wrapped_module;

int luar_register_module(lua_State* L, wrapped_module m);

#endif
