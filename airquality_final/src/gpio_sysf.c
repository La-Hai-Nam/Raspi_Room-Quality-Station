#include "gpio_sysf.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "GUI_Paint.h"
#include "OLED_1in5.h"
#include "RPI_sysfs_gpio.h"
#include <errno.h>

int count = 0;
int first_count = 1;
int do_once = 0;
int procfile_fd;

/******************************************************************************
function:	ALL sysfs functions to use GPIO_Pins 
Info:
******************************************************************************/

int gpio_export(int pin){
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

int gpio_unexport(int pin){
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

int gpio_direction(int pin, char* direction){
    char path[DIRECTION_MAX];
    //char buffer[BUFFER_MAX];
    // ssize_t bytes_written;

    int fd;
    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/direction", pin);

    fd = open(path, O_WRONLY);
    if(fd < 0){
        printf("\nfailed to open direction\n");
        return -3;
    }

    //bytes_written = snprintf(buffer, BUFFER_MAX, "%d", *direction);
    write(fd ,direction, sizeof(direction));
    close(fd);
    return 0;
}

int gpio_edge(int pin, char* edge){
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

int gpio_read(int pin){

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

int gpio_value(int pin, int value){

    char path[DIRECTION_MAX];
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;

    snprintf(path, DIRECTION_MAX, "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);

    if(fd == -1){
        printf("\nfailed to open value\n");
        return -3;
    }

    bytes_written = snprintf(buffer, BUFFER_MAX, "%d", value);
    write(fd ,buffer, bytes_written);
    close(fd);
    return 0;
}

// /******************************************************************************
// function:	Attach GPIO Pin to thread which runs simultanously to the code
// Info:
// ******************************************************************************/

// int attach_GPIO(int gpio_button, int gpio_onoff, char* direction, char *edge) {
//     gpio_export(gpio_button);
//     gpio_edge(gpio_button, edge);
//     gpio_read(gpio_button);

//     gpio_export(gpio_onoff);
//     gpio_edge(gpio_onoff, edge);
//     gpio_read(gpio_onoff);

//     pthread_t intThread;
//     if (pthread_create(&intThread, NULL, wait_interrupt, (void*) &intData)) {
//         fprintf(stderr, "Error creating thread\n");
//         return 1;
//     }
//     return 0;
// }
// /******************************************************************************
// function:	Check if GPIO value is changed with debounce and increment count in button_pressed()
// Info:
// ******************************************************************************/
// void *wait_interrupt(void *arg) {
    
//     while(1){
//         if(gpio_read(BUTTON_DATA) == 1){
//             DEV_Delay_ms(15);
//             if(gpio_read(BUTTON_DATA) == 0){
//                 button_pressed();
//             }
//         }

//         if(gpio_read(BUTTON_ONOFF) == 1){
//             DEV_Delay_ms(15);
//             if(gpio_read(BUTTON_ONOFF) == 0){
//                 onoff_button_pressed();
//             }
//         } 
//     }
// }
// /******************************************************************************
// function:	adjusts the variable count to display different states on the display
// Info:
// ******************************************************************************/
// eventHandler button_pressed(){
// 	if(count == 4 ){
//         first_count = 1;
// 		count = 1;
//         do_once = 0;
// 	}else if(count >= 0 && count <=3){
//         first_count++;
// 		count++;
//         do_once = 0;
// 	}else{
//         count = first_count;
//         do_once = 0;
//     }
//     return 1;
// }

// void onoff_button_pressed(){
//     count = 5;
// }
// /******************************************************************************
// function:	global variable sharing functions that are mainly used in OLED_1in5_test.c to change the shown measurement
// Info:
// ******************************************************************************/

// void open_procfile() {
// 	procfile_fd = open("/proc/mydev", O_RDWR | O_NONBLOCK);
// 	if(procfile_fd < 0) {
// 		printf("in interrupt.c open_procfile() error opening proc file\n");
// 	}	
// }


// int get_count() {
	
// 	char buffer[100];
// 	lseek(procfile_fd, 0, SEEK_SET);
// 	int bytes_read = read(procfile_fd, buffer, 5);

// 	printf("%s:  %d: \n", buffer, bytes_read);

// 	return atoi(buffer);
// }

// void change_count(int num) {
//     //count = num;

// 	char buffer[100];
// 	int len = sprintf(buffer, "%d", num);
	
// 	lseek(procfile_fd, 0, SEEK_SET);
// 	if(write(procfile_fd, buffer, len) != len) {
// 		printf("in interrupt.c change_count() error writing to proc file\n");
// 	}
	
// 	printf("count changed\n");
// }

// void increment_count(){
//     count++;
// }

// int get_do_once(){
//     return do_once;
// }

// void increment_do_once(){
//     do_once++;
// }
