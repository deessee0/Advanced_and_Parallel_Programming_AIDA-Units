#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  printf("a\n");
#pragma omp parallel num_threads(3)
  {
    printf("b\n");
#pragma omp single
    {
      printf("c\n");
    }
    printf("d\n");
  }
  printf("e\n");
  return 0;
}
