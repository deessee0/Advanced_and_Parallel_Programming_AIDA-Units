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
  int l = 0;
  int r = len;
  while (l < r)
  { // log_2(n) iterazione
    int m = (l + r) / 2;
    if(v[m] >= key){
      r = m;
    } else {
      l = m+1;
    }
  }
  if (v[l] == key)
  {
    return l;
  }
  else
  {
    return -1;
  }
}

int binary_search_branchless(int * v, int len, int key) {
  int l = 0;
  int r = len;
  while (l < r){ // log_2(n) iterazione
    int m = (l+r)/2;
    int q = v[m] >= key;
    r = q*m + (1-q)*r;
    l = q*l+ (1-q)*(m+1);
  }
  if (v[l] == key){
    return l;
  } else {
    return -1;
  }
}


int binary_search_branchless_prefetch(int * v, int len, int key) {
  int l = 0;
  int r = len;
  while (l < r)
  { // log_2(n) iterazione
    int m = (l + r) / 2;
    // accederò a (l+r)/2 ma..
    // caso1: (l+m)/2
    // caso2: (m+1+r)/2
    __builtin_prefetch(&v[((l+r)/2)]);
    __builtin_prefetch(&v[(m+1+r)/2]);
    int q = v[m] >= key;
    r = q * m + (1 - q) * r;
    l = q * l + (1 - q) * (m + 1);
  }
  if (v[l] == key)
  {
    return l;
  }
  else
  {
    return -1;
  }
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
    float a;
    float b;
    float c;
    printf("%d\t", i);
    a = test_search(binary_search, 1<<i, search_size);
    printf("%f\t",a);
    b = test_search(binary_search_branchless, 1 << i, search_size);
    printf("%f\t", b);
    c = test_search(binary_search_branchless_prefetch, 1 << i, search_size);
    printf("%f\t", c);
  }
  return 0;
}
