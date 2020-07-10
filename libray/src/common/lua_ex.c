#include "lua_ex.h"

#include "common/log.h"

int luar_register_module(lua_State* L, const wrapped_module m)
{
    RAY_LOG_INFO("Register lua module %s", module_get_name(m.module));
    
    lua_newtable(L);
    if (m.functions)
    {
        for (luaL_Reg* i = (luaL_Reg*)m.functions; i->func; i++)
        {
            lua_pushcfunction(L, i->func);
            lua_setfield(L, -2, i->name);
        }
    }

    lua_getglobal(L, "ray");
    lua_pushvalue(L, -2);
    lua_setfield(L, -2, module_get_name(m.module));
    lua_pop(L, 2);

    return 0;
}
