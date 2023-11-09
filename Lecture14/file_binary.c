#include <stdio.h>

void write_array(int * v, int len)
{
  FILE * fp = fopen("test.bin", "wb");
  fwrite(v, sizeof(int), len, fp); 
  fclose(fp);
}

int read_array(int * v, int len)
{
  FILE * fp = fopen("test.bin", "rb");
  if (fp == NULL) {
    printf("Unable to open the file\n");
    return 0;
  }
  int bytes_read = fread(v, sizeof(int), len, fp);
  fclose(fp);
  return bytes_read;
}

int main(int argc, char * argv[])
{
  int v[5] = {10, 20, 40, 50, -5};
  write_array(v, 5);
  int w[5] = {0, 0, 0, 0, 0};
  int n = read_array(w, 5);
  printf("%d integers read\n", n);
  for (int i = 0; i < 5; i++) {
    printf("%d ", v[i]);
  }
  printf("\n");
  return 0;
}
