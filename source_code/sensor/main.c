#include "buzzer.h"

#include <stdio.h>
#include <stdlib.h>

#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"


int main(){
    //To be added to initializing part of the code
    buzzer_initialize();

    //The interesting part for buzzer
    sensor_get_all_data(sensor, data);
    set_buzzer_alarm(data);

    //To be added to the end part of the code, when disabling all
    buzzer_end();
}



