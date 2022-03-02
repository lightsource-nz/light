#ifndef __LIGHT_DISPLAY_PANEL_H
#define __LIGHT_DISPLAY_PANEL_H

#define LIGHT_MODULE_NAME_DISPLAY_PANEL                     "display.panel"
    
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL             "display.panel"
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN   "display.panel.oled1p3in"

void light_display_panel_init(light_app_context_t *app);

light_module_t *light_display_panel_module_get();

light_component_type_t *light_display_panel_component_type_get();
light_component_type_t *light_display_panel_oled1p3in_component_type_get();

#endif