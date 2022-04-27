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
#include <light/board.h>

#include <hardware/spi.h>
#include <hardware/i2c.h>
#include <hardware/gpio.h>
#include <hardware/pwm.h>

#include <stdio.h>
#include <pico/stdio.h>

#define LIGHT_BOARD_I2C_PORT_MAX        2
#define LIGHT_BOARD_SPI_PORT_MAX        2

static uint8_t i2c_port_next = 0;
static uint8_t spi_port_next = 0;

//
// internal functions to map between Light Framework hardware ids and internal device handles
//
uint8_t _light_board_device_id_to_handle_spi(uint8_t id, spi_inst_t **out_handle);
uint8_t _light_board_device_id_to_handle_i2c(uint8_t id, i2c_inst_t **out_handle);

void light_board_pin_set_func(uint8_t pin_id, uint8_t func)
{
        switch (func)
        {
        case LIGHT_BOARD_PIN_FUNC_GPIO:
                gpio_set_function(pin_id, GPIO_FUNC_SIO);
                break;
        case LIGHT_BOARD_PIN_FUNC_I2C:


        default:
                break;
        }
}

void light_board_pin_set_input(uint8_t pin_id)
{
        gpio_init(pin_id);
        gpio_set_dir(pin_id, GPIO_IN);
}
void light_board_pin_set_output(uint8_t pin_id)
{
        gpio_init(pin_id);
        gpio_set_dir(pin_id, GPIO_IN);
}

void light_board_pin_set_pullup(uint8_t pin_id)
{
        gpio_pull_up(pin_id);
}
void light_board_pin_set_pulldown(uint8_t pin_id)
{
        gpio_pull_down(pin_id);
}
void light_board_pin_set_pulls(uint8_t pin_id, bool up, bool down)
{
        gpio_set_pulls(pin_id, up, down);
}

void light_board_gpio_write(uint8_t pin_id, uint8_t data)
{
        gpio_put(pin_id, data);
}
uint8_t light_board_gpio_read(uint8_t pin_id)
{
        return gpio_get(pin_id);
}

uint8_t light_board_i2c_device_id_next()
{
        if(i2c_port_next < LIGHT_BOARD_I2C_PORT_MAX) {
                return i2c_port_next++;
        } else {
                return LIGHT_BOARD_I2C_PORT_NONE;
        }
}

uint8_t light_board_i2c_device_id_max()
{
        return LIGHT_BOARD_I2C_PORT_MAX;
}

