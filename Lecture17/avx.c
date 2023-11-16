#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <immintrin.h>

float * make_array(int n)
{
  float * v = (float *)malloc(n * sizeof(float));
  for (int i = 0; i < n; i++) {
    v[i] = (float) rand() / RAND_MAX;
  }
  return v;
}

int main(int argc, char * argv[])
{
  const int n = 1<<20;
  float * a = make_array(n);
  float * b = make_array(n);
  float * c = make_array(n);

  clock_t start = clock();
  for (int i = 0; i < n; i += 8) {
    __m256 x = _mm256_loadu_ps(&a[i]);
    __m256 y = _mm256_loadu_ps(&b[i]);
    __m256 z = _mm256_add_ps(x, y);
    _mm256_storeu_ps(&c[i], z);
  }
  clock_t end = clock();
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Somma con istruzioni vettoriali: %f ms\n", ms);

  start = clock();
  for (int i = 0; i < n; i++) {
    c[i] = a[i] + b[i];
  }
  end = clock();
  ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Somma senza istruzioni vettoriali: %f ms\n", ms);
  
  return 0;
}
