#include <errno.h>
#include <stdio.h>
#include "gpio_utils.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <bcm2835.h>


int gpio_init(char* gpio_num , char* in_out) {

	char* export = "/sys/class/gpio/export";
	char direction[255];

	strcpy(direction, "/sys/class/gpio/gpio");
	strcat(direction, gpio_num);
	strcat(direction, "/direction");

	
	int fd_export = open(export, O_WRONLY);

	if(fd_export < 0) {
		printf("%d \n", errno);
		return -1;
	}

	printf("%s\n", export);
	int bytes_written = write(fd_export, gpio_num, strlen(gpio_num));
	if(bytes_written != strlen(gpio_num)) {
		printf("%d\n", errno);
		return -2;
	}
	

	
	int fd_direction = open(direction, O_WRONLY);	
	if(fd_direction < 0) return -3;
	bytes_written = write(fd_direction, in_out, strlen(in_out));
	if(bytes_written != strlen(in_out)) return -4;


	return 0;
}






int gpio_free(char* gpio_num) {
	char* unexport_path = "/sys/class/gpio/unexport";


	int fd_unexport = open(unexport_path, O_WRONLY);
	if(fd_unexport < 0) return -1;

	if(write(fd_unexport, gpio_num, strlen(gpio_num)) != strlen(gpio_num)) return -2;

	return 0;
}





int gpio_set(char* gpio_num, char* state) {

	char value_path[255];

	strcpy(value_path, "/sys/class/gpio/gpio");
	strcat(value_path, gpio_num);
	strcat(value_path, "/value");

	int fd_value_path = open(value_path, O_WRONLY);

	int	bytes_written = write(fd_value_path, state, strlen(state));
	if(bytes_written != strlen(state)) return -1;             	 

	return 0;
}
