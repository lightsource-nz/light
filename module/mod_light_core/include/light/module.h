
#ifndef __LIGHT_MODULE_H
#define __LIGHT_MODULE_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

extern light_module_t *_light_modules[LIGHT_DEFINED_MODULES_MAX];
extern uint8_t _light_module_count;

#define LIGHT_MODULE_IMPLEMENT(module) \
        LIGHT_ATTR_PREMAIN static uint8_t _generated_module_init() \
        { if (_light_module_count < LIGHT_DEFINED_MODULES_MAX) \
                _light_modules[_light_module_count++] = &(module); }

uint8_t light_module_activate(light_app_context_t *app, light_module_t *mod);

light_module_t *light_module_reference_resolve(const char *ref);

#endif
