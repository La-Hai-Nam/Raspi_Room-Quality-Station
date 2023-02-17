#ifndef SENSOR_BUZZER_H
#define SENSOR_BUZZER_H
#include "bme_test.h"           //Includes the struct type bmedata
//#include "bme680_defs.h"

void buzzer_initialize();
void buzzer_end();
void buzzer_on();
void buzzer_off();
void buzzer_toggle(); 
void set_buzzer_alarm(bmedata data);

#endif //SENSOR_BUZZER_H

