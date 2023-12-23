#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

#include "matrix.h"
#include "matrix_multiply.h"

double test_multiply(void (* multiply)(float *, float *, float *, int))
{
  int n = 1000;
  float * A = make_random_matrix(n);
  float * B = make_random_matrix(n);
  float * C = make_zero_matrix(n);
  double start = omp_get_wtime();
  multiply(A, B, C, n);
  double end = omp_get_wtime();
  double ms = (end - start) * 1000;
  free(A);
  free(B);
  free(C);
  return ms;
}

int main (int argc, char * argv[])
{
  printf("Time for standard multiplication: %f ms\n", test_multiply(simple_multiply));
  printf("Time for transposed multiplication: %f ms\n", test_multiply(transposed_multiply));
  printf("Time for blocked multiplication: %f ms\n", test_multiply(blocked_multiply));
  printf("\nParallel versions\n\n");
  printf("Time for standard multiplication: %f ms\n", test_multiply(omp_simple_multiply));
  printf("Time for transposed multiplication: %f ms\n", test_multiply(omp_transposed_multiply));
  printf("Time for blocked multiplication: %f ms\n", test_multiply(omp_blocked_multiply));
  return 0;
}
