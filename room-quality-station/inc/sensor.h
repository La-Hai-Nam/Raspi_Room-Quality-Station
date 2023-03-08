#ifndef SENSOR_H
#define SENSOR_H

#include "bme680_defs.h"


int8_t sensor_get_all_data(struct bme680_dev* sensor, struct bme680_field_data* data);
int8_t sensor_disable(struct bme680_dev* sensor, struct bme680_field_data* data);
int8_t sensor_init(struct bme680_dev* sensor);
int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len);
void user_delay_ms(uint32_t period);

#endif
