DIR_Config   = ./lib/Config
DIR_OLED     = ./lib/OLED
DIR_FONTS    = ./lib/Fonts
DIR_GUI      = ./lib/GUI
DIR_Examples = ./examples
DIR_BIN      = ./bin
DIR_src		 = ./src
DIR_inc 	 = ./inc

OBJ_C = $(wildcard ${DIR_inc}/*.c ${DIR_src}/*.c)
OBJ_O = $(patsubst %.c,${DIR_BIN}/%.o,$(notdir ${OBJ_C}))

TARGET = main

#USELIB = USE_BCM2835_LIB
#USELIB = USE_WIRINGPI_LIB
USELIB = USE_DEV_LIB
DEBUG = -D $(USELIB)
ifeq ($(USELIB), USE_BCM2835_LIB)
    LIB = -lbcm2835 -lm 
else ifeq ($(USELIB), USE_WIRINGPI_LIB)
    LIB = -lwiringPi -lm 
else ifeq ($(USELIB), USE_DEV_LIB)
    LIB = -lm 
endif


CC = gcc
MSG = -g -O0 -Wall
CFLAGS += $(MSG) $(DEBUG)

${TARGET}:${OBJ_O}
	$(CC) -pthread $(CFLAGS) $(OBJ_O) -o $@ $(LIB)
    
${DIR_BIN}/%.o:$(DIR_src)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@ -I $(DIR_inc)
    
${DIR_BIN}/%.o:$(DIR_inc)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@ 
    
clean :
	rm $(DIR_BIN)/*.* 
	rm $(TARGET) 
