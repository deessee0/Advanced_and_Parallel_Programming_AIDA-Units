#ifndef _TREE_NODE_H

#define _TREE_NODE_H

struct _tree_node {
  int key;
  void *value;
  struct _tree_node *left;
  struct _tree_node *right;
  struct _tree_node *parent;
};

typedef struct _tree_node *t_node;

t_node make_t_node (void);

void delete_t_node (t_node);

#endif

/* end of file - tree_node.h */
