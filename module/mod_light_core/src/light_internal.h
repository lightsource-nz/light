
#ifndef __LIGHT_INTERNAL_H
#define __LIGHT_INTERNAL_H

#include <light.h>

#define LIGHT_UNIQUE_ID()   __COUNTER__

extern light_module_t _light_modules[LIGHT_DEFINED_MODULES_MAX];

#define LIGHT_MODULE_IMPLEMENT(name, module) \
        extern uint8_t mod_init_## LIGHT_UNIQUE_ID ##() LIGHT_ATTR_PREMAIN \
        { _light_modules[_light_module_count++] = &(module) }

#endif
