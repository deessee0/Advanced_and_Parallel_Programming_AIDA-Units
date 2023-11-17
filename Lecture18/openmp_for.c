#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int sum = 0;
#pragma omp parallel for
  for (int i = 0; i < 10; i++) {
    int id = omp_get_thread_num();
    printf("posizione %d gestita da thread %d\n", i, id);
  }
  return 0;
}
