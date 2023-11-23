#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

  printf("Parallelizzazione ciclo esterno\n");
#pragma omp parallel for
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("Iterazione per i = %d e j = %d al thread %d\n", i, j, omp_get_thread_num());
    }
  }


  printf("\nParallelizzazione ciclo interno\n");
  for (int i = 0; i < 2; i++) {
#pragma omp parallel for
    for (int j = 0; j < 2; j++) {
      printf("Iterazione per i = %d e j = %d al thread %d\n", i, j, omp_get_thread_num());
    }
  }

    printf("\nParallelizzazione di tutti i cicli (non serve)\n");
#pragma omp parallel for
  for (int i = 0; i < 2; i++) {
#pragma omp parallel for
    for (int j = 0; j < 2; j++) {
      printf("Iterazione per i = %d e j = %d al thread %d\n", i, j, omp_get_thread_num());
    }
  }

  printf("\nParallelizzazione del ciclo intenro in una sezione parallela (sbagliato)\n");
#pragma omp parallel
  for (int i = 0; i < 2; i++) {
#pragma parallel for
    for (int j = 0; j < 2; j++) {
      printf("Iterazione per i = %d e j = %d al thread %d\n", i, j, omp_get_thread_num());
    }
  }

  printf("\nParallelizzazione manuale di entrambi i cicli \n");
#pragma omp parallel for
  for (int ij = 0; ij < 4; ij++) {
    int i = ij / 2;
    int j = ij % 2;
    printf("Iterazione per i = %d e j = %d al thread %d\n", i, j, omp_get_thread_num());
  }
  
  printf("\nParallelizzazione di entrambi i cicli con collapse\n");
#pragma omp parallel for collapse(2)
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      printf("Iterazione per i = %d e j = %d al thread %d\n", i, j, omp_get_thread_num());
    }
  }
  
  return 0;
}
