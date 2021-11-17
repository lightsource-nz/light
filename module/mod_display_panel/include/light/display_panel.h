#ifndef __LIGHT_DISPLAY_PANEL_H
#define __LIGHT_DISPLAY_PANEL_H
    
#define LIGHT_COMPONENT_TYPE_ID_DISPLAY_PANEL           2
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL         "display_panel"

void light_display_panel_init(light_app_context_t *app);

light_module_t *light_display_panel_module_get();

#endif