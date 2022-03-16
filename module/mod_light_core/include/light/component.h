
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
        const uint8_t pin[LIGHT_COMPONENT_PINS_MAX][LIGHT_DESCRIPTOR_NAME_MAX_LENGTH];
        const uint8_t pin_count;
        uint8_t (*init)(light_component_type_t *);
        uint8_t (*create)(light_component_t *);
} light_component_type_t;

typedef struct _light_component_pindef {
        uint8_t name[LIGHT_DESCRIPTOR_NAME_MAX_LENGTH];
        uint8_t pin;
} light_component_pindef_t;

typedef struct _light_component {
        uint8_t name[LIGHT_DESCRIPTOR_NAME_MAX_LENGTH];
        light_component_type_t *type;
        light_component_pindef_t pin[LIGHT_COMPONENT_PINS_MAX];
        const uint8_t pin_count;
        void *object;
} light_component_t;


uint8_t light_component_init();

uint8_t light_component_type_register(light_component_type_t *ct);

light_component_type_t *light_component_type_get(uint8_t const *name);

uint8_t light_component_instance_create(light_component_t *inst);
void light_component_instance_destroy(light_component_t *inst);

light_component_t *light_component_instance_get(uint8_t const *name);
light_component_pindef_t *light_component_instance_get_pin_by_name(light_component_t *inst, const uint8_t *name);
uint8_t light_component_instance_validate_pin_mapping(light_component_t *inst);

// looks up _type_ by name in the type table, and compares the result to _cmp_
uint8_t light_component_instance_is_of_type(light_component_t *cmp, const uint8_t *type);

#endif
