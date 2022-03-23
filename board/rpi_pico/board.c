/*****************************************************************************
* | File      	:   DEV_Config.c
* | Author      :   
* | Function    :   Hardware underlying interface
* | Info        :
*----------------
* |	This version:   V1.0
* | Date        :   2021-03-16
* | Info        :   
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of theex Software, and to permit persons to  whom the Software is
# furished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
******************************************************************************/
#include <light.h>
#include <light_board.h>

#include <hardware/spi.h>
#include <hardware/i2c.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>

#include <stdio.h>
#include <pico/stdio.h>

#define SPI_PORT spi1
#define I2C_PORT i2c1

/**
 * GPIO
**/
int EPD_RST_PIN;
int EPD_DC_PIN;
int EPD_CS_PIN;
int EPD_BL_PIN;
int EPD_CLK_PIN;
int EPD_MOSI_PIN;
int EPD_SCL_PIN;
int EPD_SDA_PIN;


uint slice_num;
/**
 * GPIO read and write
**/
void board_gpio_write(uint16_t Pin, uint8_t Value)
{
    gpio_put(Pin, Value);
}

uint8_t board_gpio_read(uint16_t Pin)
{
    return gpio_get(Pin);
}

/**
 * SPI
**/
void board_spi_write_byte(uint8_t Value)
{
    spi_write_blocking(SPI_PORT, &Value, 1);
}

void board_spi_write_bytes(uint8_t pData[], uint32_t Len)
{
    spi_write_blocking(SPI_PORT, pData, Len);
}



/**
 * I2C
**/

void board_i2c_write_byte(uint8_t device_id, uint8_t addr, uint8_t reg, uint8_t Value)
{
    uint8_t data[2] = {reg, Value};
    i2c_write_blocking(I2C_PORT, addr, data, 2, false);
}

void board_i2c_write_bytes(uint8_t device_id, uint8_t addr, uint8_t *pData, uint32_t Len)
{
    i2c_write_blocking(I2C_PORT, addr, pData, Len, false);
}

uint8_t board_i2c_read_byte(uint8_t device_id, uint8_t addr, uint8_t reg)
{
    uint8_t buf;
    i2c_write_blocking(I2C_PORT,addr,&reg,1,true);
    i2c_read_blocking(I2C_PORT,addr,&buf,1,false);
    return buf;
}

/**
 * GPIO Mode
**/
void board_gpio_mode(uint16_t Pin, uint16_t Mode)
{
    gpio_init(Pin);
    if(Mode == 0 || Mode == GPIO_IN) {
        gpio_set_dir(Pin, GPIO_IN);
    } else {
        gpio_set_dir(Pin, GPIO_OUT);
    }
}

/**
 * KEY Config
**/
void board_gpio_set_key(uint16_t Pin)
{
    gpio_init(Pin);
	gpio_pull_up(Pin);
    gpio_set_dir(Pin, GPIO_IN);
}

/**
 * delay x ms
**/
void board_sleep_ms(uint32_t xms)
{
    sleep_ms(xms);
}

void board_sleep_us(uint32_t xus)
{
    sleep_us(xus);
}



void board_gpio_init(void)
{
    board_gpio_mode(EPD_RST_PIN, 1);
    board_gpio_mode(EPD_DC_PIN, 1);
    board_gpio_mode(EPD_CS_PIN, 1);
    board_gpio_mode(EPD_BL_PIN, 1);
    
    
    board_gpio_mode(EPD_CS_PIN, 1);
    board_gpio_mode(EPD_BL_PIN, 1);

    board_gpio_mode(EPD_CS_PIN, 1);
    board_gpio_mode(EPD_DC_PIN, 0);
    board_gpio_mode(EPD_BL_PIN, 1);
}

uint8_t light_board_init(void)
{
    stdio_init_all();
    
    //GPIO PIN
    EPD_RST_PIN     = 12;
    EPD_DC_PIN      = 8;
    EPD_BL_PIN    = 13;
    
    EPD_CS_PIN      = 9;
    EPD_CLK_PIN     = 10;
    EPD_MOSI_PIN    = 11;
    
    EPD_SCL_PIN    = 7;
    EPD_SDA_PIN    = 6;
    
    // SPI Config
    spi_init(SPI_PORT, 10000 * 1000);
    gpio_set_function(EPD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(EPD_MOSI_PIN, GPIO_FUNC_SPI);
    
    // GPIO Config
    board_gpio_init();
    
    // PWM Config
    gpio_set_function(EPD_BL_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(EPD_BL_PIN);
    pwm_set_wrap(slice_num, 100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
    pwm_set_clkdiv(slice_num,50);
    pwm_set_enabled(slice_num, true);
    
    
    //I2C Config
    i2c_init(i2c1,300*1000);
    gpio_set_function(EPD_SDA_PIN,GPIO_FUNC_I2C);
    gpio_set_function(EPD_SCL_PIN,GPIO_FUNC_I2C);
    gpio_pull_up(EPD_SDA_PIN);
    gpio_pull_up(EPD_SCL_PIN);
    
    printf("light_display_board_init() OK \r\n");
    return LIGHT_OK;
}

void board_set_pwm(uint8_t Value){
    if(Value<0 || Value >100){
        printf("board_set_pwm Error \r\n");
    }else {
        pwm_set_chan_level(slice_num, PWM_CHAN_B, Value);
    }
        
    
    
}

void light_display_board_exit(void)
{

}

void _light_board_log_handler(const char *msg)
{
    printf("[light]: %s", msg);
}
