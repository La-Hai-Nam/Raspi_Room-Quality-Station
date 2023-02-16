#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <pthread.h>
#include "oled_1in5.h"

#define LOW 0
#define HIGH 1

#define IN "in"
#define OUT "out"

#define FALLING "falling"
#define RISING "rising"
#define BOTH "both"

#define BUTTON_DATA 5
#define BUTTON_ONOFF 6
#define GPIO25 25
#define GPIO27 27

#define BUFFER_MAX 3
#define DIRECTION_MAX 35
#define VALUE_MAX 30


typedef void (*eventHandler)();

typedef struct {
    int fd;
    int gpio;
    eventHandler func;
} intVec;


int attach_GPIO(int gpio_button, int gpio_onoff, char* direction, char *edge);
void *wait_interrupt(void *arg);
eventHandler button_pressed();
eventHandler end_button_pressed();

int GPIO_export(int pin);
int GPIO_unexport(int pin);
int GPIO_direction(int pin, char* direction);
int GPIO_edge(int pin, char* edge);
int GPIO_read(int pin);
int get_count();
void increment_count();
void onoff_button_pressed();
int get_count();
void change_count(int num);
void increment_count();
int get_do_once();
void increment_do_once();

#endif