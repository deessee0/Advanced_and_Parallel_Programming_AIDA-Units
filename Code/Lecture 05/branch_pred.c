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
    if (v[i] < threshold) {
      sum += v[i];
    }
  }
  return sum;
}

int sum_small_values_branchless(int * v, int len, int threshold)
{
  volatile int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += (v[i] < threshold) * v[i];
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

void branchless_test(int * v, int threshold)
{
  int tmp;
  clock_t start = clock();
  tmp = sum_small_values_branchless(v, SIZE, threshold);
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
  for (int i = 0; i <= 100; i += 2) {
    branch_test(v, i);
  }

  printf("Branchless\n");
  for (int i = 0; i <= 100; i += 2) {
    branchless_test(v, i);
  }
  return 0;
}
