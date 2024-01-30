#include "pgm.h"
#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

// Funzione per creare un file PGM
// - path: percorso del file PGM da creare
// - nrows: numero di righe dell'immagine
// - ncols: numero di colonne dell'immagine
// - maxIter: numero massimo di iterazioni per il calcolo
void create_pgm(const char *path, pgm pgm)
{
    // Controllo delle dimensioni dell'immagine
    if ((pgm->nrows <= 0 || pgm->ncols <= 0) || (pgm->ncols != 1.5 * pgm->nrows))
    {
        fprintf(stderr, "Errore: Dimensioni della matrice non valide.\n");
        exit(1);
    }

    // Apertura (o creazione se non esiste) del file in modalità scrittura
    pgm->file = fopen(path, "w+");
    if (pgm->file == NULL)
    {
        perror("Errore nell'apertura del file");
        exit(1);
    }

    // Ottiene il file descriptor associato al file aperto
    int fd = fileno(pgm->file);
    if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        exit(1);
    }

    // Calcola la dimensione dell'immagine
    int img_size = pgm->nrows * pgm->ncols;

    //scrive l'intestazione e salva l'offset
    pgm->offset = fprintf(pgm->file, "P5\n%d %d\n255\n", pgm->ncols, pgm->nrows);
    if (pgm->offset < 0)
    {
        perror("Errore nella scrittura dell'intestazione PGM");
        fclose(pgm->file);
        exit(1);
    }

    // Modifica la dimensione del file per accogliere i dati dell'immagine
    if (ftruncate(fd, pgm->offset + img_size * sizeof(unsigned char)) == -1)
    {
        perror("Errore in ftruncate");
        fclose(pgm->file);
        exit(1);
    }

    // Mappa il file in memoria
    pgm->map = (unsigned char *)mmap(0, pgm->offset + img_size * sizeof(unsigned char), PROT_WRITE, MAP_SHARED, fd, 0);
    if (pgm->map == MAP_FAILED)
    {
        perror("Errore nella mappatura del file in memoria");
        fclose(pgm->file);
        exit(1);
    }

}

// Funzione per scrivere i dati del frattale di Mandelbrot nel file PGM
// - map: buffer di memoria mappato
// - nrows: numero di righe dell'immagine
// - ncols: numero di colonne dell'immagine
// - maxIter: numero massimo di iterazioni per il calcolo
// - offset: offset per scrivere i dati nel buffer di memoria mappato
void write_mandelbrot_on_pgm(pgm pgm)
{
// Parallelizzazione del ciclo per calcolare il frattale in modo efficiente
#pragma omp parallel for collapse(2)
    for (int row = 0; row < pgm->nrows; row++)
    {
        for (int col = 0; col < pgm->ncols; col++)
        {
            // Calcola la parte reale e immaginaria per il punto corrente
            float re = -2.0 + col * 3.0 / (pgm->ncols - 1);
            float im = -1.0 + row * 2.0 / (pgm->nrows - 1);
            // Crea un numero complesso
            float complex c = re + im * I;

            int n = isMandelbrot(c, pgm->maxIter);

            unsigned char color;

            if (n == -1)
            {
                // Bianco per i punti all'interno dell'insieme di Mandelbrot
                color = 255;
            }
            else
            {
                // Scala di grigi basata sul numero di iterazioni
                color = (unsigned char)(255 * log(n) / log(pgm->maxIter));
            }
            // Scrive il colore calcolato nel buffer di memoria mappato
            pgm->map[(row * pgm->ncols) + pgm->offset + col] = color;
        }
    }
}

void close_pgm(pgm pgm)
{
    // Libera la mappatura del file dalla memoria
    if (munmap(pgm->map, pgm->offset + pgm->nrows * pgm->ncols * sizeof(unsigned char)) == -1)
    {
        perror("Errore nel liberare la mappatura del file");
        fclose(pgm->file);
        exit(1);
    }

    // Chiude il file
    if (fclose(pgm->file) != 0)
    {
        perror("Errore nella chiusura del file");
        exit(1);
    }
}