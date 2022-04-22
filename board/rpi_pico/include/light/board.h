#ifndef __LIGHT_BOARD_H
#define __LIGHT_BOARD_H


#include <stdint.h>
/**
 * GPIOI config
**/
extern int EPD_RST_PIN;
extern int EPD_DC_PIN;
extern int EPD_CS_PIN;
extern int EPD_BL_PIN;
extern int EPD_CLK_PIN;
extern int EPD_MOSI_PIN;
extern int EPD_SCL_PIN;
extern int EPD_SDA_PIN;

#define LIGHT_BOARD_I2C_PORT_NONE       (uint8_t)(0 - 1)
#define LIGHT_BOARD_SPI_PORT_NONE       (uint8_t)(0 - 1)

/*------------------------------------------------------------------------------------------------------*/
void board_gpio_write(uint16_t Pin, uint8_t Value);
uint8_t board_gpio_read(uint16_t Pin);

void board_gpio_mode(uint16_t Pin, uint16_t Mode);
void board_gpio_set_key(uint16_t Pin);

void board_spi_write_byte(uint8_t  Value);
void board_spi_write_bytes(uint8_t *pData, uint32_t Len);

void board_set_spi_device_pins(uint8_t mosi, uint8_t clk);
void board_set_i2c_device_pins(uint8_t sda, uint8_t scl);

void board_set_pin_input(uint8_t pin);
void board_set_pin_output(uint8_t pin);

void board_sleep_ms(uint32_t xms);
void board_sleep_us(uint32_t xus);

uint8_t board_i2c_device_id_next();
uint8_t board_i2c_device_id_max();
uint8_t board_i2c_device_init(uint8_t device_id, uint8_t pin_scl, uint8_t pin_sda);
uint8_t board_i2c_device_deinit(uint8_t device_id);

void board_i2c_write_byte(uint8_t device_id, uint8_t addr, uint8_t reg, uint8_t Value);
void board_i2c_write_bytes(uint8_t device_id, uint8_t addr, uint8_t *pData, uint32_t Len);
uint8_t board_i2c_read_byte(uint8_t device_id, uint8_t addr, uint8_t reg);

void board_pwm_set(uint8_t Value);

uint8_t  light_board_init(void);
void light_board_exit(void);

#endif
