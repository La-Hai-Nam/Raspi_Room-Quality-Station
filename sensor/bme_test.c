#include <stdio.h>
#include <stdlib.h>

#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"


int main(int argc, char *argv[] )
{

	int ms_delay = 1000;
	int n_measurements = 5;
	if(argc == 3) {
		ms_delay = atoi(argv[1]);
		n_measurements = atoi(argv[2]);
	}	

	/*first allocate sensor and data structs*/
	struct bme680_dev* sensor = (struct bme680_dev*)malloc(sizeof(struct bme680_dev));
	struct bme680_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));


	/*then initilize the sensor*/
	int8_t rslt = sensor_init(sensor);	
	if(rslt != 0) printf("rslt: %d\n", rslt);

	// measurements
	float temperature, pressure, humidity;
	int gas_resistance;
	

	for(int i = 0; i < n_measurements; i++) {
		
		user_delay_ms(ms_delay);
		/*get all the data from the sensor*/
		sensor_get_all_data(sensor, data);
		
		/* convert measurements */
		temperature = data->temperature / 100.0f;
		pressure = data->pressure / 100.0f;
		humidity = data->humidity / 1000.0f;
		gas_resistance = data->gas_resistance;
		
		/* print them */
		printf("T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", temperature, pressure, humidity);
		printf(", G: %d Ohms", gas_resistance);
		printf("\r\n");
	}	


	rslt = sensor_disable(sensor, data);
	
	return 0;
}
