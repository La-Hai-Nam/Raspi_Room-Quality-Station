//Includes
#include "gpio_sysf.h"
#include "buzzer.h"
#include <stdlib.h>
//#include "gpio.h"



//Thresholds
//Values have to be defined!! The following are just examples
const float thmax_temp = 25.0, thmax_air_quality = 298.0, thmax_humidity = 65.0;                  //Maximum thresholds
const float thmin_temp = 0.0, thmin_air_quality = 1.0, thmin_humidity = 20.0;                  //Minimum thresholds


//Variables for functions
int buzzer_pin = 12;


//Buzzer functions
void buzzer_initialize(){
    gpio_export(buzzer_pin);
    //GPIO_direction(buzzer_pin, "out");
	system("sudo echo \"out\" > /sys/class/gpio/gpio12/direction");
}

void buzzer_end(){
    gpio_unexport(buzzer_pin);
}

void buzzer_on(){
    gpio_value(buzzer_pin, 1);
}

void buzzer_off(){
    gpio_value(buzzer_pin, 0);
}

void buzzer_toggle(){
    if(gpio_read(buzzer_pin) == 0){
        gpio_value(buzzer_pin, 1);
    }else{
        gpio_value(buzzer_pin, 0);
    }
}

void set_buzzer_alarm(struct bme680_field_data* data){
	
	//printf("temp: %.3f\n airq: %.4f\n hum: %.3f\n", data->temperature/ 100.0f, data->gas_resistance/ 1.0f, data->humidity/ 1000.0f);	

    if( (data->temperature/ 100.0f)>thmax_temp ||  (data->gas_resistance/ 1.0f)>thmax_air_quality || (data->humidity/ 1000.0f)>thmax_humidity ){
        buzzer_on();
    }else if( (data->temperature/ 100.0f)<thmin_temp ||  (data->gas_resistance/ 1.0f)<thmin_air_quality || (data->humidity/ 1000.0f)<thmin_humidity ){
        buzzer_on();
    }else{
        buzzer_off();
    }
}
