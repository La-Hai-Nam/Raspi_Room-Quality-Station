#include "interrupt.h"  //Includes the gpio functions
#include "buzzer.h"
#include "bme_test.h"




const float thmax_temp = 25.0, thmax_air_quality = 298.0, thmax_humidity = 40.0;//Maximum thresholds
const float thmin_temp = 5.0, thmin_air_quality = 1.0, thmin_humidity = 1.0;//Minimum thresholds

int buzzer_pin = 12;    //This is the no. of the Pi pin the buzzer is attached to




/******************************************************************************
function:   Initialize the buzzer pin
Info:       Gives a system call to the Pi to activate the buzzer pin.
            It also should set the direction to an output with 
            "GPIO_direction()". The mentioned function is faulty.
            The buzzer nevertheless does its job, so we uncommented it.
******************************************************************************/

void buzzer_initialize(){
    GPIO_export(buzzer_pin);
    //GPIO_direction(buzzer_pin, "out");
	system("sudo echo \"out\" > /sys/class/gpio/gpio12/direction");
}


/******************************************************************************
function:	Give the buzzer pin free
Info:       Deactivates the buzzer pin to be free for other needs.
******************************************************************************/

void buzzer_end(){
    GPIO_unexport(buzzer_pin);
}


/******************************************************************************
function:   Let the buzzer making sounds
Info:       It writes an high signal to the buzzer pin.
******************************************************************************/

void buzzer_on(){
    GPIO_value(buzzer_pin, 1);
}


/******************************************************************************
function:	Makes sure that the buzzer is quiet.
Info:       It writes a low signal to the buzzer pin.
******************************************************************************/

void buzzer_off(){
    GPIO_value(buzzer_pin, 0);
}


/******************************************************************************
function:	Toggles the buzzers behavior
Info:       It writes the opposite signal from the last one to the buzzer pin.
******************************************************************************/

void buzzer_toggle(){
    if(GPIO_read(buzzer_pin) == 0){
        GPIO_value(buzzer_pin, 1);
    }else{
        GPIO_value(buzzer_pin, 0);
    }
}


/******************************************************************************
function:   Let the buzzer making sounds only when an alarm situation happens
Parameter:  bmedata is a struct type and it contains measure values: 
            temperature, humidity and gas_resistance.
Info:       It writes an high signal to the buzzer pin if a threshold is 
            exceeded or fallen below. It writes a low signal to the buzzer pin
            if the thresholds are not exceeded or fallen below.
******************************************************************************/

void set_buzzer_alarm(bmedata data){
	//printf("temp: %.3f\n airq: %.4f\n hum: %.3f\n", data.temperature, data.gas_resistance, data.humidity);	

    if( (data.temperature)>thmax_temp ||  
        (data.gas_resistance)>thmax_air_quality || 
        (data.humidity)>thmax_humidity ){
        buzzer_on();
    }else if(   (data.temperature)<thmin_temp || 
                (data.gas_resistance)<thmin_air_quality ||
                (data.humidity)<thmin_humidity ){
        buzzer_on();
    }else{
        buzzer_off();
    }
}


