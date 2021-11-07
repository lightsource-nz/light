
#ifndef __LIGHT_INTERNAL_H
#define __LIGHT_INTERNAL_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

#define LIGHT_UNIQUE_ID()   __COUNTER__

#define CAT_I(a,b) a##b
#define CAT(a,b) CAT_I(a, b)

extern light_module_t *_light_modules[LIGHT_DEFINED_MODULES_MAX];
extern uint8_t _light_module_count;

#define LIGHT_MODULE_IMPLEMENT(module) \
        LIGHT_ATTR_PREMAIN uint8_t CAT(mod_init_generated, LIGHT_UNIQUE_ID())() \
        { _light_modules[_light_module_count++] = &(module); }

#endif
