CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic

all: main

main: main.o netpbm.o netpbm.h
	${CC} ${CFLAGS} main.o netpbm.o -o $@

%.o: %.c netpbm.h
	${CC} ${CFLAGS} -c $^

.PHONY: clean main

clean:
	rm -rf *.o
