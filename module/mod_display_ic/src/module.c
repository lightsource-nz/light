#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light/mod_light_core.h>
#include <light/mod_display_ic.h>

#include <light/board.h>

#include <stddef.h>

static light_module_t this_module = {
        .name = LIGHT_MODULE_NAME_DISPLAY_IC,
        .type = LIGHT_MODULE_BASE,
        .init = &light_display_ic_module_init,
        .depends_on = { LIGHT_MODULE_NAME_LIGHT_CORE }
};

light_component_type_t component_type_display_ic = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_ABSTRACT,
        .pin_count = 3,
        .pin = {
                LIGHT_DISPLAY_IC_PIN_NAME_RESET,
                LIGHT_DISPLAY_IC_PIN_NAME_CS,
                LIGHT_DISPLAY_IC_PIN_NAME_DC
        },
        .ref_count = 0,
        .init = light_component_type_display_ic_init,
        .create = light_component_type_display_ic_create,
        .release = light_component_type_display_ic_release
};

LIGHT_MODULE_IMPLEMENT(this_module);

void light_display_ic_module_init(light_app_context_t *app)
{
        light_component_type_register(&component_type_display_ic);
        light_component_type_register(&component_type_display_ic_sh1107);
        light_component_type_register(&component_type_display_ic_sh1107_i2c);
        light_component_type_register(&component_type_display_ic_sh1107_spi);
}

light_module_t *light_display_ic_module_get()
{
        return &this_module;
}

uint8_t light_component_type_display_ic_init(light_component_type_t *type)
{
        return LIGHT_OK;
}

uint8_t light_component_type_display_ic_create(light_component_t *cmp)
{
        return LIGHT_OK;
}

void light_component_type_display_ic_release(light_component_t *cmp)
{
        
}
