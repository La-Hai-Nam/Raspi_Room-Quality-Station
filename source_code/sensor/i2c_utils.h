#ifndef I2C_UTILS_H
#define I2C_UTILS_H
#include <stdlib.h>
#include "bme280_defs.h"

#define I2C_DEVICE "/dev/i2c-1"
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
int8_t user_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
#endif

