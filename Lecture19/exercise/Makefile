CC = gcc
CFLAGS = -O3 -Wall -std=c17 -pedantic -fopenmp
HEADERS = ${wildcards *.h}
OBJECTS = main.o matrix.o graph.o

main: all

main: ${HEADERS} ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o main

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< 

.PHONY: all clean

clean:
	rm *.o
