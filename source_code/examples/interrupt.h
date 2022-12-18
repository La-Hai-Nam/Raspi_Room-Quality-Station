#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

#include <pthread.h>
#include "OLED_1in5.h"

#define LOW 0
#define HIGH 1

#define IN "in"
#define OUT "out"

#define FALLING "falling"
#define RISING "rising"
#define BOTH "both"

#define BUTTON 5
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


int attach_GPIO(int gpio, char* direction, char *edge, eventHandler func);
void *wait_interrupt(void *arg);
eventHandler button_pressed();
eventHandler end_button_pressed();

int BUTTON_export(int pin);
int BUTTON_unexport(int pin);
int BUTTON_direction(int pin, char* direction);
int BUTTON_edge(int pin, char* edge);
int BUTTON_read(int pin);
int get_count();

#endif