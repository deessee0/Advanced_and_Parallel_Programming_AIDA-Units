#ifndef _CTREE_H
#define _CTREE_H

#include <stdbool.h>

#define N 3

struct _ctree_node {
  int key[N];
  float val[N];
  int first_free;
  struct _ctree_node * children[N+1];
};

typedef struct _ctree_node * ctree;

ctree cinsert(ctree t, int key, float val);

bool csearch(ctree t, int key, float * val);

void print_ctree(ctree t);

#endif

