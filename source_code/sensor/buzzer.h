#ifndef SENSOR_BUZZER_H
#define SENSOR_BUZZER_H

void buzzer_initialize();       //Export buzzer_pin and set direction
void buzzer_end();              //Unexport buzzer_pin
void buzzer_on();               //Let the buzzer making sounds
void buzzer_off();              //Let the buzzer be quiet
void buzzer_toggle();           //Toggle buzzer´s behavior
void buzzer_alarm_set();        //Let the buzzer making sounds when alarm

#endif //SENSOR_BUZZER_H
