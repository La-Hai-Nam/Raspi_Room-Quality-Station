#include "i2c_utils.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
int8_t user_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);


int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
	// open i/o i2c bus for writing and reading
    int fd = open(I2C_DEVICE, O_RDWR);
    if(fd < 0) {
        printf("Error, failed to open %s in user_i2c_write, Errno: %d", I2C_DEVICE, errno);
        close(fd);
        return 1;
    }

	// set slave address
    if(ioctl(fd, I2C_SLAVE, BME280_I2C_ADDR_PRIM ) < 0) {
        printf("Error, failed to set slave addr,  Errno: %d", errno);
        close(fd);
        return 2;
    }
 
	// set register
	if(write(fd, &reg_addr, sizeof(reg_addr)) != sizeof(reg_addr)) {
		printf("Error, faild to write on i2c bus, Errno: %d", errno);
		close(fd);
        return 3;
	}

    // read data form i2c bus
    if(read(fd, reg_data, len * sizeof(uint8_t)) != len * sizeof(uint8_t)) {
		printf("Error, faild to read from i2c bus, Errno: %d", errno);
		close(fd);
        return 4;
	}

    // ---------------------------------------------------------------------------------------
	// open i/o i2c bus for writing
    // int fd = open(I2C_DEVICE, O_WRONLY);
    // if(fd < 0) {
    //     printf("Error, failed to open %s in user_i2c_write, Errno: %d", I2C_DEVICE, errno);
    //     close(fd);
    //     return 1;
    // }

	// // set slave address
    // if(ioctl(fd, I2C_SLAVE, dev_id) < 0) {
    //     printf("Error, failed to set slave addr,  Errno: %d", errno);
    //     close(fd);
    //     return 2;
    // }
 
	// // set register
	// if(write(fd, &reg_addr, sizeof(reg_addr)) != sizeof(reg_addr)) {
	// 	printf("Error, faild to write on i2c bus, Errno: %d", errno);
	// 	close(fd);
    //     return 3;
	// }

    
    // // open i/o i2c bus for reading
    // int fd2 = open(I2C_DEVICE, O_RDONLY);
    // if(fd < 0) {
    //     printf("Error, failed to open %s in user_i2c_write, Errno: %d", I2C_DEVICE, errno);
    //     close(fd);
    //     return 1;
    // }

    // // read data form i2c bus
    // if(read(fd, reg_data, len * sizeof(uint8_t)) != len * sizeof(uint8_t)) {
	// 	printf("Error, faild to read from i2c bus, Errno: %d", errno);
	// 	close(fd);
    //     return 4;
	// }
    // close(fd2);

    close(fd);
    return 0;
}

int8_t user_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
	// open i/o i2c bus for writing
    int fd = open(I2C_DEVICE, O_WRONLY);
    if(fd < 0) {
        printf("Error, failed to open %s in user_i2c_write, Errno: %d", I2C_DEVICE, errno);
        close(fd);
        return 1;
    }

	// set slave address
    if(ioctl(fd, I2C_SLAVE, BME280_I2C_ADDR_PRIM) < 0) {
        printf("Error, failed to set slave addr,  Errno: %d", errno);
        close(fd);
        return 2;
    }

    // set register
	if(write(fd, &reg_addr, sizeof(reg_addr)) != sizeof(reg_addr)) {
		printf("Error, faild to write on i2c bus, Errno: %d", errno);
		close(fd);
        return 3;
	}

    
	//write data to bus 
	if(write(fd, reg_data, len * sizeof(reg_data[0])) != (len * sizeof(reg_data[0]))) {
		printf("Error, faild to write on i2c bus, Errno: %d", errno);
		close(fd);
        return 3;
	}


    close(fd);
    return 0;
}

