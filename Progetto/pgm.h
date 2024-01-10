#ifndef PGM_H
#define PGM_H
#include <stdio.h>
#include <complex.h>

void create_image(const char *path, int nrows, int ncols, int maxIter);
void chiudiImmagine(FILE *sile, int ncols, int nrows, int *map);
#endif

