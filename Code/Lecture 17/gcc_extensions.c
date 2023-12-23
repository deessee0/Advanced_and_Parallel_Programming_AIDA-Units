#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int v8si __attribute__ ((vector_size (8 * sizeof(int))));

int sum_vector(int * vec, int len)
{
  int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += vec[i];
  }
  return sum;
}

int sum_vector_simd(int * vec, int len)
{
  v8si sumv = {0, 0, 0, 0};
  int i;
  for (i = 0; i+7 < len; i+= 8) {
    v8si x = *(v8si *) &vec[i];
    sumv += x;
  }
  int sum = sumv[0] + sumv[1] + sumv[2] + sumv[3] + sumv[4] + sumv[5] + sumv[6] + sumv[7];
  for (; i < len; i++) {
    sum += vec[i];
  }
  return sum;
}

#define N 1000000

int main(int argc, char * argv[])
{
  int v[N];
  for (int i = 0; i < N; i++) {
    v[i] = rand() % 100;
  }
  clock_t start = clock();
  int s = sum_vector(v, N);
  clock_t end = clock();
  float  ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("s: %f\n", ms);
  start = clock();
  int sv = sum_vector_simd(v, N);
  end = clock();
  ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("sv: %f\n", ms);
  printf("s = %d, sv = %d\n", s, sv);
  return 0;
}
