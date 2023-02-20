/* @file bme_test.c
*  @brief This file showcases how the sensor.c API is to be used.
*  @author Maximilian Lausch (s0578304), HTW-Berlin.
*  @bug No known bugs.
*/

#include <stdio.h>
#include <stdlib.h>

#include "bme680.h"
#include "sensor.h"
#include "bme680_defs.h"



/* @breif Main function / enrtypoint
*	
*  How to use: 
*		First argument -> Delay in ms between meassurements.  
* 		Second argument -> Number of total meassurements to make.
*  Default Delay is 1000 ms.
*  Default number of meassurements are 5.
*
*  @params argc The number of given arguments.
*  @params *argv[] The list of given arguments.
* 
*  @return should not return.
*/
int main(int argc, char *argv[] ) {
	
	/* Default values */	
	int ms_delay = 1000;
	int n_measurements = 5;
	/* parse arguemts */
	if(argc == 3) {
		ms_delay = atoi(argv[1]);
		n_measurements = atoi(argv[2]);
	}	
	
	
	/* Step 1: allocate space for sensor and data field*/
	struct bme680_dev* sensor = (struct bme680_dev*)malloc(sizeof(struct bme680_dev));
	struct bme680_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));


	/*Step 2: then initilize the sensor, by using the sensor_init() API function*/
	int8_t rslt = sensor_init(sensor);	
	if(rslt != 0) printf("rslt: %d\n", rslt);

	/* the meassurements */
	float temperature, pressure, humidity;
	int gas_resistance;
	

	for(int i = 0; i < n_measurements; i++) {
		
		/* Delay between meassurements */	
		user_delay_ms(ms_delay);
		
		/*Step 3: get all the data from the sensor*/
		sensor_get_all_data(sensor, data);
		
		/*Step 4: convert measurements */
		temperature = data->temperature / 100.0f;
		pressure = data->pressure / 100.0f;
		humidity = data->humidity / 1000.0f;
		gas_resistance = data->gas_resistance;
		
		/* print them */
		printf("T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", temperature, pressure, humidity);
		printf(", G: %d Ohms", gas_resistance);
		printf("\r\n");
	}	

	/* Step 5: free / diable the sensor and data */	
	rslt = sensor_disable(sensor, data);
	
	return 0;
}
