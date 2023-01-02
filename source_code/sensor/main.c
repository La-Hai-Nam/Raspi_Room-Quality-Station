#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_MAX 100

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

int GPIO_value(int pin, int value){
    char path[DIRECTION_MAX];
    char buffer[BUFFER_MAX];
    ssize_t bytes_written;
    int fd;
    snprintf(path, DIRECTION_MAX, "sys/class/gpio/gpio%d/value", pin);
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

int sensordata_threshold;
int turn_off_buzzer;
int main(){
    GPIO_export(16);
    GPIO_direction(16,out);
    if(sensordata_threshold == 1 && turn_off_buzzer == 1){
        GPIO_value(1);
        turn_off_buzzer = 0;
    }else{
        GPIO_value(0);
    }

}
