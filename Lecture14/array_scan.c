#include <stdio.h>
#include <stdlib.h>

void create_file(int n)
{
  FILE * fp = fopen("test.bin", "wb");
  for (int i = 0; i < n; i++) {
    fwrite(&i, sizeof(int), 1, fp);
  }
  fclose(fp);
}

int scan_array()
{
  FILE * fp = fopen("test.bin", "rb");
  int buffer[1024];
  int elem_read;
  int sum = 0;
  while ((elem_read = fread(buffer, sizeof(int), 1024, fp)) != 0) {
    for (int i = 0; i < elem_read; i++) {
      sum += buffer[i];
    }
  }
  fclose(fp);
  return sum;
}

int main(int argc, char * argv[])
{
  const int n = 1000000;
  create_file(n);
  int sum = scan_array();
  printf("Sum of the values: %d\n", sum);
  return 0;
}
