CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -fopenmp
OBJ = main.o mandelbrot.o pgm.o

mandelbrot: $(OBJ)
	$(CC) -o mandelbrot $(OBJ)

main.o: main.c mandelbrot.h pgm.h
	$(CC) -c main.c $(CFLAGS)

mandelbrot.o: mandelbrot.c mandelbrot.h
	$(CC) -c mandelbrot.c $(CFLAGS)

pgm.o: pgm.c pgm.h mandelbrot.h
	$(CC) -c pgm.c $(CFLAGS)

clean:
	rm -f mandelbrot $(OBJ)
