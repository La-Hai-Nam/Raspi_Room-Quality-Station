CSRCS=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(CSRCS))
CC=gcc
CFLAGS=-Wall -c -o


all: sens

%.o: %.c
	$(CC) $(CFLAGS) $@ $<

sens: $(OBJ)
	$(CC) -Wall -o $@ $^


clean:
	rm *.o
	rm sens

