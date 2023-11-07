#ifndef _TREE_H
#define _TREE_H

#include <stdbool.h>

struct _tree_node {
  int key;
  float val;
  struct _tree_node * left;
  struct _tree_node * right;
};

typedef struct _tree_node * tree;

tree insert(tree t, int key, float val);

bool search(tree t, int key, float * val);

void print_tree(tree t);

#endif

