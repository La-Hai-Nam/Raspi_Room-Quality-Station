/*****************************************************************************
* | File      	:   OLED_1in5_test.c
* | Author      :   Waveshare team
* | Function    :   1.5inch OLED Module test demo
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
#include <stdlib.h>
#include "test.h"
#include "OLED_1in5.h"
#include "interrupt.h"
#include "bme_test.h"
/******************************************************************************
function:	Initialize Display, Black image and interrupt button on GPIO5 for push button:
Info:
******************************************************************************/
int OLED_1in5_test(void)
{
	printf("1.5inch OLED test demo\n");
	if(DEV_ModuleInit() != 0) {
		return -1;
	}
	  
	printf("OLED Init...\r\n");
	OLED_1in5_Init();
	DEV_Delay_ms(500);	
	// 0.Create a new image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((OLED_1in5_WIDTH%2==0)? (OLED_1in5_WIDTH/2): (OLED_1in5_WIDTH/2+1)) * OLED_1in5_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			return -1;
	}
	printf("Paint_NewImage\r\n");
	Paint_NewImage(BlackImage, OLED_1in5_WIDTH, OLED_1in5_HEIGHT, 0, BLACK);	
	Paint_SetScale(16);
	printf("Drawing\r\n");
	//1.Select Image
	Paint_SelectImage(BlackImage);
	DEV_Delay_ms(500);
	Paint_Clear(BLACK);
	attach_GPIO(BUTTON, IN, FALLING, button_pressed());
	
}

/******************************************************************************
function:	Get sensor data from bme_test.c and display sensor data on the OLEDdisplay depending on count (if button_pressed() == true){ count++; }:
Info:
******************************************************************************/

OLED_while(bmedata s) {
			
	char temperature[MAX];
	char pressure[MAX];
	char humidity[MAX];
	char gas_resistance[MAX];
		UBYTE *BlackImage;
		UWORD Imagesize = ((OLED_1in5_WIDTH%2==0)? (OLED_1in5_WIDTH/2): 	(OLED_1in5_WIDTH/2+1)) * OLED_1in5_HEIGHT;
		if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			return -1;
		}
		Paint_NewImage(BlackImage, OLED_1in5_WIDTH, OLED_1in5_HEIGHT, 0, BLACK);	
		Paint_SetScale(16);
		Paint_SelectImage(BlackImage);
		DEV_Delay_ms(500);
		Paint_Clear(BLACK);
		snprintf(temperature, MAX, "%.2f", s.temperature);
		snprintf(pressure, MAX, "%.2f", s.pressure);
		snprintf(humidity, MAX, "%.2f", s.humidity);
		snprintf(gas_resistance, MAX, "%.2f", s.gas_resistance);
		
		char temperature_unit[MAX] = strcat(temperature, "%%");

		switch (get_count()) {
			case 1:
				printf("temperature: %s\r\n", temperature);			
				Paint_DrawString_EN(10, 0, "Temperature", &Font12, WHITE, WHITE);
				Paint_DrawString_EN(64, 56, temperature, &Font12, WHITE, WHITE);
				OLED_1in5_Display(BlackImage);
				DEV_Delay_ms(100);				
				break;
			case 2:
				printf("humidity: %s\r\n", humidity);			
				Paint_DrawString_EN(10, 0, "humidity", &Font12, WHITE, WHITE);
				Paint_DrawString_EN(64, 56, humidity, &Font12, WHITE, WHITE);
				OLED_1in5_Display(BlackImage);
				DEV_Delay_ms(100);				
				break;
			case 3:
				printf("pressure: %s\r\n", pressure);			
				Paint_DrawString_EN(10, 0, "pressure", &Font12, WHITE, WHITE);
				Paint_DrawString_EN(64, 56, pressure, &Font12, WHITE, WHITE);
				OLED_1in5_Display(BlackImage);
				DEV_Delay_ms(100);				
				break;
			case 4:
				printf("airquality: %s\r\n", gas_resistance);			
				Paint_DrawString_EN(10, 0, "gas_resistance", &Font12, WHITE, WHITE);
				Paint_DrawString_EN(64, 56, gas_resistance, &Font12, WHITE, WHITE);
				OLED_1in5_Display(BlackImage);
				DEV_Delay_ms(100);			
				break;
		}
	}
