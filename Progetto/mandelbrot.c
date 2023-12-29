#include <stdio.h>
#include <complex.h>

int isMandelbrot(float complex c, float r, int M)
{
    float complex Zn = 0;

    for(int i=0; i<M; i++){
        
        Zn = (Zn * Zn) + c;

        if (cabsf(Zn) >= r){

            return i;
        }
    }

    return -1;
}