CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic
HEADERS = ${wildcard *.h}
OBJECTS = main.o linked_list.o unrolled_linked_list.o

all: main

main: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
