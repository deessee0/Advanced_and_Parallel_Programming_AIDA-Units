#include <stdio.h>

#include "print_tree.h"


void print_tree_node(t_node T)
{
  if (T == NULL) {
    printf(".");
    return;
  }
  if (T->left == NULL && T->right == NULL) {
    printf("%d", T->key);
    return;
  }
  printf("(%d ", T->key);
  print_tree_node(T->left);
  printf(" ");
  print_tree_node(T->right);
  printf(")");
}

void print_tree(bst T)
{
  if (T == NULL) {
    return;
  }
  print_tree_node(T->root);
  printf("\n");
}
