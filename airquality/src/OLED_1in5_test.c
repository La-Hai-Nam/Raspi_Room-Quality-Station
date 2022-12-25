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
#include <math.h>

int first_time;
int second_time;

/******************************************************************************
function:	paint temperature thermometer
Info:
******************************************************************************/
void Paint_thermo(){

// draw stem/glass/container of liquid 
	Paint_DrawLine(29, 42, 35, 42, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(28, 43, 29, 43, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(35, 43, 36, 43, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(28, 44, 28, 45, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(36, 44, 36, 46, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(28, 44, 28, 45, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(36, 44, 36, 46, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(27, 45, 27, 79, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(37, 45, 37, 79, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawPoint(26, 80, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(38, 80, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);

	Paint_DrawPoint(25, 81, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(39, 81, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);

	Paint_DrawLine(24, 82, 24, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(40, 82, 40, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(23, 84, 23, 90, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(41, 84, 41, 90, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(24, 91, 24, 92, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(40, 91, 40, 92, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(25, 93, 25, 94, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(39, 93, 39, 94, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawPoint(26, 94, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(38, 94, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);

	Paint_DrawLine(27, 95, 28, 95, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(36, 95, 37, 95, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(29, 96, 35, 96, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(38, 53, 40, 53, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(38, 62, 40, 62, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);Paint_DrawLine(38, 71, 40, 71, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);



//	liquid
	Paint_DrawLine(30, 67, 34, 67, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 68, 34, 68, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 69, 34, 69, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 70, 34, 70, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 71, 34, 71, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 72, 34, 72, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 73, 34, 73, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 74, 34, 74, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 75, 34, 75, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 76, 34, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 77, 34, 77, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 78, 34, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 79, 34, 79, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 80, 34, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(29, 81, 35, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 82, 36, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 83, 37, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 84, 37, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 85, 38, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 86, 38, 86, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 87, 38, 87, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 88, 38, 88, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 89, 38, 89, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 90, 37, 90, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 91, 37, 91, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 92, 36, 92, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(29, 93, 35, 93, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

}

/******************************************************************************
function:	paint humidity droplet
Info:
******************************************************************************/
void Paint_droplet(){
	Paint_DrawPoint(32, 38, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(32, 39, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawLine(31, 40, 33, 40, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(31, 41, 33, 41, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(31, 42, 33, 42, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 43, 34, 43, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 44, 34, 44, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 45, 34, 45, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(29, 46, 35, 46, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(29, 47, 35, 47, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(29, 48, 35, 48, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 49, 36, 49, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 50, 36, 50, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 51, 36, 51, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 52, 37, 52, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 53, 37, 53, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 54, 37, 54, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 55, 38, 55, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 56, 38, 56, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 57, 38, 57, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(25, 58, 39, 58, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(25, 59, 39, 59, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(25, 60, 39, 60, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 61, 40, 61, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 62, 40, 62, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 63, 40, 63, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(23, 64, 41, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(23, 65, 41, 65, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(23, 66, 41, 66, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(22, 67, 42, 67, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(22, 68, 42, 68, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(22, 69, 42, 69, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(21, 70, 43, 70, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(21, 71, 43, 71, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(21, 72, 43, 72, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(20, 73, 44, 73, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(20, 74, 44, 74, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(20, 75, 44, 75, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(19, 76, 45, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(19, 77, 45, 77, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(18, 78, 46, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(18, 79, 46, 79, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(17, 80, 47, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(17, 81, 47, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(17, 82, 47, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 83, 48, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 84, 48, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 85, 48, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 86, 48, 86, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(16, 87, 19, 87, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 88, 19, 88, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 89, 19, 89, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(23, 87, 48, 87, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 88, 48, 88, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 89, 48, 89, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(17, 90, 20, 90, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(17, 91, 20, 91, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(17, 92, 21, 92, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(25, 90, 47, 90, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(25, 91, 47, 91, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 92, 47, 92, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(18, 93, 22, 93, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(18, 94, 23, 94, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 93, 46, 93, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 94, 46, 94, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(19, 95, 24, 95, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 95, 45, 95, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(20, 96, 26, 96, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(31, 96, 44, 96, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(21, 97, 28, 97, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(32, 97, 43, 97, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(22, 98, 42, 98, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 99, 40, 99, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 100, 38, 100, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(28, 101, 36, 101, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}

/******************************************************************************
function:	paint pressure barometer
Info:
******************************************************************************/
void Paint_barometer(){
// outer area
	Paint_DrawLine(27, 51, 37, 51, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 52, 40, 52, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(22, 53, 42, 53, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(21, 54, 26, 54, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(38, 54, 43, 54, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	
	Paint_DrawLine(21, 55, 24, 55, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(40, 55, 43, 55, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(21, 56, 22, 56, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(42, 56, 43, 56, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(20, 55, 20, 57, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(20, 83, 20, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(19, 55, 19, 58, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(19, 82, 19, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(18, 56, 18, 60, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(18, 80, 18, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(17, 57, 17, 61, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(17, 79, 17, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(16, 59, 16, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 76, 16, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(15, 60, 15, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(14, 62, 14, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(13, 65, 13, 75, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(21, 86, 26, 86, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(38, 86, 43, 86, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	
	Paint_DrawLine(21, 85, 24, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(40, 85, 43, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(21, 84, 22, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(42, 84, 43, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(27, 89, 37, 89, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 88, 40, 88, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(22, 87, 42, 87, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	
	Paint_DrawLine(44, 55, 44, 57, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(44, 83, 44, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(45, 55, 45, 58, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(45, 82, 45, 85, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(46, 56, 46, 60, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(46, 80, 46, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(47, 57, 47, 61, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(47, 79, 47, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(48, 59, 48, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(48, 76, 48, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(49, 60, 49, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(50, 62, 50, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(51, 65, 51, 75, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

// scale

	Paint_DrawLine(19, 65, 19, 74, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(20, 64, 20, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(21, 62, 21, 66, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(21, 74, 21, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(22, 61, 22, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(22, 76, 22, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(23, 60, 23, 62, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(23, 77, 23, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(24, 59, 24, 63, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(24, 76, 24, 77, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(25, 63, 25, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(25, 75, 25, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(26, 64, 26, 65, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(27, 57, 36, 57, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(26, 58, 38, 58, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	
	Paint_DrawLine(25, 59, 28, 59, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(36, 59, 38, 59, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	
	Paint_DrawLine(25, 60, 26, 60, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(38, 60, 39, 60, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(45, 65, 45, 74, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(44, 64, 44, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(43, 62, 43, 66, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(43, 74, 43, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(42, 61, 42, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(42, 76, 42, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(41, 60, 41, 62, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(41, 77, 41, 78, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(40, 59, 40, 63, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(40, 76, 40, 77, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(39, 63, 39, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(39, 75, 39, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(38, 64, 38, 65, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//indicator
	Paint_DrawLine(29, 78, 29, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(30, 77, 30, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(31, 76, 31, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(32, 64, 32, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(33, 76, 33, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(34, 77, 34, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(35, 78, 35, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
}

void Paint_Cloud(){
	Paint_DrawLine(29, 51, 38, 51, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(27, 52, 40, 52, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(25, 53, 29, 53, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(38, 53, 42, 53, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	
	Paint_DrawLine(23, 54, 27, 54, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(40, 54, 44, 54, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(22, 55, 25, 55, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(42, 55, 45, 55, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(21, 56, 23, 56, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(44, 56, 45, 56, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(20, 57, 22, 57, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawPoint(45, 57, WHITE, DOT_PIXEL_1X1, DOT_STYLE_DFT);

	Paint_DrawLine(20, 58, 21, 58, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(18, 59, 21, 59, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(15, 60, 20, 60, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(14, 61, 18, 61, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(13, 62, 15, 62, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(13, 63, 14, 63, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(12, 62, 12, 64, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(12, 79, 12, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(11, 63, 11, 66, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(11, 77, 11, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(10, 64, 10, 68, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(10, 75, 10, 79, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(9, 66, 9, 77, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(8, 68, 8, 75, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(13, 80, 13, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(14, 80, 14, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(15, 81, 15, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(18, 84, 46, 84, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(16, 83, 48, 83, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(48, 81, 49, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(16, 82, 18, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(46, 82, 49, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);


	Paint_DrawLine(46, 56, 46, 59, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(47, 57, 47, 61, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(48, 59, 48, 65, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(49, 61, 49, 66, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(50, 65, 50, 67, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(50, 80, 50, 82, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(51, 66, 51, 68, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(51, 79, 51, 81, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(52, 67, 52, 71, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(52, 76, 52, 80, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);

	Paint_DrawLine(53, 68, 53, 79, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(54, 71, 54, 76, WHITE, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	
}
/******************************************************************************
function:	screensaver that turns off display after 10 min of same state 
Info:
******************************************************************************/
screensaver(){
	if(get_do_once() == 0){
		first_time = (int)time(NULL);
		increment_do_once();
	}
	second_time = (int)time(NULL);
	if((second_time - first_time) >= 600){
		change_count(6);
	}

}
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
	attach_GPIO(BUTTON_DATA, BUTTON_ONOFF, IN, FALLING);
	
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
	char gas [MAX];


	float hum_weighting = 0.25; // so hum effect is 25% of the total air quality score
	float gas_weighting = 0.75; // so gas effect is 75% of the total air quality score

	float hum_score, gas_score;
	float gas_reference = 250000;
	float hum_reference = 40;

	char temperature_unit[MAX] = "C";
	char pressure_unit[MAX] = "hPA";
	char humidity_unit[MAX] = "%";
	char gas_resistance_unit[MAX] = "%";

	struct bme680_dev* sensor = (struct bme680_dev*)malloc(sizeof(struct bme680_dev));
	struct bme680_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));
	
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

	/*************************** IAQ calculation *************************************/

	float current_humidity = s.humidity;
	if (current_humidity >= 38 && current_humidity <= 42)
		hum_score = 0.25*100; // Humidity +/-5% around optimum 
	else
	{ //sub-optimal
		if (current_humidity < 38) 
		hum_score = 0.25/hum_reference*current_humidity*100;
		else
		{
		hum_score = ((-0.25/(100-hum_reference)*current_humidity)+0.416666)*100;
		}
	}
	
	//Calculate gas contribution to IAQ index
	float gas_lower_limit = 5000;   // Bad air quality limit
	float gas_upper_limit = 50000;  // Good air quality limit 
	float gas_ref;
	if (s.gas_resistance > gas_upper_limit) {
		gas_ref = gas_upper_limit;
	}else if(s.gas_resistance < gas_lower_limit){
			gas_ref = gas_lower_limit;
	}else{
		gas_ref = s.gas_resistance;
	}
	gas_score = (0.75/(gas_upper_limit-gas_lower_limit)*gas_ref -(gas_lower_limit*(0.75/(gas_upper_limit-gas_lower_limit))))*100;
	
	float air_quality_score = hum_score + gas_score;
	//Combine results for the final IAQ index value (0-100% where 100% is good quality air)
/*********************************************************************************/	
	//save float data values in char
	snprintf(temperature, MAX, "%.1f", (s.temperature - 2));
	snprintf(pressure, MAX, "%.0f", s.pressure);
	snprintf(humidity, MAX, "%.1f", s.humidity);
	snprintf(gas_resistance, MAX, "%.1f",air_quality_score);

/*************************** different states of display **********************/	
	switch (get_count()) {	
		case 0:
			Paint_DrawString_EN(22, 5, "Air Quality", &Font12, WHITE, WHITE);
			Paint_DrawString_EN(37, 25, "Station", &Font12, WHITE, WHITE);
			Paint_DrawString_EN(25, 64, "Welcome", &Font16, WHITE, WHITE);
			OLED_1in5_Display(BlackImage);
			DEV_Delay_ms(2000);
			Paint_Clear(BLACK);
			increment_count();
		case 1:
			printf("temperature: %s\r\n", temperature);	
			Paint_thermo();
			Paint_DrawLine(0, 2, 128, 2, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);		
			Paint_DrawString_EN(10, 5, "Temperature", &Font12, WHITE, WHITE);
			Paint_DrawLine(0, 20, 128, 20, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
			Paint_DrawString_EN(64, 60, temperature, &Font20, WHITE, WHITE);
			Paint_DrawString_EN(106, 80, temperature_unit, &Font20, WHITE, WHITE);
			OLED_1in5_Display(BlackImage);
			DEV_Delay_ms(100);
			screensaver();				
			break;
		case 2:
			printf("humidity: %s\r\n", humidity);	
			Paint_droplet();
			Paint_DrawLine(0, 2, 128, 2, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);		
			Paint_DrawString_EN(10, 5, "Humidity", &Font12, WHITE, WHITE);
			Paint_DrawLine(0, 20, 128, 20, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
			Paint_DrawString_EN(64, 60, humidity, &Font20, WHITE, WHITE);
			Paint_DrawString_EN(106, 80, humidity_unit, &Font20, WHITE, WHITE);
			OLED_1in5_Display(BlackImage);
			DEV_Delay_ms(100);	
			screensaver();			
			break;
		case 3:
			printf("pressure: %s\r\n", pressure);
			Paint_barometer();		
			Paint_DrawLine(0, 2, 128, 2, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);	
			Paint_DrawString_EN(10, 5, "Pressure", &Font12, WHITE, WHITE);
			Paint_DrawLine(0, 20, 128, 20, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
			Paint_DrawString_EN(64, 60, pressure, &Font20, WHITE, WHITE);
			Paint_DrawString_EN(80, 80, pressure_unit, &Font20, WHITE, WHITE);
			OLED_1in5_Display(BlackImage);
			DEV_Delay_ms(100);	
			screensaver();		
			break;
		case 4:
			printf("airquality: %s \r\n",gas_resistance);
			Paint_Cloud();
			Paint_DrawString_EN(18, 65, "AirQ", &Font12, WHITE, WHITE);
			Paint_DrawLine(0, 2, 128, 2, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);			
			Paint_DrawString_EN(10, 5, "Air Quality", &Font12, WHITE, WHITE);
			Paint_DrawLine(0, 20, 128, 20, WHITE, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
			Paint_DrawString_EN(64, 60, gas_resistance, &Font20, WHITE, WHITE);
			Paint_DrawString_EN(106, 80, gas_resistance_unit, &Font20, WHITE, WHITE);
			OLED_1in5_Display(BlackImage);
			DEV_Delay_ms(100);		
			screensaver();	
			break;
		case 5:
			Paint_DrawString_EN(25, 5, "Shutting Down", &Font16, WHITE, WHITE);
			OLED_1in5_Display(BlackImage);
			DEV_Delay_ms(2000);
			Paint_Clear(BLACK);
			OLED_1in5_Clear();
			DEV_ModuleExit();
			sensor_disable(sensor, data);
			system("sudo shutdown -r now");
			break;
		case 6:
		Paint_Clear(BLACK);
		OLED_1in5_Display(BlackImage);
		break;
	}
	}
