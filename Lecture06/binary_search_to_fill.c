#include <stdio.h>
#include <stdlib.h>
#include <time.h>

volatile int found_tot;

int cmpfunc (const void * a, const void * b) {
  return ( *(int*)a - *(int*)b );
}

int * random_vector(int len)
{
  int * v = (int *) malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    v[i] = rand();
  }
  return v;
}

int binary_search(int * v, int len, int key) {
  return -1;
}

int binary_search_branchless(int * v, int len, int key) {
  return -1;
}


int binary_search_branchless_prefetch(int * v, int len, int key) {
  return -1;
}



float test_search(int (*f) (int*, int, int), int size, int search_size)
{
  int * v = random_vector(size);
  qsort(v, size, sizeof(int), cmpfunc);
  int * keys = random_vector(search_size);
  int * pos = (int *) malloc(search_size * sizeof(int));
  clock_t start = clock();
  for (int i = 0; i < search_size; i++) {
    pos[i] = f(v, size, keys[i]);
  }
  clock_t end = clock();
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  for (int i = 0; i < search_size; i++) {
    if (pos[i] != -1) {
      found_tot++;
    }
  }
  free(v);
  free(keys);
  free(pos);
  return ms;
}


int main(int argc, char * argv[])
{
  srand(time(NULL));
  int search_size = 10000;
  int exp_min = 10;
  int exp_max = 23;
  
  printf("\tw/ branches\tbranchless\tb.less pref.\n");
  for (int i = exp_min; i <= exp_max; i++) {
    float t;
    printf("%d\t", i);
    t = test_search(binary_search, 1<<i, search_size);
    printf("%f\n", t);
  }
  return 0;
}
