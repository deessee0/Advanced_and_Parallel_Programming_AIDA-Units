#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int * random_vector(int len)
{
  int * v = (int *) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    v[i] = rand() % 100;
  }
  return v;
}

int sum_small_values(int * v, int len)
{
  int sum = 0;
  for (int i = 0; i < len; i++) {
    if (v[i] < 50) {
      sum += v[i];
    }
  }
  return sum;
}

int main(int argc, char * argv[])
{
  srand(time(NULL));
  int * v1 = random_vector(SIZE);
  int * v2 = random_vector(SIZE);
  int tmp;
  
  clock_t start = clock();
  tmp = sum_small_values(v1, SIZE);
  clock_t end = clock();
  float seconds = (float) (end - start) / (CLOCKS_PER_SEC/1000.0);
  printf("Unordered\tElapsed time : %f ms\t%d\n", seconds, tmp);

  qsort(v2, SIZE, sizeof(int), cmpfunc);
  
  start = clock();
  tmp = sum_small_values(v2, SIZE);
  end = clock();
  seconds = (float) (end - start) / (CLOCKS_PER_SEC/1000.0);
  printf("Ordered\t\tElapsed time : %f ms\t%d\n", seconds, tmp);
  return 0;
}
