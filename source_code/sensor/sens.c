#include "bme280.h"
#include "bme280_defs.h"
#include "i2c_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void print_sensor_data(struct bme280_data *comp_data);

void user_delay_ms(uint32_t period)
{
    usleep(period * 1000);
}

void  user_delay_us(uint32_t period, void* intf_ptr) {
	usleep(period);
}

struct bme280_dev* sensor_init() {
	struct bme280_dev* dev = (struct bme280_dev*)malloc(sizeof(struct bme280_dev));

	int8_t rslt = BME280_OK;
	uint8_t dev_addr = BME280_I2C_ADDR_PRIM;
	
	dev->intf_ptr = &dev_addr;
	dev->intf = BME280_I2C_INTF;
	dev->read = user_i2c_read;
	dev->write = user_i2c_write;
	dev->delay_us = user_delay_us;
	
	rslt = bme280_init(dev);
	
	return dev;
}


int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    int8_t rslt;
    uint8_t settings_sel;
	uint32_t req_delay;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    rslt = bme280_set_sensor_settings(settings_sel, dev);
	
	/*Calculate the minimum delay required between consecutive measurement based upon the sensor enabled
     *  and the oversampling configuration. */
    req_delay = bme280_cal_meas_delay(&dev->settings);

    printf("Temperature, Pressure, Humidity\r\n");
    /* Continuously stream sensor data */
    while (1) {
        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        /* Wait for the measurement to complete and print data @25Hz */
        dev->delay_us(req_delay, dev->intf_ptr);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        print_sensor_data(&comp_data);
    }
    return rslt;
}

void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
        printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#endif
}


int main() {

//    struct bme280_field_data* data = (struct bme680_field_data*)malloc(sizeof(struct bme680_field_data));
    struct bme280_dev* dev = sensor_init();
	stream_sensor_data_forced_mode(dev);

	
	free(dev);
    return 0;
}

