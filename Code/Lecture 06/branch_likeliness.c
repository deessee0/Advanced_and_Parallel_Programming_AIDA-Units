#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000000

int * random_vector(int len)
{
  int * v = (int *) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    v[i] = rand() % 100;
  }
  return v;
}

int sum_small_values(int * v, int len, int threshold)
{
  volatile int sum = 0;
  for (int i = 0; i < len; i++) {
    if (__builtin_expect(v[i] < threshold, 0)) {
      sum += v[i];
    }
  }
  return sum;
}

void branch_test(int * v, int threshold)
{
  int tmp;
  clock_t start = clock();
  tmp = sum_small_values(v, SIZE, threshold);
  clock_t end = clock();
  float seconds = (float) (end - start) / (CLOCKS_PER_SEC/1000.0);
  float p = threshold/100.0;
  // printf("p = %f\tElapsed time : %f ms\t%d\n", p, seconds, tmp);
  printf("%f\t%f\n", p, seconds);
}

int main(int argc, char * argv[])
{
  srand(time(NULL));
  int * v = random_vector(SIZE);
  printf("With branch\n");
  for (int i = 0; i <= 20; i += 1) {
    branch_test(v, i);
  }
  return 0;
}
