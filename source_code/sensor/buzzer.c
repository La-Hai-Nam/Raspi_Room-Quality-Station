//Includes
#include "buzzer.h"
#include "gpio.h"


//Thresholds
//Values have to be defined!! The following are just examples
const int thmax_temp = 6, thmax_air_quality = 4, thmax_humidity = 5;                  //Maximum thresholds
const int thmin_temp = 2, thmin_air_quality = 1, thmin_humidity = 1;                  //Minimum thresholds


//Variables for functions
int buzzer_pin = 16;


//Buzzer functions
void buzzer_initialize(){
    GPIO_export(buzzer_pin);
    GPIO_direction(buzzer_pin, "out");
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

void set_buzzer_alarm(struct bme680_field_data* data){
    if( (data->temperature/100.0f)>thmax_temp ||  (data->gas_resistance/100.0f)>thmax_air_quality || (data->humidity/100.0f)>thmin_humidity ){
        buzzer_on();
    }else if( (data->temperature/100.0f)<thmin_temp ||  (data->gas_resistance/100.0f)<thmin_air_quality || (data->humidity/100.0f)<thmin_humidity ){
        buzzer_on();
    }else{
        buzzer_off();
    }
}

