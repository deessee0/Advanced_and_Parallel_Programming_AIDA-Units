#include "pgm.h"
#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

void create_image(const char *path, int nrows, int ncols, int maxIter, int r)
{
    int fd = open(path, O_RDWR | O_CREAT, 0666);

    if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        exit(-1);
    }

    // Calcola la dimensione dell'immagine includendo l'intestazione PGM
    size_t img_size = nrows * ncols;
    size_t header_size = snprintf(NULL, 0, "P5\n%d %d\n255\n", ncols, nrows);
    size_t total_size = header_size + img_size;

    // Estendi la dimensione del file
    if (ftruncate(fd, total_size) == -1)
    {
        perror("Errore nel ridimensionamento del file");
        close(fd);
        exit(-1);
    }

    // Scrivi l'intestazione nel file
    char header[header_size + 1];
    sprintf(header, "P5\n%d %d\n255\n", ncols, nrows);
    // Modifica la condizione di verifica dopo la chiamata a write
    if (write(fd, header, header_size) < 0)
    {
        perror("Errore nella scrittura dell'intestazione");
        close(fd);
        exit(-1);
    }

    // Mappa il file in memoria
    unsigned char *map = mmap(0, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (map == MAP_FAILED)
    {
        perror("Errore in mmap");
        close(fd);
        exit(-1);
    }

    // Calcola e scrivi i dati dell'immagine nel buffer mappato
    unsigned char *img_data = map + header_size;
#pragma omp parallel for collapse(2)
    for (int row = 0; row < nrows; row++)
    {
        for (int col = 0; col < ncols; col++)
        {
            float re = -2 + (col * 3.0) / ncols;
            float im = -1 + (row * 2.0) / nrows;
            float complex c = re + im * I;

            int n = isMandelbrot(c, maxIter, r);
            unsigned char color;

            if (n == maxIter)
            {
                color = 255;
            }
            else
            {
                color = (unsigned char)(255 * log(n) / log(maxIter));
            }

            img_data[row * ncols + col] = color;
        }
    }

    // Rilascia la mappatura
    if (munmap(map, total_size) == -1)
    {
        perror("Errore nel rilascio di mmap");
    }

    close(fd);
}

