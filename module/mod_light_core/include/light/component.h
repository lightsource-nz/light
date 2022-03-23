
#ifndef __LIGHT_COMPONENT_H
#define __LIGHT_COMPONENT_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

#define LIGHT_COMPONENT_REFS_MAX                8
#define LIGHT_COMPONENT_PINS_MAX                32
#define LIGHT_COMPONENT_TREE_HEIGHT_MAX         8

typedef struct _light_component_ref_type light_component_ref_type_t;
typedef struct _light_component_type light_component_type_t;
typedef struct _light_component light_component_t;

typedef struct _light_component_ref_type {
        const uint8_t *name;
        const light_component_type_t *c_type;
} light_component_ref_type_t;

typedef struct _light_component_type {
        const uint8_t *name;
        const light_component_type_t *parent;
        const uint8_t *pin[LIGHT_COMPONENT_PINS_MAX];
        const uint8_t pin_count;
        const light_component_ref_type_t ref[LIGHT_COMPONENT_REFS_MAX];
        const uint8_t ref_count;
        const uint8_t (*init)(light_component_type_t *);
        const uint8_t (*create)(light_component_t *);
        const uint8_t (*update)(light_component_t *, uint8_t *, uint8_t *);
} light_component_type_t;

typedef struct _light_component_pindef {
        const uint8_t *name;
        uint8_t id;
} light_component_pindef_t;

typedef struct _light_component_ref {
        const uint8_t *name;
        const light_component_type_t *type;
        light_component_t *target;
} light_component_ref_t;

// not going to implement GC yet but let's count incoming refs just in case
typedef struct _light_component {
        uint8_t name[LIGHT_DESCRIPTOR_NAME_MAX_LENGTH];
        const light_component_type_t *type;
        light_component_pindef_t pin[LIGHT_COMPONENT_PINS_MAX];
        uint8_t pin_count;
        light_component_ref_t ref[LIGHT_COMPONENT_REFS_MAX];
        uint8_t ref_count;
        uint8_t refs_incoming;
        void *object;
        uint8_t (*update)(light_component_t *, uint8_t *, uint8_t *);
} light_component_t;


uint8_t light_component_init();

uint8_t light_component_type_register(light_component_type_t *ct);

light_component_type_t *light_component_type_get(uint8_t const *name);

uint8_t light_component_instance_create(light_component_t *inst);
void light_component_instance_destroy(light_component_t *inst);

light_component_t *light_component_instance_get_by_name(uint8_t const *name);
light_component_pindef_t *light_component_instance_get_pin_by_name(light_component_t *inst, const uint8_t *name);
light_component_ref_t *light_component_instance_get_ref_by_name(light_component_t *inst, const uint8_t *name);
uint8_t light_component_instance_validate_pin_mapping(light_component_t *inst);
uint8_t light_component_instance_validate_references(light_component_t *inst);
uint8_t light_component_instance_reference_set(light_component_t *cmp, uint8_t *ref, uint8_t *value);

// returns true if the given component type name matches _cmp->type_ or any of its ancestors
uint8_t light_component_instance_is_of_type(light_component_t *cmp, const uint8_t *type);

#endif
