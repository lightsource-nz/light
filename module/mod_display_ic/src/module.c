#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light/mod_light_core.h>
#include <light/mod_display_ic.h>

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
        .pin_count = 0,
        .ref_count = 0,
        .init = light_component_type_display_ic_init,
        .create = light_component_type_display_ic_create
};

light_component_type_t component_type_display_ic_sh1107 = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1107,
        .parent = &component_type_display_ic,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_ABSTRACT,
        .pin_count = 0,
        .ref_count = 0,
        .init = light_component_type_display_ic_sh1107_init,
        .create = light_component_type_display_ic_sh1107_create
};

light_component_type_t component_type_display_ic_sh1107_i2c = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1107_I2C,
        .parent = &component_type_display_ic_sh1107,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
        .pin_count = 0,
        .ref_count = 0,
        .init = light_component_type_display_ic_sh1107_i2c_init,
        .create = light_component_type_display_ic_sh1107_i2c_create
};

light_component_type_t component_type_display_ic_sh1107_spi = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1107_SPI,
        .parent = &component_type_display_ic_sh1107,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
        .pin_count = 0,
        .ref_count = 0,
        .init = light_component_type_display_ic_sh1107_spi_init,
        .create = light_component_type_display_ic_sh1107_spi_create
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

uint8_t light_component_type_display_ic_sh1107_init(light_component_type_t *type)
{
        return LIGHT_OK;
        
}

uint8_t light_component_type_display_ic_sh1107_create(light_component_t *cmp)
{
        return LIGHT_OK;
}

uint8_t light_component_type_display_ic_sh1107_i2c_init(light_component_type_t *type)
{
        return LIGHT_OK;

}

uint8_t light_component_type_display_ic_sh1107_i2c_create(light_component_t *cmp)
{

        return LIGHT_OK;
}

uint8_t light_component_type_display_ic_sh1107_spi_init(light_component_type_t *type)
{
        
        return LIGHT_OK;
}

uint8_t light_component_type_display_ic_sh1107_spi_create(light_component_t *cmp)
{
        
        return LIGHT_OK;
}
