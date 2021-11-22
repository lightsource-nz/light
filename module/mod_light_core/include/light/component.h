
#ifndef __LIGHT_COMPONENT_H
#define __LIGHT_COMPONENT_H

#ifndef __LIGHT_H
#error "light.h must be included before " __FILE__
#endif

uint8_t light_component_init();

uint8_t light_component_type_register(light_component_t *ct);

light_component_t *light_component_type_get(char *name);

#endif
