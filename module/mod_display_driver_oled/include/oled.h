#ifndef __OLED_H
#define __OLED_H		

#include "config_display_board.h"


#define OLED_CS_0      board_gpio_write(EPD_CS_PIN,0)
#define OLED_CS_1      board_gpio_write(EPD_CS_PIN,1)

#define OLED_RST_0      board_gpio_write(EPD_RST_PIN,0)
#define OLED_RST_1      board_gpio_write(EPD_RST_PIN,1)

#define OLED_DC_0       board_gpio_write(EPD_DC_PIN,0)
#define OLED_DC_1       board_gpio_write(EPD_DC_PIN,1)


void display_oled_clear_screen(void);
void display_oled_show_image(const uint8_t *image);

#endif  
	 
