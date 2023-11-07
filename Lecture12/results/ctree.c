#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "ctree.h"

ctree make_cnode(int key, float val)
{
  ctree t = (ctree) malloc(sizeof(struct _ctree_node));
  t->key[0] = key;
  t->val[0] = val;
  t->first_free = 1;
  for (int i = 0; i < N+1; i++) {
    t->children[i] = NULL;
  }
  return t;
}

ctree cinsert(ctree t, int key, float val)
{
  if (t == NULL) {
    return make_cnode(key, val);
  }
  if (t->first_free < N) {
    int k = key;
    float v = val;
    for (int i = 0; i < t->first_free; i++) {
      if (key == t->key[i]) {
	t->val[i] = val;
	return t;
      }
      if (t->key[i] > k) {
	int tmp = k;
	k = t->key[i];
	t->key[i] = tmp;
	float ftmp = v;
	v = t->val[i];
	t->val[i] = ftmp;
      }
    }
    t->key[t->first_free] = k;
    t->val[t->first_free] = v;
    t->first_free++;
    return t;
  }
  int i = 0;
  while (i < N && key >= t->key[i]) {
    if (key == t->key[i]) {
      t->val[i] = val;
      return t;
    }
    i++;
  }
  t->children[i] = cinsert(t->children[i], key, val);
  return t;
}

bool csearch(ctree t, int key, float * val)
{
  if (t == NULL) {
    return false;
  }
  int i = 0;
  while (i < t->first_free && key >= t->key[i]) {
    if (key == t->key[i]) {
      *val = t->val[i];
      return true;
    }
    i++;
  }
  return csearch(t->children[i], key, val);
}

void print_ctree(ctree t)
{
  if (t == NULL) {
    printf(".");
    return;
  }
  printf("(");
  for (int i = 0; i < t->first_free; i++) {
    print_ctree(t->children[i]);
    // printf(" %d:%f ", t->key[i], t->val[i]);
    printf(" %d ", t->key[i]);
  }
  print_ctree(t->children[N]);
  printf(")");
}
