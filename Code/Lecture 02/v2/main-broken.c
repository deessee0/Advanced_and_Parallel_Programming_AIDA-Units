#include <stdio.h>

struct stat {
  float avg;
  int min;
  int max;
};

extern struct stat compute_stats(int * v, int len);

int main(int argc, char * argv[])
{
  int v[8] = {2, 3, 5, 7, -8, 9, 4, 1};
  struct stat s = compute_stats(v, 8);
  printf("min: %d\tmax: %d\tavg:%f\n", s.min, s.max, s.avg);
  return 0;
}
