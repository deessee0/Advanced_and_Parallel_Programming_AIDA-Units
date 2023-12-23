#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "tree.h"

tree make_node(int key, float val, tree left, tree right)
{
  tree t = (tree) malloc(sizeof(struct _tree_node));
  t->key = key;
  t->val = val;
  t->left = left;
  t->right = right;
  return t;
}

tree insert(tree t, int key, float val)
{
  if (t == NULL) {
    return make_node(key, val, NULL, NULL);
  }
  if (key == t->key) {
    t->val = val;
  } else if (key < t->key) {
    t->left = insert(t->left, key, val);
  } else {
    t->right = insert(t->right, key, val);
  }
  return t;
}

bool search(tree t, int key, float * val)
{
  if (t == NULL) {
    return false;
  }
  if (t->key == key) {
    *val = t->val;
    return true;
  }
  if (key < t->key) {
    return search(t->left, key, val);
  } 
  return search(t->right, key, val);
}

void print_tree(tree t)
{
  if (t == NULL) {
    printf(".");
    return;
  }
  printf("(");
  print_tree(t->left);
  // printf(" %d:%f ", t->key, t->val);
  printf(" %d ", t->key);
  print_tree(t->right);
  printf(")");
}
