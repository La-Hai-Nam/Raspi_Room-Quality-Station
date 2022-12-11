#ifndef _INTERRUPT_H_
#define _INTERRPUT_H_

#include <pthread.h>
#include "OLED_1in5.h"
#include <poll.h>

int count = 0;
typedef void (*eventHandler)();

typedef struct {
    int fd;
    int gpio;
    eventHandler func;
} intVec;

intVec intData;

int attach_GPIO(int gpio, char *edge, eventHandler func);
void *wait_interrupt(void *arg);
void button_pressed();
void end_button_pressed();

#endif