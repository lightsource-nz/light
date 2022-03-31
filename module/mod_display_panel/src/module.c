#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light_core.h>
#include <mod_display_ic.h>
#include <mod_display_panel.h>

#include <component/panel.h>

#include <stddef.h>

light_component_type_t component_type_display_panel = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL,
        .parent = NULL,
        .pin_count = 0,
        .ref_count = 1,
        .ref = {
                {
                        .name = LIGHT_COMPONENT_REF_NAME_DISPLAY_PANEL_DRIVER_IC,
                        
                }
        },
        .init = light_component_type_display_panel_init,
        .create = light_component_type_display_panel_create
};

light_component_type_t component_type_display_panel_oled1p3in = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN,
        .parent = &component_type_display_panel,
        .pin_count = 0,
        .init = light_component_type_display_panel_oled1p3in_init,
        .create = light_component_type_display_panel_oled1p3in_create
};

light_component_type_t component_type_display_panel_oled1p3in_i2c = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN_I2C,
        .parent = &component_type_display_panel_oled1p3in,
        .pin_count = 2,
        .pin = {
                LIGHT_PANEL_PIN_NAME_SCL,
                LIGHT_PANEL_PIN_NAME_SDA
        },
        .init = light_component_type_display_panel_oled1p3in_i2c_init,
        .create = light_component_type_display_panel_oled1p3in_i2c_create
};

light_component_type_t component_type_display_panel_oled1p3in_spi = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN_SPI,
        .parent = &component_type_display_panel_oled1p3in,
        .pin_count = 5,
        .pin = {
                LIGHT_PANEL_PIN_NAME_SCL,
                LIGHT_PANEL_PIN_NAME_SDA,
                LIGHT_PANEL_PIN_NAME_RESET,
                LIGHT_PANEL_PIN_NAME_DC,
                LIGHT_PANEL_PIN_NAME_CS
        },
        .init = light_component_type_display_panel_oled1p3in_i2c_init,
        .create = light_component_type_display_panel_oled1p3in_i2c_create
};


static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_PANEL,
        .type = LIGHT_MODULE_BASE,
        .init = &light_display_panel_module_init,
        .deps_count = 2,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE,
                        LIGHT_MODULE_NAME_DISPLAY_IC },
        .decl_count = 0
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_panel_module_init(light_app_context_t *app)
{
        light_component_type_register(&component_type_display_panel);
        light_component_type_register(&component_type_display_panel_oled1p3in);
        light_component_type_register(&component_type_display_panel_oled1p3in_i2c);
        light_component_type_register(&component_type_display_panel_oled1p3in_spi);
}

light_module_t *light_display_panel_module_get()
{
        return &this_module;
}
