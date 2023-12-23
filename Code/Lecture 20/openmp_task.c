#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void f(int x)
{
  int y = 0;
  for (int i = 0; i < 1<<x; i++) {
    y++;
  }
  printf("Il thread %d sta eseguendo f(%d) con risultato %d\n", omp_get_thread_num(), x, y);
}

int main(int argc, char *argv[])
{
#pragma omp parallel
#pragma omp single
  {
#pragma omp task
    f(3);
#pragma omp task
    f(13);
#pragma omp task
    f(20);
#pragma omp task
    f(11);
#pragma omp task
    f(18);
#pragma omp task
    f(16);
  }
  return 0;
}
