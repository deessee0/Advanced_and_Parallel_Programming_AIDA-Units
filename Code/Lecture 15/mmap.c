#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

int main(int argc, char * argv[])
{
  char * data;
  struct stat sbuf;
  FILE * fd = fopen("mmap_demo", "r");
  int fdnum = fileno(fd);
  
  stat("mmap_demo", &sbuf);

  data = mmap((void *)0, sbuf.st_size, PROT_READ, MAP_SHARED, fdnum, 0);

  for (int i = 0; i < 10; i++) {
    printf("%c %c\n", data[i], getc(fd));
  }
  
  munmap(data, sbuf.st_size);

  fclose(fd);
  
  return 0;
}
