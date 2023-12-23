#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include "netpbm.h"

int open_image(char * path, netpbm_ptr img)
{
  return -1;
}

int empty_image(char * path, netpbm_ptr img, int width, int height)
{
  FILE * fd = fopen(path, "w+");
  if (fd == NULL) {
    return -1;
  }
  int written = fprintf(fd, "P5\n%d %d\n255\n", width, height);
  ftruncate(fileno(fd), written + width * height);
  fclose(fd);
  return open_image(path, img);
}

char * pixel_at(netpbm_ptr img, int x, int y)
{
  return NULL;
}

int close_image(netpbm_ptr img)
{
  return 0;
}
