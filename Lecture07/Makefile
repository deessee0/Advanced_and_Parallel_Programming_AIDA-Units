CC = gcc
CFLAGS = -O3 -Wall -pedantic -std=c17 -fno-if-conversion -fno-if-conversion2 -fno-tree-loop-if-convert
HEADERS = ${wildcards *.h}

all: main

main: main.o merge.o
	${CC} ${CFLAGS} -o $@ $^

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<


.PHONY: clean all

clean:
	rm -f *.o
