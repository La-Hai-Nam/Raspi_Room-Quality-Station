/*****************************************************************************
* | File      	:   oled_1in5.c
* | Author      :   Waveshare team
* | Function    :   1.5inch oled Module Drive function
* | Info        :
*----------------
* |	This version:   V2.0
* | Date        :   2020-08-15
* | Info        :
* -----------------------------------------------------------------------------
#
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
#
******************************************************************************/
#include "oled_1in5.h"
#include "stdio.h"

/*******************************************************************************
function:
            Hardware reset
*******************************************************************************/
static void oled_Reset(void)
{
    oled_RST_1;
    DEV_Delay_ms(100);
    oled_RST_0;
    DEV_Delay_ms(100);
    oled_RST_1;
    DEV_Delay_ms(100);
}

/*******************************************************************************
function:
            Write register address and data
*******************************************************************************/
static void oled_WriteReg(uint8_t Reg)
{
#if USE_SPI
    oled_DC_0;
    DEV_SPI_WriteByte(Reg);
#elif USE_IIC
    I2C_Write_Byte(Reg,IIC_CMD);
#endif
}

static void oled_WriteData(uint8_t Data)
{   
#if USE_SPI
    oled_DC_1;
    DEV_SPI_WriteByte(Data);
#elif USE_IIC
    I2C_Write_Byte(Data,IIC_RAM);
#endif
}

/*******************************************************************************
function:
        Common register initialization
*******************************************************************************/
static void oled_InitReg(void)
{
    oled_WriteReg(0xae);//--turn off oled panel

    oled_WriteReg(0x15);    //   set column address
    oled_WriteReg(0x00);    //  start column   0
    oled_WriteReg(0x7f);    //  end column   127

    oled_WriteReg(0x75);    //   set row address
    oled_WriteReg(0x00);    //  start row   0
    oled_WriteReg(0x7f);    //  end row   127

    oled_WriteReg(0x81);  // set contrast control
    oled_WriteReg(0x80);

    oled_WriteReg(0xa0);    // gment remap
    oled_WriteReg(0x51);   //51

    oled_WriteReg(0xa1);  // start line
    oled_WriteReg(0x00);

    oled_WriteReg(0xa2);  // display offset
    oled_WriteReg(0x00);

    oled_WriteReg(0xa4);    // rmal display
    oled_WriteReg(0xa8);    // set multiplex ratio
    oled_WriteReg(0x7f);

    oled_WriteReg(0xb1);  // set phase leghth
    oled_WriteReg(0xf1);

    oled_WriteReg(0xb3);  // set dclk
    oled_WriteReg(0x00);  //80Hz:0xc1 90Hz:0xe1   100Hz:0x00   110Hz:0x30 120Hz:0x50   130Hz:0x70     01

    oled_WriteReg(0xab);  //
    oled_WriteReg(0x01);  //

    oled_WriteReg(0xb6);  // set phase leghth
    oled_WriteReg(0x0f);

    oled_WriteReg(0xbe);
    oled_WriteReg(0x0f);

    oled_WriteReg(0xbc);
    oled_WriteReg(0x08);

    oled_WriteReg(0xd5);
    oled_WriteReg(0x62);

    oled_WriteReg(0xfd);
    oled_WriteReg(0x12);

}

/********************************************************************************
function:
            initialization
********************************************************************************/
void oled_1in5_Init(void)
{
    //Hardware reset
    oled_Reset();

    //Set the initialization register
    oled_InitReg();
    DEV_Delay_ms(200);

    //Turn on the oled display
    oled_WriteReg(0xAF);
}

/********************************************************************************
function:   Set the display Window(Xstart, Ystart, Xend, Yend)
parameter:
        xStart :   X direction Start coordinates
        Ystart :   Y direction Start coordinates
        Xend   :   X direction end coordinates
        Yend   :   Y direction end coordinates
********************************************************************************/
static void oled_SetWindow(UBYTE Xstart, UBYTE Ystart, UBYTE Xend, UBYTE Yend)
{
    if((Xstart > oled_1in5_WIDTH) || (Ystart > oled_1in5_HEIGHT) ||
       (Xend > oled_1in5_WIDTH) || (Yend > oled_1in5_HEIGHT))
        return;

    oled_WriteReg(0x15);
    oled_WriteReg(Xstart/2);
    oled_WriteReg(Xend/2 - 1);

    oled_WriteReg(0x75);
    oled_WriteReg(Ystart);
    oled_WriteReg(Yend - 1);
}

/********************************************************************************
function:
            Clear screen
********************************************************************************/
void oled_1in5_Clear(void)
{
    UWORD i;
    oled_SetWindow(0, 0, 128, 128);
    for(i=0; i<oled_1in5_WIDTH*oled_1in5_HEIGHT/2; i++){
        oled_WriteData(0x00);
    }
}

/********************************************************************************
function:   Update all memory to oled
********************************************************************************/
void oled_1in5_Display(UBYTE *Image)
{
    UWORD i, j, temp;
    oled_SetWindow(0, 0, 128, 128);
    for(i=0; i<oled_1in5_HEIGHT; i++)
        for(j=0; j<oled_1in5_WIDTH/2; j++)
        {
            temp = Image[j + i*64];
            oled_WriteData(temp);
        }
}
