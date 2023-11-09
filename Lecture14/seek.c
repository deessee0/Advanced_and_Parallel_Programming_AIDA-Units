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

int main(int argc, char * argv[])
{
  const int n = 1000;
  create_file(n);
  FILE * fp = fopen("test.bin", "rb");
  for (int i = 0; i < 10; i++) {
    int pos = sizeof(int) * (rand() % n);
    fseek(fp, pos, SEEK_SET);
    int val;
    fread(&val, sizeof(int), 1, fp);
    printf("Letto %d in posizione %d\n", val, pos);
  }
  fclose(fp);
  return 0;
}
