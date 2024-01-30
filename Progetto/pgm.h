#ifndef PGM_H
#define PGM_H
#include <stdio.h>
#include <complex.h>

struct Pgm
{
    FILE *file;
    unsigned char *map; // Buffer di memoria mappato
    int nrows;          // Numero di righe dell'immagine
    int ncols;          // Numero di colonne dell'immagine
    int maxIter;        // Numero massimo di iterazioni per il calcolo
    int offset;         // Offset per scrivere i dati nel buffer di memoria mappato
};

typedef struct Pgm *pgm;

void create_pgm(const char *path, pgm pgm); 
void write_mandelbrot_on_pgm(pgm pgm);
void close_pgm(pgm pgm);

#endif
