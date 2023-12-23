#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "tree_node.h"
#include "bst.h"

bst make_bst (void)
{
  bst tmp = (bst) malloc(sizeof(struct _bst));
  if (tmp == NULL) {
    errno = ENOMEM;
    perror("make_bst - creazione albero fallita.");
  } else {
    tmp->root = NULL;
  }
  return tmp;
}

void delete_node_cascade (t_node t)
{
  if (t == NULL)
    return;
  delete_node_cascade(t->left);
  delete_node_cascade(t->right);
  if (t->value != NULL)
    free(t->value);
  free(t);
}

void delete_bst (bst t)
{
  if (t != NULL)
    delete_node_cascade(t->root);
  free(t);
}

void bst_insert (bst t, t_node n)
{
  if (t != NULL && n != NULL) {
    if (t->root == NULL)
      t->root = n;
    else {
      t_node cfr = t->root;
      while (1) {
	if (n->key > cfr->key) {
	  if (cfr->right == NULL) {
	    cfr->right = n;
	    n->parent = cfr;
	    break;
	  } else
	    cfr = cfr->right;
	} else {
	  if (cfr->left == NULL) {
	    cfr->left = n;
	    n->parent = cfr;
	    break;
	  } else
	    cfr = cfr->left;
	}
      }
    }
  }
}

int node_depth (t_node n)
{
  if (n == NULL)
    return 0;
  int l = node_depth(n->left);
  int r = node_depth(n->right);
  if (l > r)
    return l + 1;
  return r + 1;
}

int bst_depth (bst t) {
  if (t != NULL)
    return node_depth(t->root);
  return 0;
}

/*end of file - bst.c */
