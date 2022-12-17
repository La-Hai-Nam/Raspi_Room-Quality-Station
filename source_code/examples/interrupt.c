#include "interrupt.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <poll.h>

intVec intData;

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
<<<<<<< HEAD
    snprintf(path, DIRECTION_MAX, "sys/class/gpio/gpio%d/direction", pin);printf("\n%d" , path);
    fd = open(path, O_WRONLY);
    if(fd == -1){
        printf("\nfailed to open direction\n");
=======
    snprintf(path, DIRECTION_MAX, "sys/class/gpio/gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if(fd == -1){
        printf("failed to open direction");
>>>>>>> 998a8e9188309535fb6ff35217277ef3ac4c3da6
        return -3;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", *direction);
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

int attach_GPIO(int gpio, char *edge, eventHandler func) {
    BUTTON_export(gpio);
    BUTTON_direction(gpio, edge);
    BUTTON_read(gpio);
    int fd[32];
    intData.fd = fd[gpio];
    intData.gpio = gpio;
    intData.func = func;
    pthread_t intThread;
    if (pthread_create(&intThread, NULL, wait_interrupt, (void*) &intData)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    return 0;
}

void *wait_interrupt(void *arg) {

    intVec *intData = (intVec*) arg;
    int gpio = intData->gpio;
    struct pollfd fdset[1];
    fdset[0].fd = intData->fd;
    fdset[0].events = POLLPRI;
    fdset[0].revents = 0;
    for (;;) {
        int rc = poll(fdset, 1, -1);
        if (fdset[0].revents & POLLPRI) {
            intData->func();
            lseek(fdset[0].fd, 0, SEEK_SET);
            BUTTON_read(gpio);
        }
    }
    pthread_exit(0);
}

// eventHandler button_pressed(int count){
// 	if(count == 4){
// 		count = 0;
// 	}else{
// 		count++;
// 	}
// }

eventHandler end_button_pressed(){
	OLED_1in5_Clear();
    return 0;
}
