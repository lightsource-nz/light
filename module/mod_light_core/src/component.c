#include <light.h>
#include <light/component.h>

#include <stddef.h>
#include <string.h>

static light_component_type_t *light_component_type_table[LIGHT_COMPONENT_TYPES_MAX];
static uint8_t light_component_type_count;

static light_component_t *light_component_table[LIGHT_COMPONENTS_MAX];
static uint8_t light_component_count;

uint8_t light_component_init()
{
        light_component_type_count = 0;
}

// light_component_type_register:
// add component type to table, passing the new type to all parent types' init functions.
// init() calls are made in ascending order up the type hierarchy
uint8_t light_component_type_register(light_component_type_t *ct)
{
        if(light_component_type_count < LIGHT_COMPONENT_TYPES_MAX) {
                light_component_type_t *parent;
                light_component_type_table[light_component_type_count++] = ct;
                ct->init(ct);
                while(parent = ct->parent) {
                        parent->init(ct);
                }
                return LIGHT_OK;
        }
        return LIGHT_ALLOC_LIMIT_REACHED;
}

// light_component_type_get:
// search component type table for the specified type name
light_component_type_t *light_component_type_get(uint8_t const *name)
{
        for(uint8_t i = 0; i < light_component_type_count; i++) {
                if(strcmp(light_component_type_table[i]->name, name))
                        return light_component_type_table[i];
        }
        return NULL;
}

// light_component_instance_create:
// add component to table, passing the new instance to all parent types' create functions.
// create() calls are made in ascending order up the type hierarchy
uint8_t light_component_instance_create(light_component_t *inst)
{
        if(light_component_count < LIGHT_COMPONENTS_MAX) {
                light_component_type_t *type;
                light_component_table[light_component_count++] = inst;
                type = inst->type;

                type->create(inst);
                while(type = type->parent) {
                        type->create(inst);
                }
                return LIGHT_OK;
        }
        return LIGHT_ALLOC_LIMIT_REACHED;

}

light_component_t *light_component_instance_get(uint8_t const *name)
{
        for(uint8_t i = 0; i < light_component_count; i++) {
                if(strcmp(light_component_table[i]->name, name))
                        return light_component_table[i];
        }
        return NULL;

}
