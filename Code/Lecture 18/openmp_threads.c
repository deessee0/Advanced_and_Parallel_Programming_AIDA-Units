#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
#pragma omp parallel
  {
    int n_threads = omp_get_thread_num();
    printf("Saluti dal thread %d\n", n_threads);
  }
  return 0;
}
