#include "gpio_utils.h"

#include <stdio.h>

int main () {

	char* gpio_num = "17";
	char* direction = "out";
	char* value = "1";


	int status = gpio_init(gpio_num, direction);
	printf("init status: %d \n", status);

	status = gpio_set(gpio_num, "0");
	printf("set status: %d \n", status);

	status = gpio_free(gpio_num);
	printf("free status: %d \n", status);



	return 0;
}
