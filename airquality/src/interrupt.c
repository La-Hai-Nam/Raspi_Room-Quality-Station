#include "interrupt.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "GUI_Paint.h"
#include "OLED_1in5.h"

intVec intData;
int count = 0;
int first_count = 1;
int do_once = 0;

/******************************************************************************
function:	ALL sysfs functions to use GPIO_Pins 
Info:
******************************************************************************/

int GPIO_export(int pin){
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if(fd == -1){
        printf("failed to open export");
        return -1;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd ,buffer, bytes_written);
    close(fd);
    return 0;
}

int GPIO_unexport(int pin){
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if(fd == -1){
        printf("failed to open unexport");
        return -2;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", pin);
    write(fd ,buffer, bytes_written);
    close(fd);
    return 0;
}

int GPIO_direction(int pin, char* direction){
    char path[DIRECTION_MAX];
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;
    snprintf(path, DIRECTION_MAX, "sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if(fd == -1){
        printf("\nfailed to open direction\n");
        return -3;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", *direction);
    write(fd ,buffer, bytes_written);
    close(fd);
    return 0;
}

int GPIO_edge(int pin, char* edge){
    char path[DIRECTION_MAX];
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;
    snprintf(path, DIRECTION_MAX, "sys/class/gpio/gpio%d/edge", pin);
    fd = open(path, O_WRONLY);
    // if(fd == -1){
    //     printf("\nfailed to open direction\n");
    //     return -3;
    // }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", *edge);
    write(fd ,buffer, bytes_written);
    close(fd);
    return 0;
}

int GPIO_read(int pin){

	char path[VALUE_MAX];
	char value_str[3];
	int fd;

	snprintf(path, VALUE_MAX, "/sys/class/gpio/gpio%d/value", pin);
	fd = open(path, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Failed to open gpio value for reading!\n");
		return(-4);
	}

	if (read(fd, value_str, 3) == -1) {
		fprintf(stderr, "Failed to read value!\n");
		return(-5);
	}

	close(fd);

	return(atoi(value_str));
}

/******************************************************************************
function:	Attach GPIO Pin to thread which runs simultanously to the code
Info:
******************************************************************************/

int attach_GPIO(int gpio_button, int gpio_onoff, char* direction, char *edge) {
    GPIO_export(gpio_button);
    GPIO_edge(gpio_button, edge);
    GPIO_read(gpio_button);

    GPIO_export(gpio_onoff);
    GPIO_edge(gpio_onoff, edge);
    GPIO_read(gpio_onoff);

    pthread_t intThread;
    if (pthread_create(&intThread, NULL, wait_interrupt, (void*) &intData)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    return 0;
}
/******************************************************************************
function:	Check if GPIO value is changed with debounce and increment count in button_pressed()
Info:
******************************************************************************/
void *wait_interrupt(void *arg) {
    
    while(1){
        if(GPIO_read(BUTTON_DATA) == 1){
            DEV_Delay_ms(15);
            if(GPIO_read(BUTTON_DATA) == 0){
                button_pressed();
            }
        }

        if(GPIO_read(BUTTON_ONOFF) == 1){
            DEV_Delay_ms(15);
            if(GPIO_read(BUTTON_ONOFF) == 0){
                onoff_button_pressed();
            }
        } 
    }
}
/******************************************************************************
function:	adjusts the variable count to display different states on the display
Info:
******************************************************************************/
eventHandler button_pressed(){
	if(count == 4 ){
        first_count = 1;
		count = 1;
        do_once = 0;
	}else if(count >= 0 && count <=3){
        first_count++;
		count++;
        do_once = 0;
	}else{
        count = first_count;
        do_once = 0;
    }
}
/******************************************************************************
function:	global variable sharing functions that are mainly used in OLED_1in5_test.c
Info:
******************************************************************************/
void onoff_button_pressed(){
    count = 5;
}

int get_count() {
    return count;
}

void change_count(int num) {
    count = num;
}

void increment_count(){
    count++;
}

int get_do_once(){
    return do_once;
}

void increment_do_once(){
    do_once++;
}