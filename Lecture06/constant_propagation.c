#include <stdio.h>

int main(int argc, char * argv[])
{
  int a = (5 * 6) + 4;
  int b = 2 - 3;
  int c = 2 * 3;
  int d = c / 4;
  printf("a = %d, b = %d, c = %d, d = %d\n", a, b, c, d);

  int sum = 0;
  for (int i = 0; i < 100; i++) {
    sum += i;
  }
  printf("sum = %d\n", sum);
  return 0;
}
