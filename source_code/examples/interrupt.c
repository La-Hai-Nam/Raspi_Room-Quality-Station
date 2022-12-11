#include "interrupt.h"


int attach_GPIO(int gpio, char *edge, eventHandler func) {
    openGPIO(gpio, 0);
    setEdgeGPIO(gpio, edge);
    readGPIO(gpio);
    intData.fd = fd[gpio];
    intData.gpio=gpio;
    intData.func = func;
    pthread_t intThread;
    if (pthread_create(&intThread, NULL, waitInterrupt, (void*) &intData)) {
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
            readGPIO(gpio);
        }
    }
    pthread_exit(0);
}

void button_pressed(){
	if(count == 4){
		count = 0;
	}else{
		count++;
	}
}

void end_button_pressed(){
	OLED_1in5_Clear();
}