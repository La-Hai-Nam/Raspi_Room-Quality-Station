//Includes
#include "buzzer.h"
#include "gpio.h"


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

void buzzer_alarm_set(int measure_values[3], int thresholds_max[3], int thresholds_min[3]){
    for(int i=0; i<3; i++){
        if(measure_values[i]>thresholds_max || measure_values[i]<thresholds_min){
            buzzer_on();
        }else{
            buzzer_off();
        }
    }
}
