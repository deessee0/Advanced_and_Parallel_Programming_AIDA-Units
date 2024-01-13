#ifndef PGM_H
#define PGM_H
#include <stdio.h>
#include <complex.h>

void create_pgm(const char *path, int nrows, int ncols, int maxIter);
void write_mandelbrot_on_pgm(char *map, int nrows, int ncols, int maxIter, int offset);

#endif

