#include <stdio.h>

void read_with_fscanf()
{
  FILE * fp = fopen("test.txt", "r");
  if (fp == NULL) {
    printf("Unable to open the file\n");
    return;
  }
  int x;
  while (fscanf(fp, "i = %d\n", &x) != EOF) {
    printf("%d\n", x);
  }
  fclose(fp);
}

void read_with_getc()
{
  FILE * fp = fopen("test.txt", "r");
  if (fp == NULL) {
    printf("Unable to open the file\n");
    return;
  }
  int c;
  while ((c = getc(fp)) != EOF) {
    putc(c, stdout);
  }
  fclose(fp);
}

int main(int argc, char * argv[])
{
  read_with_fscanf();
  read_with_getc();
  return 0;
}
