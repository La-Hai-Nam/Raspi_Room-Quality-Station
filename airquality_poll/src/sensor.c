#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bme680.h"


//I2c device discriptor
static int sensor_i2c_fd;
// write buffer
static int8_t wbuffer[254];


int8_t sensor_get_all_data(struct bme680_dev* sensor, struct bme680_field_data* data);
int8_t sensor_disable(struct bme680_dev* sensor, struct bme680_field_data* data);
int8_t sensor_init(struct bme680_dev* sensor);

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
void user_delay_ms(uint32_t period);

static int8_t i2c_init();
static int8_t i2c_close();




static int8_t i2c_init() {
	sensor_i2c_fd = open("/dev/i2c-1", O_RDWR);
	if (sensor_i2c_fd < 0) {
		printf("in i2c_init -> cant open i2c device, Errno: %d\n", errno);
		return 1;
	}

	if (ioctl(sensor_i2c_fd, I2C_SLAVE, BME680_I2C_ADDR_SECONDARY) < 0) {
		printf("in i2c_init -> ioctl failed, Errno: %d\n", errno);
		return 2;
	}

	return 0;
}

// close the I2c device
static int8_t i2c_close() {
	if(close(sensor_i2c_fd) != 0) {
		printf("in i2c_close, failed to close i2c device, Errno: %d\n", errno);
		return 1;
	}
	return 0;	
}


void user_delay_ms(uint32_t period) {
    usleep(period * 1000);
}


int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

 	if (write(sensor_i2c_fd, &reg_addr, 1) != 1) {
		printf("in user_i2c_read -> failed to write address, Errno: %d\n", errno);
		rslt = 1;
	}
	if (read(sensor_i2c_fd, reg_data, len) != len) {
		printf("in user_i2c_read -> failed to data, Errno: %d\n", errno);
		rslt = 2;
	}

    return rslt;
}

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len) {
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */


    wbuffer[0]=reg_addr;
	
    for (int i=1; i<len+1; i++) {
       wbuffer[i] = reg_data[i-1];
	}

    if (write(sensor_i2c_fd, wbuffer, len+1) != len+1) {
		printf("in user_i2c_write -> failed to write data, Errno: %d\n", errno);
		rslt = 1;
	}

    return rslt;
}


int8_t sensor_init(struct bme680_dev* sensor) {
	// init i2c device
	int8_t rslt = BME680_OK;

	rslt = i2c_init();
	if(rslt != 0) printf("rslt: %d\n", rslt);	

	
    // init device
	sensor->dev_id = BME680_I2C_ADDR_SECONDARY;
	sensor->intf = BME680_I2C_INTF;
	sensor->read = user_i2c_read;
	sensor->write = user_i2c_write;
	sensor->delay_ms = user_delay_ms;

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
	/* Create a ramp heat waveform in 3 steps */
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


int8_t sensor_disable(struct bme680_dev* sensor, struct bme680_field_data* data) {

	if(i2c_close() != 0) {
		printf("in sensor_disable -> cant close device file, Errno: %d\n", errno);
		return 1;
	}	

	if(sensor) free(sensor);
	if(data) free(data);
	
	return 0;
}


int8_t sensor_get_all_data(struct bme680_dev* sensor, struct bme680_field_data* data) {

	uint16_t meas_period;
	bme680_get_profile_dur(&meas_period, sensor);
	user_delay_ms(meas_period); /* Delay till the measurement is ready */
	int8_t rslt = BME680_OK;
	
	do {
		// get data
		rslt = bme680_get_sensor_data(data, sensor);
		if(rslt != 0) printf("rslt: %d\n", rslt);	
	
		rslt = bme680_set_sensor_mode(sensor); /* Trigger a measurement */
		if(rslt != 0) printf("rslt: %d\n", rslt);	
	
		user_delay_ms(meas_period); /* Wait for the measurement to complete */			
	}
	while(!(data->status & BME680_GASM_VALID_MSK) || !(data->status & BME680_HEAT_STAB_MSK)); 
	
	return rslt;	
}
