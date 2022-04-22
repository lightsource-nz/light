#ifndef __LIGHT_DISPLAY_PANEL_H
#define __LIGHT_DISPLAY_PANEL_H

#define LIGHT_MODULE_NAME_DISPLAY_PANEL                         "display.panel"
    
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL                 "display.panel:type:base"
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN       "display.panel:type:oled1p3in"
//#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN_I2C   "display.panel:type:oled1p3in.i2c"
//#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN_SPI   "display.panel:type:oled1p3in.spi"

#define LIGHT_COMPONENT_DISPLAY_PANEL_OLED1P3IN_X_PIXELS        128
#define LIGHT_COMPONENT_DISPLAY_PANEL_OLED1P3IN_Y_PIXELS        64

#define LIGHT_COMPONENT_REF_NAME_DISPLAY_PANEL_DRIVER_IC        "display.panel:ref:driver"
#define LIGHT_COMPONENT_REF_NAME_DISPLAY_PANEL_TARGET_GUI       "display.panel:ref:gui"

void light_display_panel_module_init(light_app_context_t *app);

light_module_t *light_display_panel_module_get();

extern light_component_type_t component_type_display_panel;
extern light_component_type_t component_type_display_panel_oled1p3in;
//extern light_component_type_t component_type_display_panel_oled1p3in_i2c;
//extern light_component_type_t component_type_display_panel_oled1p3in_spi;

#endif
