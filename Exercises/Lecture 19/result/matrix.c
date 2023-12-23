#include <stdlib.h>

#include "matrix.h"

float * random_matrix(int n)
{
  float * m = (float *)malloc(n * n * sizeof(float));
  for (int i = 0; i < n*n; i++) {
    m[i] = (float) rand() / RAND_MAX;
  }
  // azzeramento della diagonale
  for (int i = 0; i < n; i++) {
    m[i * n + i] = 0;
  }
  return m;
}

float * zero_matrix(int n)
{
  float * m = (float *)malloc(n * n * sizeof(float));
  for (int i = 0; i < n*n; i++) {
    m[i] = 0;
  }
  return m;
}
