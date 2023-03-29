/**
* @file sensor.c
* @brief This file provides an API for the bme680 sensor.
* @author Maximilian Lausch, HTW-Berlin s0578304
* @bug Currently there are no known bugs
*/

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bme680.h"


/* I2c device filediscriptor */
static int sensor_i2c_fd;
/* buffer for that stores what is send over I2C in one Transaction (between one Start and Stop) */
static int8_t wbuffer[254];


int8_t sensor_get_all_data(struct bme680_dev* sensor, struct bme680_field_data* data);
int8_t sensor_disable(struct bme680_dev* sensor, struct bme680_field_data* data);
int8_t sensor_init(struct bme680_dev* sensor);

static int8_t i2c_init();
static int8_t i2c_close();
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);

void user_delay_ms(uint32_t period);


/* @brief Userspace I2C initilization
*  
*  Opens up the i2c device file.
*  Sets the i2c slave address to the sensors address.
* 
*  @return The status (Success / Failure) code.
*/
static int8_t i2c_init() {
	/* open i2c device file */
	sensor_i2c_fd = open("/dev/i2c-1", O_RDWR);
	if (sensor_i2c_fd < 0) {
		printf("in i2c_init -> cant open i2c device, Errno: %d\n", errno);
		return 1;
	}

	/* change i2c device parameters, 
	   specify i2c addess to communicate to */
	if (ioctl(sensor_i2c_fd, I2C_SLAVE, BME680_I2C_ADDR_SECONDARY) < 0) {
		printf("in i2c_init -> ioctl failed, Errno: %d\n", errno);
		return 2;
	}

	return 0;
}

/* @brief Disables the userspace I2C Comunication
*  
*  Closes the i2c device file
* 
*  @return The status (Success / Failure) code.
*/
static int8_t i2c_close() {
	/* close i2c device file, shut down communication */
	if(close(sensor_i2c_fd) != 0) {
		printf("in i2c_close, failed to close i2c device, Errno: %d\n", errno);
		return 1;
	}
	return 0;	
}


/* @brief Halts execution of the programm.
*
*  @param period The time to halt / sleep in milliseconds 
*  @return Void
*/
void user_delay_ms(uint32_t period) {
    usleep(period * 1000);
}

/* @brief URaspberry-Pi Userspace I2C reading.
*
*  This function is used by the bme680 driver (bme680.c)
*  for reading from the sensor.
* 
*  @param dev_id Is used to store the I2C address of the device.
*  @param reg_addr The register that is to be read.
*  @param *reg_data The buffer where the read data is written to.
*  @param len The number of bytes to be read.
* 
*  @return Success / Failure code
*/
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
	
	/* send the address of the register we want to read from */	
 	if (write(sensor_i2c_fd, &reg_addr, 1) != 1) {
		printf("in user_i2c_read -> failed to write address, Errno: %d\n", errno);
		rslt = 1;
	}

	/* read the received data */ 
	if (read(sensor_i2c_fd, reg_data, len) != len) {
		printf("in user_i2c_read -> failed to data, Errno: %d\n", errno);
		rslt = 2;
	}

    return rslt;
}


/* @brief Raspberry-Pi userspace I2C writing
*
*  This function is used by the bme680 driver (bme680.c)
*  for writing to the sensor.
*
*  @param dev_id Is used to store the I2C address of the device.
*  @param reg_addr The register where the data is written to.
*  @param *red_data The data that is send.
*  @param len The number of bytes to send. 
*
*  @return Status / Failure code.
*/
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

	/* put the address and the data in one I2c-"Querry" */
    wbuffer[0]=reg_addr;
	
    for (int i=1; i<len+1; i++) {
       wbuffer[i] = reg_data[i-1];
	}

	/* send the data */
    if (write(sensor_i2c_fd, wbuffer, len+1) != len+1) {
		printf("in user_i2c_write -> failed to write data, Errno: %d\n", errno);
		rslt = 1;
	}

    return rslt;
}


