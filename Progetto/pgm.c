#include "pgm.h"
#include "mandelbrot.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

// Funzione per scrivere i dati del frattale di Mandelbrot nel file PGM
// - map: buffer di memoria mappato
// - nrows: numero di righe dell'immagine
// - ncols: numero di colonne dell'immagine
// - maxIter: numero massimo di iterazioni per il calcolo
// - offset: offset per scrivere i dati nel buffer di memoria mappato
void write_mandelbrot_on_pgm(char *map, int nrows, int ncols, int maxIter, int offset)
{
// Parallelizzazione del ciclo per calcolare il frattale in modo efficiente
#pragma omp parallel for collapse(2)
    for (int row = 0; row < nrows; row++)
    {
        for (int col = 0; col < ncols; col++)
        {
            // Calcola la parte reale e immaginaria per il punto corrente
            float re = -2.0 + col * 3.0 / (ncols - 1);
            float im = -1.0 + row * 2.0 / (nrows - 1);
            // Crea un numero complesso
            float complex c = re + im * I; 

            int n = isMandelbrot(c, maxIter);

            char color;

            if (n == -1)
            {
                // Bianco per i punti all'interno dell'insieme di Mandelbrot
                color = 255; 
            }
            else
            {
                // Scala di grigi basata sul numero di iterazioni
                color = (char)(255 * log(n) / log(maxIter)); 
            }
            // Scrive il colore calcolato nel buffer di memoria mappato
            map[(row * ncols) + offset + col] = color;
        }
    }
}

// Funzione per creare un file PGM
// - path: percorso del file PGM da creare
// - nrows: numero di righe dell'immagine
// - ncols: numero di colonne dell'immagine
// - maxIter: numero massimo di iterazioni per il calcolo
void create_pgm(const char *path, int nrows, int ncols, int maxIter)
{
    // Controllo delle dimensioni dell'immagine
    if ((nrows <= 0 || ncols <= 0) || (ncols != 1.5 * nrows))
    {
        fprintf(stderr, "Errore: Dimensioni della matrice non valide.\n");
        exit(1);
    }

    // Apertura (o creazione se non esiste) del file in modalità scrittura
    FILE *file = fopen(path, "w+");
    if (file == NULL)
    {
        perror("Errore nell'apertura del file");
        exit(1);
    }

    // Ottiene il file descriptor associato al file aperto
    int fd = fileno(file);
    if (fd == -1)
    {
        perror("Errore nell'apertura del file");
        exit(1);
    }

    // Calcola la dimensione dell'immagine
    int img_size = nrows * ncols;

    //scrive l'intestazione e salva l'offset
    int offset = fprintf(file, "P5\n%d %d\n255\n", ncols, nrows);
    if (offset < 0)
    {
        perror("Errore nella scrittura dell'intestazione PGM");
        fclose(file);
        exit(1);
    }

    // Modifica la dimensione del file per accogliere i dati dell'immagine
    if (ftruncate(fd, offset + img_size * sizeof(char)) == -1)
    {
        perror("Errore in ftruncate");
        fclose(file);
        exit(1);
    }

    // Mappa il file in memoria
    char *map = (char *)mmap(0, offset + img_size * sizeof(char), PROT_WRITE, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED)
    {
        perror("Errore nella mappatura del file in memoria");
        fclose(file);
        exit(1);
    }

    // Chiama la funzione per scrivere i dati del frattale di Mandelbrot nel file PGM
    write_mandelbrot_on_pgm(map, nrows, ncols, maxIter, offset);

    // Libera la mappatura del file dalla memoria
    if (munmap(map, offset + nrows * ncols * sizeof(char)) == -1)
    {
        perror("Errore nel liberare la mappatura del file");
        fclose(file);
        exit(1);
    }

    // Chiude il file
    if (fclose(file) != 0)
    {
        perror("Errore nella chiusura del file");
        exit(1);
    }
}