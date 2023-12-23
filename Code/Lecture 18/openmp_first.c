#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  printf("a\n");
#pragma omp parallel
  {
    printf("b\n");
    printf("c\n");
  }
  printf("d\n");
  return 0;
}
