#ifndef __LIGHT_BOARD_H
#define __LIGHT_BOARD_H


#include <stdint.h>
#include <stdbool.h>

#define LIGHT_BOARD_I2C_PORT_NONE           ((uint8_t)0xFF)
#define LIGHT_BOARD_SPI_PORT_NONE           ((uint8_t)0xFF)

#define LIGHT_BOARD_IO_BAUD_RATE_1MHZ       (1000 * 1000)
#define LIGHT_BOARD_IO_BAUD_RATE_10MHZ      (10 * 1000 * 1000)

// pass to board_x_device_init, to denote a hardware signal not muxed to a physical pin on the chip
// (e.g. for applications which use SPI but are input- or output-only)
#define LIGHT_BOARD_PIN_ID_NC               ((uint8_t)0xFF)

#define LIGHT_BOARD_PIN_FUNC_GPIO           ((uint8_t)0x0)
#define LIGHT_BOARD_PIN_FUNC_I2C            ((uint8_t)0x1)
#define LIGHT_BOARD_PIN_FUNC_SPI            ((uint8_t)0x2)
#define LIGHT_BOARD_PIN_FUNC_NC             ((uint8_t)0xFF)


#define LIGHT_BOARD_GPIO_PIN_MODE_INPUT     ((uint8_t)0x00)
#define LIGHT_BOARD_GPIO_PIN_MODE_OUTPUT    ((uint8_t)0x1)

/*------------------------------------------------------------------------------------------------------*/
void light_board_pin_set_func(uint8_t pin_id, uint8_t func);

void light_board_pin_set_input(uint8_t pin_id);
void light_board_pin_set_output(uint8_t pin_id);

void light_board_pin_set_pullup(uint8_t pin_id);
void light_board_pin_set_pulldown(uint8_t pin_id);
void light_board_pin_set_pulls(uint8_t pin_id, bool up, bool down);

void light_board_gpio_write(uint8_t pin_id, uint8_t data);
uint8_t light_board_gpio_read(uint8_t pin_id);

void light_board_sleep_ms(uint32_t xms);
void light_board_sleep_us(uint32_t xus);

uint8_t light_board_i2c_device_id_next();
uint8_t light_board_i2c_device_id_max();
uint32_t light_board_i2c_device_init(uint8_t device_id, uint32_t baudrate, uint8_t pin_scl, uint8_t pin_sda);
uint8_t light_board_i2c_device_deinit(uint8_t device_id);

uint8_t light_board_i2c_write_byte(uint8_t device_id, uint8_t addr, uint8_t reg, uint8_t data);
uint8_t light_board_i2c_write_bytes(uint8_t device_id, uint8_t addr, uint8_t *p_data, uint32_t length);
uint8_t light_board_i2c_read_byte(uint8_t device_id, uint8_t addr, uint8_t reg, uint8_t *out_data);

uint8_t light_board_spi_device_id_next();
uint8_t light_board_spi_device_id_max();
uint32_t light_board_spi_device_init(uint8_t device_id, uint32_t baudrate, uint8_t pin_clk, uint8_t pin_miso, uint8_t pin_mosi);
uint8_t light_board_spi_device_deinit(uint8_t device_id);

uint8_t light_board_spi_write_byte(uint8_t device_id, uint8_t data);
uint8_t light_board_spi_write_bytes(uint8_t device_id, uint8_t *p_data, uint32_t length);
uint8_t light_board_spi_read_byte(uint8_t device_id, uint8_t *out_data);

//void light_board_pwm_set(uint8_t Value);

uint8_t light_board_init(void);
void light_board_exit(void);

#endif
