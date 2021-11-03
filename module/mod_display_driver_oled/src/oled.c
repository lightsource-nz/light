
#include "oled.h"
#include "stdio.h"

/*******************************************************************************
function:
			Hardware reset
*******************************************************************************/
static void OLED_Reset(void)
{
    OLED_RST_1;
    DEV_Delay_ms(100);
    OLED_RST_0;
    DEV_Delay_ms(100);
    OLED_RST_1;
    DEV_Delay_ms(100);
}

/*******************************************************************************
function:
			Write register address and data
*******************************************************************************/
static void driver_oled_write_register(uint8_t Reg)
{
#if USE_SPI
    OLED_DC_0;
    OLED_CS_0;
    board_spi_write_byte(Reg);
    OLED_CS_1;
#elif USE_IIC
    board_i2c_write_byte(Reg,IIC_CMD);
#endif
}

static void driver_oled_write_data(uint8_t Data)
{	
#if USE_SPI
    OLED_DC_1;
    OLED_CS_0;
    board_spi_write_byte(Data);
    OLED_CS_1;
#elif USE_IIC
    board_i2c_write_byte(Data,IIC_RAM);
#endif
}

/*******************************************************************************
function:
			Common register initialization
*******************************************************************************/
static void OLED_InitReg(void)
{
    driver_oled_write_register(0xae);	/*turn off OLED display*/

    driver_oled_write_register(0x00);	/*set lower column address*/ 
    driver_oled_write_register(0x10);	/*set higher column address*/ 

    driver_oled_write_register(0xB0);	/*set page address*/ 
	
    driver_oled_write_register(0xdc);	/*set display start line*/ 
    driver_oled_write_register(0x00);  

    driver_oled_write_register(0x81);	/*contract control*/ 
    driver_oled_write_register(0x6f);	/*128*/ 
    driver_oled_write_register(0x21);  	/* Set Memory addressing mode (0x20/0x21) */ 
	
    driver_oled_write_register(0xa0); 	/*set segment remap*/ 
    driver_oled_write_register(0xc0);  	/*Com scan direction*/ 
    driver_oled_write_register(0xa4);	/*Disable Entire Display On (0xA4/0xA5)*/ 

    driver_oled_write_register(0xa6);	/*normal / reverse*/
    driver_oled_write_register(0xa8);	/*multiplex ratio*/ 
    driver_oled_write_register(0x3f);  	/*duty = 1/64*/ 
  
    driver_oled_write_register(0xd3);  	/*set display offset*/ 
    driver_oled_write_register(0x60);

    driver_oled_write_register(0xd5);	/*set osc division*/ 
    driver_oled_write_register(0x41);
		
    driver_oled_write_register(0xd9); 	/*set pre-charge period*/ 
    driver_oled_write_register(0x22);   

    driver_oled_write_register(0xdb); 	/*set vcomh*/ 
    driver_oled_write_register(0x35);  

    driver_oled_write_register(0xad); 	/*set charge pump enable*/ 
    driver_oled_write_register(0x8a);	/*Set DC-DC enable (a=0:disable; a=1:enable) */
}


/********************************************************************************
function:
			initialization
********************************************************************************/
void oled_init()
{
    //Hardware reset
    oled_do_reset();
    
    //Set the initialization register
    OLED_InitReg();
    DEV_Delay_ms(200);

    //Turn on the OLED display
    OLED_WriteReg(0xaf);
}


/********************************************************************************
function:
			Clear screen
********************************************************************************/
void display_oled_clear_screen(uint8_t id)
{
	uint8_t Width, Height, column;
	Width = (OLED_1in3_C_WIDTH % 8 == 0)? (OLED_1in3_C_WIDTH / 8 ): (OLED_1in3_C_WIDTH / 8 + 1);
	Height = OLED_1in3_C_HEIGHT;  
	OLED_WriteReg(0xb0); 	//Set the row  start address
	for (uint8_t j = 0; j < Height; j++) {
		column = 63 - j;
		OLED_WriteReg(0x00 + (column & 0x0f));  //Set column low start address
		OLED_WriteReg(0x10 + (column >> 4));  //Set column higt start address
		for (uint8_t i = 0; i < Width; i++) {
			OLED_WriteData(0x00);
		 }
	}
}

/********************************************************************************
function:   
            reverse a byte data
********************************************************************************/
static uint8_t reverse(uint8_t temp)
{
    temp = ((temp & 0x55) << 1) | ((temp & 0xaa) >> 1);
    temp = ((temp & 0x33) << 2) | ((temp & 0xcc) >> 2);
    temp = ((temp & 0x0f) << 4) | ((temp & 0xf0) >> 4);  
    return temp;
}

/********************************************************************************
function:	
			Update all memory to OLED
********************************************************************************/
void driver_oled_display_show(const UBYTE *Image)
{		
    UWORD Width, Height, column, temp;
    Width = (OLED_1in3_C_WIDTH % 8 == 0)? (OLED_1in3_C_WIDTH / 8 ): (OLED_1in3_C_WIDTH / 8 + 1);
    Height = OLED_1in3_C_HEIGHT;   
    OLED_WriteReg(0xb0); 	//Set the row  start address
    for (UWORD j = 0; j < Height; j++) {
        column = 63 - j;
        OLED_WriteReg(0x00 + (column & 0x0f));  //Set column low start address
        OLED_WriteReg(0x10 + (column >> 4));  //Set column higt start address
        for (UWORD i = 0; i < Width; i++) {
            temp = Image[i + j * Width];
            // printf("0x%x \r\n",temp);
            temp = reverse(temp);	//reverse the buffer
            OLED_WriteData(temp);
         }
    }   
}


