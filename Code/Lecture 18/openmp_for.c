#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int sum = 0;
#pragma omp parallel for
  for (int i = 0; i < 10; i++) {
    printf("%d\n", i);
  }
  return 0;
}
