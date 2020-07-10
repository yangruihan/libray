#ifndef LIBRAY_MODULE_H_
#define LIBRAY_MODULE_H_

typedef enum
{
    ray_mt_timer = 0,
} ray_module_type;

typedef struct
{
    ray_module_type module_type;
    char*           module_name;
} module;

ray_module_type module_get_type(module* m);
const char*     module_get_name(module* m);

void            module_set(ray_module_type type, module * m);
module*         module_get(ray_module_type type);

#endif // LIBRAY_MODULE_H_
