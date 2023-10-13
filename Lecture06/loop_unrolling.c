#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
  int sum = 0;
  for (int i = 0; i < 8; i++) {
    sum += rand();
  }
  #pragma GCC unroll 16
  for (int i = 0; i < 256; i++) {
    sum += rand();
  }
  printf("sum = %d\n", sum);
  return 0;
}
