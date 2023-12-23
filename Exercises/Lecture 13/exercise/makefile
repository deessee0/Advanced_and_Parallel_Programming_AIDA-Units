CC = gcc
CFLAGS = -O3 -march=native -std=c17 -Wall -pedantic
HEADERS = ${wildcard *.h}
OBJECTS = matrix.o main.o matrix_multiply.o

all: main

main: ${OBJECTS} ${HEADERS}
	${CC} ${CFLAGS} -o $@ ${OBJECTS}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
