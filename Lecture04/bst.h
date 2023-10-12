#ifndef _BST_H
#define _BST_H
#include "node.h"


typedef struct _bst *bst;

struct _bst
{
    t_node root;
};

bst make_bst(void);
void delete_node_cascade(t_node t);
void delete_bst(bst t);
void bst_insert(bst t, t_node n);
int node_depth(t_node n);
int bst_depth(bst t);
void s_test(int n);
void r_test(int n);

#endif