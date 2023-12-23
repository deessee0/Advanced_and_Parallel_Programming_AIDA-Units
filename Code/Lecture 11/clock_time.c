#include <stdio.h>
#include <time.h>

int main(int argc, char * argv[])
{
  int n = 1000000;
  clock_t start = clock();
  for (int i = 0; i < n; i++) {
    clock();
  }
  clock_t end = clock();
  float ms = (float) (end - start) / (CLOCKS_PER_SEC / 1000.0);
  ms /= n;
  printf("Millisecondi per una chiamata a clock(): %f ms\n", ms);
  return 0;
}
