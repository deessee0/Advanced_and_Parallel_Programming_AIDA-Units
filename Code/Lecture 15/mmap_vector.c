#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

void read_vector(int len)
{
  FILE * fd = fopen("mmap_vector_demo", "r");
  if (fd == NULL) {
    printf("Impossibile aprire il file\n");
    return;
  }
  int fdnum = fileno(fd);
  int * data = mmap((void *)0, len * sizeof(int), PROT_READ, MAP_SHARED, fdnum, 0);
  if (data == MAP_FAILED) {
    printf("Impossibile effettuare il mapping\n");
    return;
  }
  int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += data[i];
  }
  printf("La somma dei valori salvati nel file è %d\n", sum);
  munmap(data, len * sizeof(int));
  fclose(fd);
}

void write_vector(int len)
{
  FILE * fd = fopen("mmap_vector_demo", "w+");
  if (fd == NULL) {
    printf("Impossibile aprire il file\n");
    return;
  }
  int fdnum = fileno(fd);
  ftruncate(fdnum, len * sizeof(int));
  
  int * data = mmap((void *)0, len * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fdnum, 0);
  if (data == MAP_FAILED) {
    printf("Impossibile effettuare il mapping\n");
    return;
  }
  for (int i = 0; i < len; i++) {
    data[i] = i;
  }
  munmap(data, len * sizeof(int));
  fclose(fd);
  
}

int main(int argc, char * argv[])
{
  const int len = 10000;
  write_vector(len);
  read_vector(len);
  return 0;
}
