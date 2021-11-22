
#ifndef __LIGHT_COMPONENT_H
#define __LIGHT_COMPONENT_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

typedef struct _light_component light_component_type_t;

typedef struct _light_component {
    uint8_t const *name;
    uint8_t (*init)(light_app_context_t *, light_component_type_t *);
} light_component_type_t;

uint8_t light_component_init();

uint8_t light_component_type_register(light_component_type_t *ct);

light_component_type_t *light_component_type_get(char *name);

#endif
