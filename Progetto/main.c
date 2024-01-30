#include "pgm.h"
#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Uso: %s <nome file> <numero di iterazioni> <numero di righe>\n", argv[0]);
        return 1;
    }

    struct Pgm *pgm = malloc(sizeof(struct Pgm)); 
    if (pgm == NULL)
    {
        perror("Errore di allocazione memoria per Pgm");
        return 1;
    }

    const char *path = argv[1];
    pgm->maxIter = atoi(argv[2]);
    pgm->nrows = atoi(argv[3]);
    pgm->ncols = (int)(1.5 * pgm->nrows);

    create_pgm(path, pgm); 
    write_mandelbrot_on_pgm(pgm);
    close_pgm(pgm);

    free(pgm); 
    
    return 0;
}
