DIR_Config   = ./lib/Config
DIR_oled     = ./lib/oled
DIR_FONTS    = ./lib/Fonts
DIR_GUI      = ./lib/GUI
DIR_Examples = ./examples
DIR_BIN      = ./bin

OBJ_C = $(wildcard ${DIR_oled}/*.c ${DIR_Config}/*.c ${DIR_GUI}/*.c ${DIR_Examples}/*.c ${DIR_FONTS}/*.c)
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
    
${DIR_BIN}/%.o:$(DIR_Examples)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@ -I $(DIR_Config) -I $(DIR_GUI) -I $(DIR_oled)
    
${DIR_BIN}/%.o:$(DIR_oled)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@ -I $(DIR_Config)
    
${DIR_BIN}/%.o:$(DIR_FONTS)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@
    
${DIR_BIN}/%.o:$(DIR_GUI)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@ -I $(DIR_Config)  -I $(DIR_oled) -I $(DIR_Examples)

${DIR_BIN}/%.o:$(DIR_Config)/%.c
	$(CC) -pthread $(CFLAGS) -c  $< -o $@ $(LIB)
	
clean :
	rm $(DIR_BIN)/*.* 
	rm $(TARGET) 
