CSRCS=$(wildcard *.c)

OBJ=$(patsubst %.c,%.o,$(CSRCS))

CC=gcc

all: blinky

%.o: %.c

	$(CC) -c -o $@ $<

blinky: blinky.o gpio_utils.o

	$(CC) -o $@ $^

clean:

	rm *.o

	rm blinky
