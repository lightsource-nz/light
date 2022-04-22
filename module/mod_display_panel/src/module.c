#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light/mod_light_core.h>
#include <light/mod_display_ic.h>
#include <light/mod_display_gui.h>
#include <light/mod_display_panel.h>

#include <light/display_panel.h>

#include <stddef.h>

light_component_type_t component_type_display_panel = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL,
        .parent = NULL,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_ABSTRACT,
        .pin_count = 0,
        .ref_count = 2,
        .ref = {
                {
                        .name = LIGHT_COMPONENT_REF_NAME_DISPLAY_PANEL_DRIVER_IC,
                        .c_type = &component_type_display_ic
                },
                {
                        .name = LIGHT_COMPONENT_REF_NAME_DISPLAY_PANEL_TARGET_GUI,
                        .c_type = &component_type_display_gui
                }
        },
        .init = light_component_type_display_panel_init,
        .create = light_component_type_display_panel_create,
        .update = light_component_type_display_panel_update,
        .release = light_component_type_display_panel_release
};

light_component_type_t component_type_display_panel_oled1p3in = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN,
        .parent = &component_type_display_panel,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
        .pin_count = 0,
        .ref_count = 0,
        .init = light_component_type_display_panel_oled1p3in_init,
        .create = light_component_type_display_panel_oled1p3in_create,
        .update = light_component_type_display_panel_oled1p3in_update,
        .release = light_component_type_display_panel_oled1p3in_release
};
/*
light_component_type_t component_type_display_panel_oled1p3in_i2c = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN_I2C,
        .parent = &component_type_display_panel_oled1p3in,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
        .pin_count = 2,
        .pin = {
                LIGHT_PANEL_PIN_NAME_SCL,
                LIGHT_PANEL_PIN_NAME_SDA
        },
        .init = light_component_type_display_panel_oled1p3in_i2c_init,
        .create = light_component_type_display_panel_oled1p3in_i2c_create,
        .update = light_component_type_display_panel_oled1p3in_i2c_update,
        .release = light_component_type_display_panel_oled1p3in_i2c_release
};

light_component_type_t component_type_display_panel_oled1p3in_spi = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_PANEL_OLED1P3IN_SPI,
        .parent = &component_type_display_panel_oled1p3in,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
        .pin_count = 5,
        .pin = {
                LIGHT_PANEL_PIN_NAME_SCL,
                LIGHT_PANEL_PIN_NAME_SDA,
                LIGHT_PANEL_PIN_NAME_RESET,
                LIGHT_PANEL_PIN_NAME_DC,
                LIGHT_PANEL_PIN_NAME_CS
        },
        .init = light_component_type_display_panel_oled1p3in_spi_init,
        .create = light_component_type_display_panel_oled1p3in_spi_create,
        .update = light_component_type_display_panel_oled1p3in_spi_update,
        .release = light_component_type_display_panel_oled1p3in_spi_release
};
*/


static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_PANEL,
        .type = LIGHT_MODULE_BASE,
        .deps_count = 2,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE,
                        LIGHT_MODULE_NAME_DISPLAY_IC },
        .decl_count = 0,
        .init = &light_display_panel_module_init,
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_panel_module_init(light_app_context_t *app)
{
        light_component_type_register(&component_type_display_panel);
        light_component_type_register(&component_type_display_panel_oled1p3in);
        //light_component_type_register(&component_type_display_panel_oled1p3in_i2c);
        //light_component_type_register(&component_type_display_panel_oled1p3in_spi);
}

light_module_t *light_display_panel_module_get()
{
        return &this_module;
}
