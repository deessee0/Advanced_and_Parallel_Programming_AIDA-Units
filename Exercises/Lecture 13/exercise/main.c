#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "matrix.h"
#include "matrix_multiply.h"

#define NN 10
#define MM 10
#define PP 10

float test_multiply(void (* multiply)(float *, float *, float *, int))
{
  int n = 1000;
  float * A = make_random_matrix(n);
  float * B = make_random_matrix(n);
  float * C = make_zero_matrix(n);
  clock_t start = clock();
  multiply(A, B, C, n);
  clock_t end = clock();
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  free(A);
  free(B);
  free(C);
  return ms;
}

int main (int argc, char * argv[])
{
  const int n = 8;
  float * A = make_random_matrix(n);
  float * B = make_random_matrix(n);
  float * BT = to_column_major(B, n);
  float * C1 = make_zero_matrix(n);
  float * C2 = make_zero_matrix(n);
  float * C3 = make_zero_matrix(n);
  simple_multiply(A, B, C1, n);
  print_matrix(C1, n, false);
  printf("\n");
  /* transposed_multiply(A, BT, C2, n); */
  /* print_matrix(C2, n, false); */
  /* printf("\n"); */
  /* blocked_multiply(A, BT, C3, n); */
  /* print_matrix(C3, n, false); */
  /* printf("\n"); */
  printf("Time for standard multiplication: %f ms\n", test_multiply(simple_multiply));
  /* printf("Time for transposed multiplication: %f ms\n", test_multiply(transposed_multiply)); */
  /* printf("Time for blocked multiplication: %f ms\n", test_multiply(blocked_multiply)); */
  return 0;
}
