CC = gcc
CFLAGS = -Wall -Wextra -std=c17 -fopenmp -O3
OBJ = main.o mandelbrot.o pgm.o

.PHONY: clean run

mandelbrot: $(OBJ)
	$(CC) -o mandelbrot $(OBJ) $(CFLAGS) -lm

$(OBJ): mandelbrot.h pgm.h

clean:
	rm -f mandelbrot $(OBJ)

run: mandelbrot
	./mandelbrot default.pgm 1000 1000
