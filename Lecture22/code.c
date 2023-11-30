#include <stdio.h>

int sum(int a, int b)
{
  int res = a + b;
  printf("Somma di %d e %d con risultato %d\n", a, b, res);
  return res;
}

float multiply(int a, float b)
{
  float res = a * b;
  printf("Moltiplicaizone di %d e %f con risultato %f\n", a, b, res);
  return res;
}

void swap(int * a, int * b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}
