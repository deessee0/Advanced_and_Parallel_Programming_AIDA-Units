#include "pgm.h"
#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

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
    int offset = fprintf(sile, "P5\n%d %d\n255\n", ncols, nrows);

    if (ftruncate(fd, offset + img_size * sizeof(char)) == -1)
    {
        perror("Errore in ftruncate");
        // Gestisci l'errore come necessario
    }

    // Mappa il file in memoria
    char *map = (char *)mmap(0, offset + img_size * sizeof(char), PROT_WRITE, MAP_SHARED, fd, 0);

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
            float re = -2.0 + col * 3.0 / (ncols-1);
            float im = -1.0 + row * 2.0 / (nrows-1);
            float complex c = re + im * I;

            int n = isMandelbrot(c, maxIter);

            char color;

            if (n == -1)
            {
                color = 255; // Bianco per i punti all'interno dell'insieme di Mandelbrot
            }
            else
            {
                color = (char)(255 * log(n) / log(maxIter)); // Scala di grigi per altri punti
            }
            
            map[(row * ncols) + offset + col] = color;
        }
    }

    munmap(map, offset + nrows * ncols * sizeof(char));
    fclose(sile);
}