/* @brief Initilizes and configures the sensor.
*
*  @param *sensor The sensor instance.
*                 It holds all Information about the Sensor.
*
*  @return Success / Failure code.
*/
int8_t sensor_init(struct bme680_dev* sensor) {

	int8_t rslt = BME680_OK;
	/* initilize the i2c communication / device */
	rslt = i2c_init();
	if(rslt != 0) printf("rslt: %d\n", rslt);	

	
	/* Set device related I2C settings */
	sensor->dev_id = BME680_I2C_ADDR_SECONDARY;
	sensor->intf = BME680_I2C_INTF;
	sensor->read = user_i2c_read;
	sensor->write = user_i2c_write;
	sensor->delay_ms = user_delay_ms;

	/* initilize sensor */
	rslt = bme680_init(sensor);
	if(rslt != 0) printf("rslt: %d\n", rslt);	

    uint8_t set_required_settings;

	/* Set the temperature, pressure and humidity settings */
	sensor->tph_sett.os_hum = BME680_OS_2X;
	sensor->tph_sett.os_pres = BME680_OS_4X;
	sensor->tph_sett.os_temp = BME680_OS_8X;
	sensor->tph_sett.filter = BME680_FILTER_SIZE_3;

	/* Set the remaining gas sensor settings and link the heating profile */
	sensor->gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
	/* Create a ramp heat waveform */
	sensor->gas_sett.heatr_temp = 320; /* degree Celsius */
	sensor->gas_sett.heatr_dur = 150; /* milliseconds */

	/* Select the power mode */
	/* Must be set before writing the sensor configuration */
	sensor->power_mode = BME680_FORCED_MODE; 

	/* Set the required sensor settings needed */
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL 
		| BME680_GAS_SENSOR_SEL;

	/* Set the desired sensor configuration */
	rslt = bme680_set_sensor_settings(set_required_settings,sensor);
	if(rslt != 0) printf("in sensor_confi -> set settings error, rslt: %d\n", rslt);	

	/* Set the power mode */
	rslt = bme680_set_sensor_mode(sensor);
	if(rslt != 0) printf("in sensor_conifg -> set mode error, rslt: %d\n", rslt);	

	return rslt;	
}


/* @brief Disable / free the sensor.
*
*  This function frees all ressources related to a sensor instance.
*
*  @param *sensor The sensor instance that is to be disabled / freed. 
*  @param *data The data field related to the sensor instance that is to be freed.
*
*  @return Success / Failure code.
*/
int8_t sensor_disable(struct bme680_dev* sensor, struct bme680_field_data* data) {
	
	/* close the i2c device file */
	if(i2c_close() != 0) {
		printf("in sensor_disable -> cant close device file, Errno: %d\n", errno);
		return 1;
	}	
	
	/* free the sensor */
	if(sensor) free(sensor);
	/* free the data field */
	if(data) free(data);
	
	return 0;
}


/* @brief Gets every measurement from the sensor.
*
*  @param *sensor The sensor instance that we want the measurements from
*  @param *data This is where the received data gets stored.
* 
*  @return Success / Failure code.
*/
int8_t sensor_get_all_data(struct bme680_dev* sensor, struct bme680_field_data* data) {
	
	/* the time it takes for one measurement to complete */
	uint16_t meas_period;

	/* fetch the measurement period from the sensor instance */
	bme680_get_profile_dur(&meas_period, sensor);

	/* Delay till the measurement is ready */
	user_delay_ms(meas_period); 	
	int8_t rslt = BME680_OK;
	
	do {
		/* read every measurement form the sensor */
		rslt = bme680_get_sensor_data(data, sensor);
		if(rslt != 0) printf("rslt: %d\n", rslt);	
		
		/* Trigger the next measurement */
		rslt = bme680_set_sensor_mode(sensor); 
		if(rslt != 0) printf("rslt: %d\n", rslt);	
		
		/* Wait for the measurement to complete */
		user_delay_ms(meas_period); 			
	}
	/* measure until there is are valid measurements */
	while(!(data->status & BME680_GASM_VALID_MSK) || !(data->status & BME680_HEAT_STAB_MSK)); 
	
	return rslt;	
}
