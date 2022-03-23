#include <light.h>
#include <light/component.h>

#include <stddef.h>
#include <string.h>
#include <stdbool.h>

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
uint8_t light_component_type_register(light_component_type_t *type)
{
        if(light_component_type_count < LIGHT_COMPONENT_TYPES_MAX) {
                const light_component_type_t *parents[LIGHT_COMPONENT_TREE_HEIGHT_MAX];
                uint8_t height;

                light_component_type_table[light_component_type_count++] = type;
                const light_component_type_t *next = type;
                for(height= 0; height < LIGHT_COMPONENT_TREE_HEIGHT_MAX; height++) {
                        parents[height] = next;
                }

                while(height >= 0) {
                        parents[height]->init(type);
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

uint8_t light_component_instance_validate_pin_mapping(light_component_t *inst);
// light_component_instance_create:
// add component to table, passing the new instance to all parent types' create functions.
// create() calls are made in descending order from the root of the type hierarchy
uint8_t light_component_instance_create(light_component_t *inst)
{
        if(light_component_count >= LIGHT_COMPONENTS_MAX)
                return LIGHT_ALLOC_LIMIT_REACHED;

        

        const light_component_type_t *type[LIGHT_COMPONENT_TREE_HEIGHT_MAX];
        const light_component_type_t *next = inst->type;
        uint8_t height;
        uint8_t status;

        light_component_table[light_component_count++] = inst;

        if((status = light_component_instance_validate_pin_mapping(inst)) != LIGHT_OK) {
                light_log(LIGHT_ERROR, "failed to validate pin mapping for component '%s'", inst->name);
                return status;
        }

        
        if((status = light_component_instance_validate_references(inst)) != LIGHT_OK) {
                light_log(LIGHT_ERROR, "failed to validate pin mapping for component '%s'", inst->name);
                return status;
        }
        
        for(height = 0; height < LIGHT_COMPONENT_TREE_HEIGHT_MAX; height++) {
                type[height] = next;
                next = next->parent;
        }

        while (height >= 0) {
                type[height]->create(inst);
                height--;
        }

        return LIGHT_OK;

}

light_component_pindef_t *light_component_instance_get_pin_by_name(light_component_t *inst, const uint8_t *name)
{
        for(uint8_t i = 0; i < inst->type->pin_count; i++) {
                if(strcmp(inst->pin[i].name, name)) {
                        return &inst->pin[i];
                }
        }

        return NULL;
}

light_component_ref_t *light_component_instance_get_ref_by_name(light_component_t *inst, const uint8_t *name)
{
        for(uint8_t i = 0; i < inst->type->ref_count; i++) {
                if(strcmp(inst->ref[i].name, name)) {
                        return &inst->ref[i];
                }
        }

        return NULL;
}

uint8_t light_component_instance_validate_pin_mapping(light_component_t *inst)
{
        
        const light_component_type_t *next_type = inst->type;
        do {
                for(uint8_t j = 0; j < next_type->pin_count; j++) {
                        light_component_pindef_t *dest_pin = light_component_instance_get_pin_by_name(inst, next_type->pin[j]);
                        if(!strcmp(dest_pin->name, next_type->pin[j])) {
                                return LIGHT_INVALID_ARG;
                        }
                }
                
        } while(next_type = next_type->parent);

        light_log(LIGHT_INFO, "validated pin mapping for component '%s'", inst->name);

        return LIGHT_OK;
}

uint8_t light_component_instance_validate_references(light_component_t *inst)
{
        
        const light_component_type_t *next_type = inst->type;
        do {
                for(uint8_t j = 0; j < next_type->ref_count; j++) {
                        light_component_ref_t *ref = light_component_instance_get_ref_by_name(inst, next_type->ref[j].name);
                        if(!strcmp(ref->name, next_type->ref[j].name)) {
                                return LIGHT_INVALID_ARG;
                        }
                }
                
        } while(next_type = next_type->parent);

        light_log(LIGHT_INFO, "validated component references for component '%s'", inst->name);

        return LIGHT_OK;
}

uint8_t light_component_instance_reference_set(light_component_t *cmp, uint8_t *ref_id, uint8_t *value)
{
        light_component_t *target;
        if((target = light_component_instance_get_by_name(value)) != NULL) {
                light_log(LIGHT_WARN, "%s: component not found by name '%s'", __func__, value);
                return LIGHT_INVALID_ARG;
        }

        light_component_ref_t *ref;
        if((ref = light_component_instance_get_ref_by_name(cmp, ref_id)) != NULL) {
                light_log(LIGHT_WARN, "%s: component reference not found by name '%s::%s'", __func__, cmp, ref_id);
                return LIGHT_INVALID_ARG;
        }
        // if the reference already has a target, decrement that target's ref-count
        if(ref->target != NULL) {
                if(ref->target->refs_incoming > 0) {    // this should always be true, actually
                        ref->target->refs_incoming--;
                }
                ref->target = NULL;
        }

        if(!light_component_instance_is_of_type(target, ref->type)) {
                light_log(LIGHT_WARN, "%s: target component '%s' is of type '%s', which does not match reference type '%s'", __func__, target, target->type, ref->type);
                return LIGHT_INVALID_ARG;
        }

        target->refs_incoming++;

        ref->type->update(cmp, ref_id, value);

        return LIGHT_OK;
}

light_component_t *light_component_instance_get_by_name(uint8_t const *name)
{
        for(uint8_t i = 0; i < light_component_count; i++) {
                if(strcmp(light_component_table[i]->name, name))
                        return light_component_table[i];
        }
        return NULL;

}

uint8_t light_component_instance_is_of_type(light_component_t *cmp, const uint8_t *type_name)
{
        light_component_type_t const *type = light_component_type_get(type_name);
        do{
                if(type == cmp->type)
                        return true;
        } while (type = type->parent);
        return false;
}
