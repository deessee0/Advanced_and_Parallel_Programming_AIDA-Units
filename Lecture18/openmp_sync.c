#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int sum = 0;
#pragma omp parallel
  {
    int n_thread = omp_get_thread_num();
#pragma omp critical
    {
      sum += n_thread;
    }
  }
  printf("La somma dei valori è %d\n", sum);
  return 0;
}
