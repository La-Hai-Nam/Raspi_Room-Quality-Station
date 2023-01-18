#include <stdio.h>
#include <stdlib.h>

#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"
#include "bme_test.h"

/******************************************************************************
function:	Initialize bme680 sensor
Info:
******************************************************************************/
void bme_init(struct bme680_dev* sensor){

	int8_t rslt = sensor_init(sensor);	
	if(rslt != 0) printf("rslt: %d\n", rslt);
}

/******************************************************************************
function:	Gets captured data from sensor and returns struct bmedata which contains all captured data from sensor 
Info:
******************************************************************************/

bmedata bme_while(struct bme680_dev* sensor, struct bme680_field_data* data){
		bmedata s;
		int ms_delay = 2000;

		sensor_get_all_data(sensor, data);
		
		/* convert measurements */
		s.temperature = data->temperature / 100.0f;
		s.pressure = data->pressure / 100.0f;
		s.humidity = data->humidity / 1000.0f;
		s.gas_resistance = data->gas_resistance / 1.0f;

		return s;
}