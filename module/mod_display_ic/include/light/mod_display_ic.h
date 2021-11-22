#ifndef __LIGHT_DISPLAY_IC_H
#define __LIGHT_DISPLAY_IC_H

#define LIGHT_MODULE_NAME_DISPLAY_IC                 "display.ic"

#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC         "display.ic"

void light_display_ic_init(light_app_context_t *app);

light_module_t *light_display_ic_module_get();

#endif