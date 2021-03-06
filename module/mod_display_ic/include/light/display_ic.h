/*****************************************************************************
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documnetation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to  whom the Software is
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
#ifndef __LIGHT_DISPLAY_IC_SH1107_H
#define __LIGHT_DISPLAY_IC_SH1107_H		

#include "light/board.h"

/********************************************************************************
function:	
		Define the full screen height length of the display
********************************************************************************/
#define USE_SPI 1
#define USE_IIC 0

#define IIC_CMD        0X00
#define IIC_RAM        0X40

#define OLED_CS_0      DEV_Digital_Write(EPD_CS_PIN,0)
#define OLED_CS_1      DEV_Digital_Write(EPD_CS_PIN,1)

#define OLED_RST_0      DEV_Digital_Write(EPD_RST_PIN,0)
#define OLED_RST_1      DEV_Digital_Write(EPD_RST_PIN,1)

#define OLED_DC_0       DEV_Digital_Write(EPD_DC_PIN,0)
#define OLED_DC_1       DEV_Digital_Write(EPD_DC_PIN,1)




void display_sh1107_init(uint8_t id);
void display_sh1107_clear_screen(void);
void OLED_1in3_C_Display(const UBYTE *Image);

#endif  
