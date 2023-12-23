#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#include "matrix.h"
#include "graph.h"


double test_shortcut(void (*f) (float *, float *, int), float * m, float * d, float n)
{
  const int repetitions = 5;
  double t = 0;
  for (int i = 0; i < repetitions; i++) {
    double start = omp_get_wtime();
    f(m, d, n);
    double end = omp_get_wtime();
    t += (end - start);
  }
  return 1000 * t / repetitions;
}

int main(int argc, char * argv[])
{
  const int n = 1000;
  float * m = zero_matrix(n);
  float * d = random_matrix(n);
  double t;
  t = test_shortcut(shortcut_std, m, d, n);
  printf("Tempo per shortcut standard: %f ms\n", t);
  t = test_shortcut(shortcut_trs, m, d, n);
  printf("Tempo per shortcut con trasposta: %f ms\n", t);
  t = test_shortcut(shortcut_omp, m, d, n);
  printf("Tempo per shortcut OpenMP: %f ms\n", t);
  t = test_shortcut(shortcut, m, d, n);
  printf("Tempo per shortcut: %f ms\n", t);
  return 0;
}
