#include "pgm.h"
#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void chiudiImmagine(FILE *sile, int ncols, int nrows, int *map)
{

    munmap(map, nrows * ncols * sizeof(int));
    fseek(sile, 0, SEEK_SET);
    fprintf(sile, "P5\n%d %d\n255\n", ncols, nrows);
    fclose(sile);
}

void create_image(const char *path, int nrows, int ncols, int maxIter)
{
    FILE *sile = fopen(path, "w+");
    int fd = fileno(sile);

    if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        exit(-1);
    }

    // Calcola la dimensione dell'immagine
    int img_size = nrows * ncols;
    if (ftruncate(fd, img_size * sizeof(int)) == -1)
    {
        perror("Errore in ftruncate");
        // Gestisci l'errore come necessario
    }

    // Mappa il file in memoria
    int *map = (int *)mmap(0, img_size *sizeof(int), PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED)
    {
        perror("Errore in mmap");
        close(fd);
        exit(-1);
    }

#pragma omp parallel for collapse(2)
    for (int row = 0; row < nrows; row++)
    {
        for (int col = 0; col < ncols; col++)
        {
            float re = -2.0 + col * 3.0 / ncols;
            float im = -1.0 + row * 2.0 / nrows;
            float complex c = re + im * I;

            int n = isMandelbrot(c, maxIter);

            int color;

            if (n == -1)
            {
                color = 255; // Bianco per i punti all'interno dell'insieme di Mandelbrot
            }
            else
            {
                color = (int)(255 * log(n) / log(maxIter)); // Scala di grigi per altri punti
            }

            map[row * ncols + col] = color;
        }
    }

    chiudiImmagine(sile, ncols, nrows, map);
}