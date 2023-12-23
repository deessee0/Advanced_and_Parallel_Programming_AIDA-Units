CC = gcc-13
CFLAGS = -O3 -fopenmp -march=native -std=c17 -Wall -pedantic -fPIC
HEADERS = ${wildcard *.h}
OBJECTS = matrix.o matrix_multiply.o

all: libmatrix.so

libmatrix.so: ${OBJECTS} ${HEADERS}
	${CC} ${CFLAGS} -o $@ -shared ${OBJECTS}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $<

.PHONY: clean

clean:
	rm -f *.o
