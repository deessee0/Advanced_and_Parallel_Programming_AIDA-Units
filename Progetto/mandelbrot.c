#include <stdio.h>
#include <complex.h>

int isMandelbrot(float complex c, int M)
{
    float complex Zn = 0;

    for(int i=0; i<M; i++){  

        if (cabsf(Zn) >= 2.0){
            return i;
        }

        Zn = (Zn * Zn) + c;
    }

    return -1;
}