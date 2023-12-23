#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  int sum = 0;
#pragma omp parallel
  {
    printf("Questo lo eseguono tutti\n");
#pragma omp for
    for (int i = 0; i < 10; i++) {
      printf("%d\n", i);
    }
  }

#pragma omp parallel
  for (int i = 0; i < 10; i++) {
    printf("Ooops %d\n", i);
  }
  return 0;
}
