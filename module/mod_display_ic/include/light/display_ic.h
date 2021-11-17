#ifndef __LIGHT_DISPLAY_IC_H
#define __LIGHT_DISPLAY_IC_H
    
#define LIGHT_COMPONENT_TYPE_ID_DISPLAY_IC           1
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC         "display_ic"

void light_display_ic_init(light_app_context_t *app);

light_module_t *light_display_ic_module_get();

#endif