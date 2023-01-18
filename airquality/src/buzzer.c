//Includes
#include "interrupt.h"
#include "buzzer.h"
#include "bme_test.h"
//#include "gpio.h"



//Thresholds
//Values have to be defined!! The following are just examples
const float thmax_temp = 25.0, thmax_air_quality = 298.0, thmax_humidity = 40.0;                  //Maximum thresholds
const float thmin_temp = 5.0, thmin_air_quality = 1.0, thmin_humidity = 1.0;                  //Minimum thresholds


//Variables for functions
int buzzer_pin = 12;


//Buzzer functions
void buzzer_initialize(){
    GPIO_export(buzzer_pin);
    //GPIO_direction(buzzer_pin, "out");
	system("sudo echo \"out\" > /sys/class/gpio/gpio12/direction");
}

void buzzer_end(){
    GPIO_unexport(buzzer_pin);
}

void buzzer_on(){
    GPIO_value(buzzer_pin, 1);
}

void buzzer_off(){
    GPIO_value(buzzer_pin, 0);
}

void buzzer_toggle(){
    if(GPIO_read(buzzer_pin) == 0){
        GPIO_value(buzzer_pin, 1);
    }else{
        GPIO_value(buzzer_pin, 0);
    }
}

void set_buzzer_alarm(bmedata data){
	
	//printf("temp: %.3f\n airq: %.4f\n hum: %.3f\n", data.temperature, data.gas_resistance, data.humidity);	

    if( (data.temperature)>thmax_temp ||  (data.gas_resistance)>thmax_air_quality || (data.humidity)>thmax_humidity ){
        buzzer_on();
    }else if( (data.temperature)<thmin_temp ||  (data.gas_resistance)<thmin_air_quality || (data.humidity)<thmin_humidity ){
        buzzer_on();
    }else{
        buzzer_off();
    }
}

