#include <stdio.h>
#include <stdlib.h>

int * rand_vector(int len)
{
  int * v = (int *) malloc (len * sizeof(int));
  for (int i = 0; i < len; i++) {
    v[i] = rand()%100;
  }
  return v;
}

int sum_threshold(int * v, int len, int threshold)
{
  int sum = 0;
  for (int i = 0; i < len; i++) {
    if (v[i] < threshold) {
      sum += v[i];
    }
  }
  return sum;
}

int main(int argc, char * argv[])
{
  int n = 10000;
  int * v = rand_vector(n);
  int sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += sum_threshold(v, n, rand()%100);
  }
  printf("%d\n", sum);
  return 0;
}
