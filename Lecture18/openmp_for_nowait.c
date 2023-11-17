#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int sum = 0;
#pragma omp parallel
  {
#pragma omp for nowait
    for (int i = 0; i < 10; i++) {
      printf("%d\n", i);
    }
    printf("Fuori dal ciclo\n");
  }
  return 0;
}
