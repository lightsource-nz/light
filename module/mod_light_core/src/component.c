#include <light.h>
#include <light/component.h>

#include <stddef.h>
#include <string.h>

static light_component_t *light_component_type_table[LIGHT_COMPONENT_TYPES_MAX];
static uint8_t light_component_type_count;

uint8_t light_component_init()
{
        light_component_type_count = 0;
}

uint8_t light_component_type_register(light_component_t *ct)
{
        if(light_component_type_count < LIGHT_COMPONENT_TYPES_MAX) {
                light_component_type_table[light_component_type_count++] = ct;
                return LIGHT_OK;
        }
        return LIGHT_ALLOC_LIMIT_REACHED;
}

// light_component_type_get:
// search component table for the specified component name
light_component_t *light_component_type_get(char *name)
{
        for(uint8_t i = 0; i < light_component_type_count; i++) {
                if(strcmp(light_component_type_table[i]->name, name))
                        return light_component_type_table[i];
        }
        return NULL;
}
