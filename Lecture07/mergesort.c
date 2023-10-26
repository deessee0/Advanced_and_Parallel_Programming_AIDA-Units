#include "merge.h"
#include <stdlib.h>





void merge(int *v1, int n1, int *v2, int n2, int *results)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while ((i < n1) && (j < n2))
    {
        if (v1[i] < v2[j])
        {
            results[k] = v1[i];
            i++;
            k++;
        }
        else
        {
            results[k] = v2[j];
            j++;
            k++;
        }
    }

    if (i < n1)
    {
        for (i; i < n1; i++)
        {
            results[k] = v1[i];
            k++;
        }
    }
    else if (j < n2)
    {
        for (j; j < n2; j++)
        {
            results[k] = v2[j];
            k++;
        }
    }
}

void merge_branchless(int *v1, int n1, int *v2, int n2, int *results)
{
    volatile int i = 0;
    volatile int j = 0;
    volatile int k = 0;

    while ((i < n1) && (j < n2))
    {
        int q = v1[i] < v2[j];

        results[k] = q * v1[i] + (1 - q) * v2[j];
        i = i + q;
        j = j + (1 - q);
        k++;
    }
    if (i < n1)
    {
        for (i; i < n1; i++)
        {
            results[k] = v1[i];
            k++;
        }
    }
    else if (j < n2)
    {
        for (j; j < n2; j++)
        {
            results[k] = v2[j];
            k++;
        }
    }
}

merge_sort(int *v, int len, void (*m)(int *, int, int *, int, int *)){

    int size;
    int l;

    for(size = 1; size < len; size = 2*size){
        
    }
    
}

    int main(int argc, char *argv[])
{

    return 0;
}
