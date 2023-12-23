#ifndef _NETPBM_H
#define _NETPBM_H

#include <stdio.h>

struct _netpbm_image {
  int width;
  int height;
  int offset;
  int size;
  FILE * fd;
  char * data;
};

typedef struct _netpbm_image netpbm;
typedef struct _netpbm_image * netpbm_ptr;

int open_image(char * path, netpbm_ptr img);

int empty_image(char * path, netpbm_ptr img, int width, int height);

char * pixel_at(netpbm_ptr img, int x, int y);

int close_image(netpbm_ptr img);

#endif
