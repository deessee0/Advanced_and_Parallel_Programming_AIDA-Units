#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000

struct foo {
  int a;
  int b;
  int c;
  int d;
};

struct array_foo {
  int * a;
  int * b;
  int * c;
  int * d;
};

int main(int argc, char * argv[])
{
  srand(time(NULL));
  struct foo * v  = (struct foo *) malloc(N * sizeof(struct foo));
  for (int i = 0; i < N; i++) {
    v[i].a = rand();
  }
  int sum = 0;
  clock_t start = clock();
  for (int i = 0; i < N; i++) {
    sum += v[i].a;
  }
  clock_t end = clock();
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  volatile int tmp = sum;
  printf("Somma (array of structures) in %fms\n", ms);

  struct array_foo x;
  x.a = (int *) malloc(N * sizeof(int));
  x.b = (int *) malloc(N * sizeof(int));
  x.c = (int *) malloc(N * sizeof(int));
  x.d = (int *) malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    x.a[i] = rand();
  }
  sum = 0;
  start = clock();
  for (int i = 0; i < N; i++) {
    sum += x.a[i];
  }
  end = clock();
  ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  tmp = sum;
  printf("Somma (structure of arrays) in %fms\n", ms);
  return 0;
}
