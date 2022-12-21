#include "interrupt.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "GUI_Paint.h"

intVec intData;
int count = 0;

int BUTTON_export(int pin){
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

int BUTTON_unexport(int pin){
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

int BUTTON_direction(int pin, char* direction){
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

int BUTTON_edge(int pin, char* edge){
    char path[DIRECTION_MAX];
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;
    snprintf(path, DIRECTION_MAX, "sys/class/gpio/gpio%d/edge", pin);
    fd = open(path, O_WRONLY);
    if(fd == -1){
        printf("\nfailed to open direction\n");
        return -3;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", *edge);
    write(fd ,buffer, bytes_written);
    close(fd);
    return 0;
}

int BUTTON_read(int pin){

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

int attach_GPIO(int gpio,char* direction, char *edge, eventHandler func) {
    BUTTON_export(gpio);
    //BUTTON_direction(gpio, direction);
    BUTTON_edge(gpio, edge);
    BUTTON_read(gpio);
    pthread_t intThread;
    if (pthread_create(&intThread, NULL, wait_interrupt, (void*) &intData)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    return 0;
}

void *wait_interrupt(void *arg) {
    
    while(1){
        if(BUTTON_read(BUTTON) == 1){
            DEV_Delay_ms(15);
            if(BUTTON_read(BUTTON) == 0){
                button_pressed();
                Paint_Clear(BLACK);
                DEV_Delay_ms(100);
            }
        }
    }
}

eventHandler button_pressed(){
	if(count > 3){
		count = 1;
	}else{
		count++;
	}
	return 0;
}

eventHandler end_button_pressed(){
	OLED_1in5_Clear();
    return 0;
}

int get_count() {
    printf("count:%d = ", count);
    return count;
}
