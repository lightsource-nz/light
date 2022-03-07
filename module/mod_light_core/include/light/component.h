
#ifndef __LIGHT_COMPONENT_H
#define __LIGHT_COMPONENT_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

#define LIGHT_COMPONENT_PINS_MAX                32
#define LIGHT_COMPONENT_TREE_HEIGHT_MAX         8

typedef struct _light_component_type light_component_type_t;
typedef struct _light_component light_component_t;

typedef struct _light_component_type {
        const uint8_t *name;
        const light_component_type_t *parent;
        const uint8_t *pin[LIGHT_COMPONENT_PINS_MAX];
        uint8_t (*init)(light_component_type_t *);
        uint8_t (*create)(light_component_t *);
} light_component_type_t;

typedef struct _light_component_pindef {
        const uint8_t *name;
        uint8_t pin;
} light_component_pindef_t;

typedef struct _light_component {
        uint8_t *name;
        light_component_type_t *type;
        light_component_pindef_t pin[LIGHT_COMPONENT_PINS_MAX];
        void *object;
} light_component_t;


uint8_t light_component_init();

uint8_t light_component_type_register(light_component_type_t *ct);

light_component_type_t *light_component_type_get(uint8_t const *name);

uint8_t light_component_instance_create(light_component_t *inst);
void light_component_instance_destroy(light_component_t *inst);
light_component_t *light_component_instance_get(uint8_t const *name);

#endif
