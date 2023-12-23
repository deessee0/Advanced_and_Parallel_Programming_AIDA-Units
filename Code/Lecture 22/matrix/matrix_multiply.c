#include "matrix_multiply.h"

void simple_multiply(float * A, float * B, float * C, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
	C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void transposed_multiply(float * A, float * B, float * C, int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
	C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

void kernel(float * A, float * B, float * C, int x, int dx, int y, int dy, int z, int dz, int n)
{
  int mx = (x + dx > n) ? n : x + dx;
  int my = (y + dy > n) ? n : y + dy;
  int mz = (z + dz > n) ? n : z + dz;
  for (int i = x; i < mx; i++) {
    for (int j = y; j < my; j++) {
      for (int k = z; k < mz; k++) {
	C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

void blocked_multiply(float * A, float * B, float * C, int n)
{
  const int s1 = 16;
  const int s2 = 16;
  const int s3 = 16;

  for (int i = 0; i < n; i += s1) {
    for (int j = 0; j < n; j += s2) {
      for (int k = 0; k < n; k += s3) {
	kernel(A, B, C, i, s1, j, s2, k, s3, n);
      }
    }
  }
}

void omp_simple_multiply(float * A, float * B, float * C, int n)
{
#pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
	C[i * n + j] += A[i * n + k] * B[k * n + j];
      }
    }
  }
}

void omp_transposed_multiply(float * A, float * B, float * C, int n)
{
#pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
	C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

void omp_blocked_multiply(float * A, float * B, float * C, int n)
{
  const int s1 = 16;
  const int s2 = 16;
  const int s3 = 16;

#pragma omp parallel for collapse(2)
  for (int i = 0; i < n; i += s1) {
    for (int j = 0; j < n; j += s2) {
      for (int k = 0; k < n; k += s3) {
	kernel(A, B, C, i, s1, j, s2, k, s3, n);
      }
    }
  }
}
