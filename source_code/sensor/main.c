#include "buzzer.h"


//Measure values
//Function to get array of (0: temp, 1: air_quality, 2: humidity), see declaration below main
int* set_measure_values();


//Thresholds
//Values have to be defined!! The following are just examples
const int thmax_temp = 6, thmax_air_quality = 4, thmax_humidity = 5;                  //Maximum thresholds
const int thmin_temp = 2, thmin_air_quality = 1, thmin_humidity = 1;                  //Minimum thresholds
const int thresholds_max[3] = {thmax_temp,thmax_air_quality,thmax_humidity};
const int thresholds_min[3] = {thmin_temp,thmin_air_quality,thmin_humidity};




//Function called main here, but maybe the interrupt-part in the project?
int main(){
    buzzer_initialize();
    buzzer_alarm_set(set_measure_values(), thresholds_max, thresholds_min);     //Let the buzzer making sounds when alarm
    buzzer_end();                                                               //Unexport the buzzer_pin is needed???
}




//Function declarations
int* set_measure_values(){
    int measure_values[3]
    //read() is just a filler for a function reading a specific value
    measure_values[0] = read(temp);
    measure_values[1] = read(air_quality);
    measure_values[2] = read(humidity);
    return measure_values;
}