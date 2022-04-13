#ifndef __LIGHT_DISPLAY_GUI_H
#define __LIGHT_DISPLAY_GUI_H


#define LIGHT_MODULE_NAME_DISPLAY_GUI                 "display.gui"

#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_GUI         "display.gui"
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_GUI_64X128  "display.gui.64x128"

void light_display_gui_module_init(light_app_context_t *app);

light_module_t *light_display_gui_module_get();

extern light_component_type_t component_type_display_gui;
extern light_component_type_t component_type_display_gui_64x128;

uint8_t light_component_type_display_gui_init(light_component_type_t *type);

uint8_t light_component_type_display_gui_create(light_component_t *cmp);

uint8_t light_component_type_display_gui_64x128_init(light_component_type_t *type);

uint8_t light_component_type_display_gui_64x128_create(light_component_t *cmp);

uint8_t light_component_action_display_gui_set_context(light_component_t *cmp);

#endif