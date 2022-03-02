
#ifndef __LIGHT_COMPONENT_H
#define __LIGHT_COMPONENT_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

typedef struct _light_component_type light_component_type_t;
typedef struct _light_component light_component_t;

typedef struct _light_component_type {
    uint8_t const *name;
    light_component_type_t *parent;
    uint8_t (*init)(light_component_type_t *);
    uint8_t (*create)(light_component_t *);
} light_component_type_t;



typedef struct _light_component {
    uint8_t const *name;
    light_component_type_t *type;
} light_component_t;


uint8_t light_component_init();

uint8_t light_component_type_register(light_component_type_t *ct);

light_component_type_t *light_component_type_get(uint8_t const *name);

uint8_t light_component_instance_create(light_component_t *inst);
light_component_t *light_component_instance_get(uint8_t const *name);

#endif
