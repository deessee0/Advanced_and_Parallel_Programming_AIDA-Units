CC = gcc
CFLAGS = -O3 -Wall -pedantic -std=c17 -fopenmp
HEADERS = ${wildcards *.h}

all: mergesort

mergesort: mergesort.o
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<


.PHONY: clean all

clean:
	rm -f *.o
