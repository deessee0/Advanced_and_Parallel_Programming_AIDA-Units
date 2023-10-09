#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char * getmem(int len)
{
  char * m = (char *) malloc(len * sizeof(char));
  memset(m, 42, len);
  return m;
}

int readmem(char * m, int num, int stride)
{
  int sum = 0;
  for (int i = 0; i < num; i++) {
    sum += m[stride * i];
  }
  return sum;
}


int main(int argc, char * argv[])
{
  char * m = getmem(1024 * 1024 * 1024); // 1GB
  int strides[17] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
                     2048, 4096, 8192, 16384, 32768, 65536};
  int tmp;
  printf("Tempo richiesto per accedere 2**20 volte alla memoria\n");
  for (int i = 0; i < 17; i++) {
    clock_t start = clock();
    for (int j = 0; j < 64; j++) {
      tmp = readmem(m, 16384, strides[i]);
    }
    clock_t end = clock();
    float seconds = (float) (end - start) / (CLOCKS_PER_SEC/1000.0);
    printf("Stride %d\t Elapsed time : %f ms\t%d\n", strides[i], seconds, tmp);
  }
  return 0;
}
