#ifndef SENSOR_BUZZER_H
#define SENSOR_BUZZER_H

#include "bme680_defs.h"

void buzzer_initialize();       //Export buzzer_pin and set direction
void buzzer_end();              //Unexport buzzer_pin
void buzzer_on();               //Let the buzzer making sounds
void buzzer_off();              //Let the buzzer be quiet
void buzzer_toggle();           //Toggle buzzer´s behavior
void set_buzzer_alarm(struct bme680_field_data* data);        //Let the buzzer making sounds when alarm

#endif //SENSOR_BUZZER_H
