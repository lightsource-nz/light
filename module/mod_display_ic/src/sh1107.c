#include <light.h>
#include <light/module.h>
#include <light/component.h>

#include <light/mod_light_core.h>
#include <light/mod_display_ic.h>

#include <light/board.h>

#include <stddef.h>

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
        .pin_count = 2,
        .pin = {
                LIGHT_DISPLAY_IC_PIN_NAME_I2C_SCL,
                LIGHT_DISPLAY_IC_PIN_NAME_I2C_SDA
        },
        .ref_count = 0,
        .init = light_component_type_display_ic_sh1107_i2c_init,
        .create = light_component_type_display_ic_sh1107_i2c_create,
        .release = light_component_type_display_ic_sh1107_i2c_release
};

light_component_type_t component_type_display_ic_sh1107_spi = {
        .name = LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1107_SPI,
        .parent = &component_type_display_ic_sh1107,
        .is_abstract = LIGHT_COMPONENT_TYPE_IS_CONCRETE,
        .pin_count = 2,
        .pin = {
                LIGHT_DISPLAY_IC_PIN_NAME_SPI_CLK,
                LIGHT_DISPLAY_IC_PIN_NAME_SPI_MOSI
        },
        .ref_count = 0,
        .init = light_component_type_display_ic_sh1107_spi_init,
        .create = light_component_type_display_ic_sh1107_spi_create,
        .release = light_component_type_display_ic_sh1107_spi_release
};

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
        uint8_t status;
        light_component_pindef_t *pin_scl = light_component_instance_get_pin_by_name(cmp, LIGHT_DISPLAY_IC_PIN_NAME_I2C_SCL);
        light_component_pindef_t *pin_sda = light_component_instance_get_pin_by_name(cmp, LIGHT_DISPLAY_IC_PIN_NAME_I2C_SDA);
        uint8_t i2c_port = light_board_i2c_device_id_next();

        if(i2c_port == LIGHT_BOARD_I2C_PORT_NONE) {
                light_log(LIGHT_ERROR, "%s: no i2c hardware ports available");
                return LIGHT_RESOURCE_UNAVAILABLE;
        }

        if((status = light_board_i2c_device_init(i2c_port, LIGHT_BOARD_IO_BAUD_RATE_10MHZ, pin_scl->id, pin_sda->id)) != LIGHT_OK) {
                light_log(LIGHT_ERROR, "%s: i2c port with id '%d' failed to initialize", __func__, i2c_port);
                return status;
        }

        return LIGHT_OK;
}

void light_component_type_display_ic_sh1107_i2c_release(light_component_t *cmp)
{

}

uint8_t light_component_type_display_ic_sh1107_spi_init(light_component_type_t *type)
{
        
        return LIGHT_OK;
}

uint8_t light_component_type_display_ic_sh1107_spi_create(light_component_t *cmp)
{
        uint8_t status;
        light_component_pindef_t *pin_clk = light_component_instance_get_pin_by_name(cmp, LIGHT_DISPLAY_IC_PIN_NAME_SPI_CLK);
        light_component_pindef_t *pin_mosi = light_component_instance_get_pin_by_name(cmp, LIGHT_DISPLAY_IC_PIN_NAME_SPI_MOSI);
        uint8_t spi_port = light_board_spi_device_id_next();
        if(spi_port == LIGHT_BOARD_I2C_PORT_NONE) {
                light_log(LIGHT_ERROR, "%s: no spi hardware ports available");
                return LIGHT_RESOURCE_UNAVAILABLE;
        }
        
        if((status = light_board_spi_device_init(spi_port, LIGHT_BOARD_IO_BAUD_RATE_10MHZ, pin_clk->id, LIGHT_BOARD_PIN_ID_NC, pin_mosi->id)) != LIGHT_OK) {
                light_log(LIGHT_ERROR, "%s: spi port with id '%d' failed to initialize", __func__, spi_port);
                return status;
        }

        return LIGHT_OK;
}

void light_component_type_display_ic_sh1107_spi_release(light_component_t *cmp)
{

}
