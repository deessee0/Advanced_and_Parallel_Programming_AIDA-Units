#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char * argv[])
{
  srand(time(NULL));
  int n = 1<<20;
  int *v = (int *) malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    v[i] = rand() % 10;
  }
  int dot = 0;
  clock_t start = clock();
  for (int i = 0; i < n; i++) {
    dot += v[i] *v[i];
  }
  clock_t end = clock();
  float ms = (end - start) / (CLOCKS_PER_SEC/1000.0);
  printf("il prodotto interno di v è %d\n", dot);
  printf("il tempo richiesto è stato %f ms\n", ms);
  return 0;
}
