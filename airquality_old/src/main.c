#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "test.h"
#include <string.h>
#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"
#include "bme_test.h"


void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    Paint_Clear(BLACK);
    OLED_1in5_Clear();
    DEV_ModuleExit();
    exit(0);
}



int main(int argc, char *argv[])
{

    struct bme680_dev* sensor = (struct bme680_dev*)malloc(sizeof(struct bme680_dev));
    struct bme680_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    OLED_1in5_test();
    bme_init(sensor);

    while (1){
        OLED_while(bme_while(sensor, data));
        
    }

	// Paint_Clear(BLACK);
    // OLED_1in5_Clear();
    // DEV_ModuleExit();
    // sensor_disable(sensor, data);
	return 0;
	
}
