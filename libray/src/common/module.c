#include "module.h"

module* ray_modules[1];

ray_module_type module_get_type(module* m)
{
    return m->module_type;
}

const char* module_get_name(module* m)
{
    return m->module_name;
}

void module_set(ray_module_type type, module* m)
{
    ray_modules[type] = m;
}

module* module_get(const ray_module_type type)
{
    return ray_modules[type];
}
