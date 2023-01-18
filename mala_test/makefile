CSRCS=$(wildcard *.c)
OBJ=$(patsubst %.c,%.o,$(CSRCS))
CC=gcc
CFLAGS=-Wall -c -o


all: kmtest

%.o: %.c
	$(CC) $(CFLAGS) $@ $<

bme_test: $(OBJ)
	$(CC) -Wall -o $@ $^


clean:
	rm *.o
	rm kmtest
