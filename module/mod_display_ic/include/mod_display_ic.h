#ifndef __LIGHT_DISPLAY_IC_SH1107_H
#define __LIGHT_DISPLAY_IC_SH1107_H

#define LIGHT_MODULE_NAME_DISPLAY_IC                        "display.ic"

#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC                "display.ic"
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1106         "display.ic.sh1106"
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1106_I2C     "display.ic.sh1106.i2c"
#define LIGHT_COMPONENT_TYPE_NAME_DISPLAY_IC_SH1106_SPI     "display.ic.sh1106.spi"

// i2c and spi interfaces share clock and data pin names
#define LIGHT_DISPLAY_IC_PIN_NAME_I2C_SCL                               "pin:I2C_SCL"
#define LIGHT_DISPLAY_IC_PIN_NAME_I2C_SDA                               "pin:I2C_SDA"
#define LIGHT_DISPLAY_IC_PIN_NAME_SPI_CLK                               "pin:SPI_CLK"
#define LIGHT_DISPLAY_IC_PIN_NAME_SPI_MOSI                              "pin:SPI_SDA"
#define LIGHT_DISPLAY_IC_PIN_NAME_RESET                                 "pin:RESET"
#define LIGHT_DISPLAY_IC_PIN_NAME_DC                                    "pin:DC"
#define LIGHT_DISPLAY_IC_PIN_NAME_CS                                    "pin:CS"

extern light_component_type_t component_type_display_ic;
extern light_component_type_t component_type_display_ic_sh1106;
extern light_component_type_t component_type_display_ic_sh1106_i2c;
extern light_component_type_t component_type_display_ic_sh1106_spi;

void light_display_ic_module_init(light_app_context_t *app);

light_module_t *light_display_ic_module_get();

uint8_t light_component_type_display_ic_init(light_component_type_t *type);
uint8_t light_component_type_display_ic_create(light_component_t *cmp);

uint8_t light_component_type_display_ic_sh1106_init(light_component_type_t *type);
uint8_t light_component_type_display_ic_sh1106_create(light_component_t *cmp);

uint8_t light_component_type_display_ic_sh1106_i2c_init(light_component_type_t *type);
uint8_t light_component_type_display_ic_sh1106_i2c_create(light_component_t *cmp);
uint8_t light_component_type_display_ic_sh1106_spi_init(light_component_type_t *type);
uint8_t light_component_type_display_ic_sh1106_spi_create(light_component_t *cmp);

#endif