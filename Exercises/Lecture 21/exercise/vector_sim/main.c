#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "vector_sim.h"

float * random_vector(int len)
{
  float * v = (float *)malloc(len * sizeof(float));
  for (int i = 0; i < len; i++) {
    v[i] = (float) rand() / RAND_MAX;
  }
  return v;
}

float * random_matrix(int nrows, int ncols)
{
  return random_vector(nrows * ncols);
}

double test_similarity(int nrows, int ncols, int (*f) (float *, float *, int, int))
{
  float * M = random_matrix(nrows, ncols);
  float * v = random_vector(ncols);
  double start = omp_get_wtime();
  volatile int idx = f(v, M, nrows, ncols);
  double end = omp_get_wtime();
  free(v);
  free(M);
  return (end - start) * 1000;
}

int main(int argc, char * argv[])
{
  const int nrows = 100000;
  const int ncols = 200;
  double t = test_similarity(nrows, ncols, most_similar);
  printf("Tempo richiesto (sequenziale): %fms\n", t);
  t = test_similarity(nrows, ncols, omp_most_similar);
  printf("Tempo richiesto (parallelo): %fms\n", t);
  return 0;
}
