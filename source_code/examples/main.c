#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include "test.h"
#include <string.h>

void  Handler(int signo)
{
    //System Exit
    printf("\r\nHandler:exit\r\n");
    Paint_Clear(BLACK);
    OLED_1in5_Clear();
    DEV_ModuleExit();

    exit(0);
}



int main(int argc, char *argv[])
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler);
    
    OLED_1in5_test();
	
	return 0;
	
}
