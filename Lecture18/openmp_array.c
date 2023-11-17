#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  const int n = 1<<20;
  int * v = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    v[i] = rand() % 100;
  }
  int sum = 0;
#pragma omp parallel
  {
    int n_thread = omp_get_thread_num();
    int slice_size = n / omp_get_num_threads();
    int start = n_thread * slice_size;
    int end = (n_thread + 1) * slice_size;
    int partial_sum = 0;
    for (int i = start; i < end; i++) {
      partial_sum += v[i];
    }
    printf("Somma partiale terminata (thread %d)\n", n_thread);
#pragma omp critical
    {
      sum += partial_sum;
    }
  }
  printf("La somma dei valori è %d\n", sum);
  return 0;
}
