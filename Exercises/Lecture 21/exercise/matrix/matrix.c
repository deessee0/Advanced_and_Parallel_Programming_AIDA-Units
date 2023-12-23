#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "matrix.h"

float * make_random_matrix(int n)
{
  float * matrix = (float *)malloc(sizeof(float) * n * n);
  for (int i = 0; i < n * n; i++) {
    matrix[i] = (float) rand() / RAND_MAX;
  }
  return matrix;
}

float * make_zero_matrix(int n)
{
  float * matrix = (float *)malloc(sizeof(float) * n * n);
  for (int i = 0; i < n * n; i++) {
    matrix[i] = 0.0;
  }
  return matrix;
}

float * to_column_major(float * M, int n)
{
  float * MT = make_zero_matrix(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      MT[j * n + i] = M[i * n + j];
    }
  }
  return MT;
}

void print_matrix(float * M, int n, bool column_major)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (column_major) {
	printf("%2.3f ", M[j * n + i]);
      } else {
	printf("%2.3f ", M[i * n + j]);
      }
    }
    printf("\n");
  }
}
