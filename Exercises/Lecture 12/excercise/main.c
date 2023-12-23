#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "tree.h"
#include "ctree.h"

void benchmark_tree(int n, int repetitions)
{
  tree t = NULL;
  for (int i = 0; i < n; i++) {
    int k = rand();
    float v = (float) rand() / RAND_MAX;
    t = insert(t, k, v);
  }
  int * to_search = (int *)malloc(repetitions * sizeof(int));
  for (int i = 0; i < repetitions; i++) {
    to_search[i] = rand();
  }
  bool b = true;
  volatile bool tmp;
  float val;
  clock_t start = clock();
  for (int i = 0; i < repetitions; i++) {
    b &= search(t, to_search[i], &val);
  }
  clock_t end = clock();
  tmp = b;
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Searching %d times in a tree: %f ms\n", repetitions, ms);
}

void benchmark_ctree(int n, int repetitions)
{
  ctree t = NULL;
  for (int i = 0; i < n; i++) {
    int k = rand();
    float v = (float) rand() / RAND_MAX;
    t = cinsert(t, k, v);
  }
  int * to_search = (int *)malloc(repetitions * sizeof(int));
  for (int i = 0; i < repetitions; i++) {
    to_search[i] = rand();
  }
  bool b = true;
  volatile bool tmp;
  float val;
  clock_t start = clock();
  for (int i = 0; i < repetitions; i++) {
    b &= csearch(t, to_search[i], &val);
  }
  clock_t end = clock();
  tmp = b;
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  printf("Searching %d times in a c-tree: %f ms\n", repetitions, ms);
}


void test_tree(int n)
{
  tree t = NULL;
  for (int i = 0; i < n; i++) {
    int k = rand() % n;
    float v = (float) rand() / RAND_MAX;
    t = insert(t, k, v);
      print_tree(t);
      printf("\n");
  }
  for (int i = 0; i < n; i++) {
    float v;
    printf("Searching for %d: %c\n", i, search(t, i, &v) ? 't' : 'f');
  }
}

void test_ctree(int n)
{
  ctree t = NULL;
  for (int i = 0; i < n; i++) {
    int k = rand() % n;
    float v = (float) rand() / RAND_MAX;
    t = cinsert(t, k, v);
    print_ctree(t);
    printf("\n");
  }
  for (int i = 0; i < n; i++) {
    float v;
    printf("Searching for %d: %c\n", i, csearch(t, i, &v) ? 't' : 'f');
  }
}

int main(int argc, char * argv[])
{  
  test_tree(10);
  benchmark_tree(1000000, 1000);

  // test_ctree(10);
  //benchmark_ctree(1000000, 1000);
  return 0;
}
