CC = gcc
CFLAGS = -O3 -fopenmp -march=native -std=c17 -Wall -pedantic
HEADERS = ${wildcard *.h}
OBJECTS = vector_sim.o main.o

all: main

main: ${OBJECTS} ${HEADERS}
	${CC} ${CFLAGS} -o $@ ${OBJECTS} -lm

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
