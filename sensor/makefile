CSRCS=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(CSRCS))
CC=gcc
CFLAGS=-Wall -c -o


all: bme_test

%.o: %.c
	$(CC) $(CFLAGS) $@ $<

bme_test: $(OBJ)
	$(CC) -Wall -o $@ $^


clean:
	rm *.o
	rm bme_test
