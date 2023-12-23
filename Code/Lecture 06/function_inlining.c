#include <stdio.h>
#include <stdlib.h>

inline int f(int a, int b)
{
  int s = 0;
  while (a < b) {
    s += a;
    a++;
  }
  return s;
}


int g(int a, int b)
{
  int s = 0;
  while (a < b) {
    s += a;
    a++;
  }
  return s;
}


int main(int argc, char * argv[])
{
  int x = f(10, 20);
  int y = g(10, 20);
  printf("x = %d\ny = %d\n", x, y);
  return 0;
}
