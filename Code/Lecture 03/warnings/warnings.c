#include <stdio.h>
#include <stdlib.h>

// Questo file esiste per generare dei warnings

int f(int x, int y)
{
  return x*x;
}


int main(int argc, char * argv[])
{
  short a[3] = {1,2,3};
  int b = 1<<64;
  printf("%d\n", b);
  for (int i = 0; i < 3; i++) {
    printf("%d %d\t", a[i], f(a[i], 1));
  }
  int * p = malloc(sizeof(int));
  printf("%p\n", p);
  return 0;
}
