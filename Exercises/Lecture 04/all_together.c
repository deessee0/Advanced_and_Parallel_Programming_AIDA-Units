#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

struct _tree_node {
  int key;
  void *value;
  struct _tree_node *left;
  struct _tree_node *right;
  struct _tree_node *parent;
};

typedef struct _tree_node *t_node;

t_node make_t_node (void)
{
  t_node tmp = (t_node) malloc(sizeof(struct _tree_node));
  if (tmp == NULL) {
    errno = ENOMEM;
    perror("make_t_node - creazione nodo fallita");
  } else {
    tmp->value = tmp->left = tmp->right = tmp->parent = NULL;
    tmp->key = 0;
  }
  return tmp;
}

void delete_t_node (t_node tmp)
{
  if (tmp == NULL)
    return;
  if (tmp->value != NULL)
    free(tmp->value);
  free(tmp);
}

struct _bst {
  t_node root;
};

typedef struct _bst *bst;

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

void s_test (int n)
{
  int i = 0;
  bst t = make_bst();
  printf("Aggiunta dei nodi\n");
  for (;i < n; i++) {
    t_node n = make_t_node();
    n->key = i;
    bst_insert(t, n);
  }
  printf("L'albero e' profondo %d\n",bst_depth(t));
  delete_bst(t);
}

void r_test (int n)
{
  int i = 0;
  bst t = make_bst();
  printf("Aggiunta dei nodi\n");
  for (;i < n; i++) {
    t_node n = make_t_node();
    n->key = rand();
    bst_insert(t, n);
  }
  printf("L'albero e' profondo %d\n",bst_depth(t));
  delete_bst(t);
}

int main (int argc, char * argv[])
{
  int n;
  srand((int)time(NULL));
  printf("Numero di nodi: ");
  while (!scanf("%d",&n));
  s_test(n);
  r_test(n);
  return 0;
}
