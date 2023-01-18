#ifndef GPIO_UTILS_H

#define GPIO_UTILS_H

int gpio_init(char* gpio_num , char* direction);

int gpio_free(char* gpio_num);

int gpio_set(char* gpio_num, char* state);

#endif
