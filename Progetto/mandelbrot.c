#include <stdio.h>
#include <complex.h>

// Funzione per verificare se un punto complesso appartiene all'insieme di Mandelbrot
// - c: il punto complesso da verificare
// - M: il numero massimo di iterazioni per determinare l'appartenenza
// Restituisce:
// - il numero di iterazioni necessarie per uscire dall'insieme (se esce entro M iterazioni)
// - -1 se il punto sembra appartenere all'insieme (dopo M iterazioni)

int isMandelbrot(float complex c, int M)
{
    float complex Zn = 0; // Inizializza Zn a zero

    for (int i = 0; i < M; i++)
    {
        if (cabsf(Zn) >= 2.0)
        {
            return i; // Se la magnitudine di Zn supera 2, esce restituendo il numero di iterazioni
        }

        Zn = (Zn * Zn) + c; // Calcola il nuovo valore di Zn per la prossima iterazione
    }

    return -1; // Se il punto sembra appartenere all'insieme dopo M iterazioni, restituisce -1
}
