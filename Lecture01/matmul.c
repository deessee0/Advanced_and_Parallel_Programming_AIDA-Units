#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef float ** matrix;

matrix make_empty_matrix(int n, int m)
{
  matrix M = (float **) malloc(n * sizeof(float *));
  for (int i = 0; i < n; i++) {
    M[i] = (float *) malloc(m * sizeof(float));
    for (int j = 0; j < m; j++) {
      M[i][j] = 0;
    }
  }
  return M;
}

matrix make_random_matrix(int n, int m)
{
  matrix M = (float **) malloc(n * sizeof(float *));
  for (int i = 0; i < n; i++) {
    M[i] = (float *) malloc(m * sizeof(float));
    for (int j = 0; j < m; j++) {
      M[i][j] = rand()/RAND_MAX;
    }
  }
  return M;
}

void matmul(matrix A, matrix B, matrix C, int n, int m, int p)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < p; k++) {
	C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

int main(int argc, char * argv[])
{
  int n = 512;
  int m = 512;
  int p = 512;
  matrix A = make_random_matrix(n, p);
  matrix B = make_random_matrix(p, m);
  matrix C = make_random_matrix(n, m);
  clock_t start = clock();
  matmul(A, B, C, n, m, p);
  clock_t end = clock();
  float seconds = (float) (end - start) / CLOCKS_PER_SEC;
  printf("Time required %f\n", seconds);
  return 0;
}
