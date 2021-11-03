#ifndef _LIGHT_DISPLAY_BOARD_H_
#define _LIGHT_DISPLAY_BOARD_H_

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

/*------------------------------------------------------------------------------------------------------*/
void board_gpio_write(uint16_t Pin, uint8_t Value);
uint8_t board_gpio_read(uint16_t Pin);

void board_gpio_mode(uint16_t Pin, uint16_t Mode);
void board_gpio_set_key(uint16_t Pin);

void board_spi_write_byte(uint8_t  Value);
void board_spi_write_bytes(uint8_t *pData, uint32_t Len);

void board_sleep_ms(uint32_t xms);
void board_sleep_us(uint32_t xus);


void board_i2c_write_byte(uint8_t addr, uint8_t reg, uint8_t Value);
void board_i2c_write_bytes(uint8_t addr, uint8_t *pData, uint32_t Len);
uint8_t board_i2c_read_byte(uint8_t addr, uint8_t reg);

void board_pwm_set(uint8_t Value);

uint8_t  light_display_board_init(void);
void light_display_board_exit(void);


#endif
