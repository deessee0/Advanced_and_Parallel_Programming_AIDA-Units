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
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      for (int k = 0; k < n; k++)
      {
  C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

void kernel(float * A, float * B, float * C, int x, int dx, int y, int dy, int z, int dz, int n)
{
  /*
   * Moltiplicazione di blocchi. Si prende il blocco A[x:x+dx, z:z+dz] e si moltiplica con B[z:z+dz, y+dy]
   * sommando il risultato nella posizioni C[x:x+dx, y:y+dy].
   * Prestare attenzione che x+dx, y+dy e z+dz potenzialmente potrebbero essere maggiori di n,
   * quindi serve limitarsi a n come dimensione.
   */

  for (int i = x; i < x+dx; i++)
  {
    for (int j = y; j < y+dy; j ++)
    {
      for (int k = z; k < z+dz; k ++)
      {
         C[i * n + j] += A[i * n + k] * B[j * n + k];
      }
    }
  }
}

      void blocked_multiply(float *A, float *B, float *C, int n)
      {
  const int s1 = 16; // Provare inizialmente con 2 o 4
  const int s2 = 16;
  const int s3 = 16;

  for (int i = 0; i < n; i+=s1)
  {
    for (int j = 0; j < n; j+=s2)
    {
      for (int k = 0; k < n; k+=s3)
      {

        int dx = (i + s1 > n) ? (n - i) : s1;
        int dy = (j + s2 > n) ? (n - j) : s2;
        int dz = (k + s3 > n) ? (n - k) : s3;


        kernel(A,B,C,i,dx,j,dy,k,dz,n);
      }
    }
  }
}
