#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "test.h"
#include <string.h>
#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"
#include "bme_test.h"

/******************************************************************************
function:	Handler for ctrl+c interrupt(only appliable when debugging the code):
Parameter: int signo is the singal which terminates the code (ctrl+c)
Info:
******************************************************************************/

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    Paint_Clear(BLACK);
    oled_1in5_Clear();
    DEV_ModuleExit();
    exit(0);
}



int main(int argc, char *argv[])
{

    struct bme680_dev* sensor = (struct bme680_dev*)malloc(sizeof(struct bme680_dev));
    struct bme680_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));

    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

   //initialize all used components
    oled_1in5_init();
    bme_init(sensor);
    //main while loop where display, sensor and buzzer are run in loop
    while (1){
        oled_while(bme_while(sensor, data));
    }

	return 0;
	
}
