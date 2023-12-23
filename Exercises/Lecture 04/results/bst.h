#ifndef _BST_H

#define _BST_H

#include "tree_node.h"

struct _bst {
  t_node root;
};

typedef struct _bst *bst;

bst make_bst (void);

void delete_bst (bst);

void bst_insert (bst, t_node);

void bst_insert_rand (bst, t_node);

int bst_depth (bst);

int bst_m_depth (bst);

#endif

/* end of file - bst.h */