uint32_t light_board_i2c_device_init(uint8_t device_id, uint32_t baudrate, uint8_t pin_scl, uint8_t pin_sda)
{
        i2c_inst_t *handle;
        if(!_light_board_device_id_to_handle_i2c(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;

        if(pin_scl != LIGHT_BOARD_PIN_ID_NC)
                gpio_set_function(pin_scl, GPIO_FUNC_I2C);
        if(pin_sda != LIGHT_BOARD_PIN_ID_NC)
                gpio_set_function(pin_sda, GPIO_FUNC_I2C);

        return i2c_init(handle, baudrate);
}

uint8_t light_board_i2c_device_deinit(uint8_t device_id)
{
        i2c_inst_t *handle;
        if(!_light_board_device_id_to_handle_i2c(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;

        i2c_deinit(handle);
        return LIGHT_OK;
    
}

uint8_t light_board_i2c_write_byte(uint8_t device_id, uint8_t addr, uint8_t reg, uint8_t Value)
{
        i2c_inst_t *handle;
        if(!_light_board_device_id_to_handle_i2c(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;

        uint8_t data[2] = {reg, Value};
        i2c_write_blocking(handle, addr, data, 2, false);
        return LIGHT_OK;
}

uint8_t light_board_i2c_write_bytes(uint8_t device_id, uint8_t addr, uint8_t *pData, uint32_t Len)
{
        i2c_inst_t *handle;
        if(!_light_board_device_id_to_handle_i2c(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;
        
        i2c_write_blocking(handle, addr, pData, Len, false);
        return LIGHT_OK;
}

uint8_t light_board_i2c_read_byte(uint8_t device_id, uint8_t addr, uint8_t reg, uint8_t *out_data)
{
        i2c_inst_t *handle;
        if(!_light_board_device_id_to_handle_i2c(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;

        i2c_write_blocking(handle,addr,&reg,1,true);
        i2c_read_blocking(handle,addr,out_data,1,false);
        return LIGHT_OK;
}

uint8_t light_board_spi_device_id_next()
{
        if(spi_port_next < LIGHT_BOARD_SPI_PORT_MAX) {
                return spi_port_next++;
        } else {
                return LIGHT_BOARD_SPI_PORT_NONE;
        }
}

uint8_t light_board_spi_device_id_max()
{
        return LIGHT_BOARD_SPI_PORT_MAX;
}

uint32_t light_board_spi_device_init(uint8_t device_id, uint32_t baudrate, uint8_t pin_clk, uint8_t pin_miso, uint8_t pin_mosi)
{
        spi_inst_t *handle;
        if(!_light_board_device_id_to_handle_spi(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;
        
        spi_init(handle, baudrate);
        return LIGHT_OK;
}

uint8_t light_board_spi_device_deinit(uint8_t device_id)
{
        spi_inst_t *handle;
        if(!_light_board_device_id_to_handle_spi(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;
        
        spi_deinit(handle);
        return LIGHT_OK;
}

uint8_t light_board_spi_write_byte(uint8_t device_id, uint8_t data)
{
        spi_inst_t *handle;
        if(!_light_board_device_id_to_handle_spi(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;
        
        spi_write_blocking(handle, &data, 1);
        return LIGHT_OK;

}
uint8_t light_board_spi_write_bytes(uint8_t device_id, uint8_t *p_data, uint32_t length)
{
        spi_inst_t *handle;
        if(!_light_board_device_id_to_handle_spi(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;
        
        spi_write_blocking(handle, p_data, length);
        return LIGHT_OK;

}

uint8_t light_board_spi_read_byte(uint8_t device_id, uint8_t *out_data)
{
        spi_inst_t *handle;
        if(!_light_board_device_id_to_handle_spi(device_id, &handle))
                return LIGHT_RESOURCE_UNAVAILABLE;
        
        spi_read_blocking(handle, 0x00, out_data, 1);
        return LIGHT_OK;
}

// TODO make this junk configurable via API
uint8_t light_board_pwm_device_init(uint8_t pin)
{
        uint8_t slice = pwm_gpio_to_slice_num(pin);
        uint8_t channel = pwm_gpio_to_channel(pin);

        pwm_config conf;

        // 350kHz clock
        pwm_config_set_clkdiv(&conf, 380.0f);

        pwm_init(slice, &conf, false);

        
        return LIGHT_OK;
}
void light_board_pwm_device_deinit(uint8_t pin)
{
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), false);
}

void light_board_pwm_device_start(uint8_t pin)
{
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), true);

}
void light_board_pwm_device_stop(uint8_t pin)
{
        pwm_set_enabled(pwm_gpio_to_slice_num(pin), false);
}

void light_board_sleep_ms(uint32_t xms)
{
        sleep_ms(xms);
}
void light_board_sleep_us(uint32_t xus)
{
        sleep_us(xus);
}

uint8_t light_board_init(void)
{
    stdio_init_all();
    
    /*
    // PWM Config
    gpio_set_function(EPD_BL_PIN, GPIO_FUNC_PWM);
    slice_num = pwm_gpio_to_slice_num(EPD_BL_PIN);
    pwm_set_wrap(slice_num, 100);
    pwm_set_chan_level(slice_num, PWM_CHAN_B, 1);
    pwm_set_clkdiv(slice_num,50);
    pwm_set_enabled(slice_num, true);
    */
    
    light_log(LIGHT_INFO, "%s: init OK", __func__);
    return LIGHT_OK;
}

/*
void light_board_set_pwm(uint8_t Value){
    if(Value<0 || Value >100){
        printf("board_set_pwm Error \r\n");
    }else {
        pwm_set_chan_level(slice_num, PWM_CHAN_B, Value);
    }
}
*/

void light_board_exit(void)
{

}

void _light_board_log_handler(const char *msg)
{
    printf("[light]: %s", msg);
}

uint8_t _light_board_device_id_to_handle_spi(uint8_t id, spi_inst_t **out_handle)
{
        switch (id)
        {
        case 0:
                *out_handle = spi0;
                return true;
        case 1:
                *out_handle = spi1;
                return true;
        default:
                *out_handle = NULL;
                return false;
        }
}

uint8_t _light_board_device_id_to_handle_i2c(uint8_t id, i2c_inst_t **out_handle)
{
        switch (id)
        {
        case 0:
                *out_handle = i2c0;
                return true;
        case 1:
                *out_handle = i2c1;
                return true;
        default:
                *out_handle = NULL;
                return false;
        }
}