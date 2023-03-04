#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "test.h"
#include <string.h>
#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"
#include "gpio_sysf.h"
#include "buzzer.h"
#include "OLED_1in5.h"
#include "procfile_utils.h"

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
    OLED_1in5_Clear();
    DEV_ModuleExit();
	buzzer_off();
	buzzer_end();
    exit(0);
}


int main(int argc, char *argv[])
{
    UBYTE *black_image;
	UWORD Imagesize = ((OLED_1in5_WIDTH%2==0)? (OLED_1in5_WIDTH/2): 	(OLED_1in5_WIDTH/2+1)) * OLED_1in5_HEIGHT;
	if((black_image = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
    struct bme680_dev* sensor = (struct bme680_dev*)malloc(sizeof(struct bme680_dev));
    struct bme680_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));

    int current_mode;
	int fd = open_procfile();
    
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);

    //initialize all used components
    oled_init(black_image);
    sensor_init(sensor);
	open_procfile();
    buzzer_initialize();


    //main while loop where display, sensor and buzzer are run in loop
    while (1){
		sensor_get_all_data(sensor, data);	
		current_mode = get_procfile_mode_number(fd);
        oled_while(black_image, current_mode, data, fd); 
        if(current_mode == 5) {
            OLED_1in5_Clear();
            DEV_ModuleExit();
            sensor_disable(sensor, data);
            buzzer_off();
            buzzer_end();
            system("sudo shutdown -h now");
            return 0;
        }
        set_buzzer_alarm(data);
    }

	return 0;
	
}
