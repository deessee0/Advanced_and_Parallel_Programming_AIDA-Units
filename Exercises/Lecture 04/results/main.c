#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bst.h"
#include "tree_node.h"
#include "print_tree.h"

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
  printf("L'albero è profondo %d\n",bst_depth(t));
  print_tree(t);
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
  printf("L'albero è profondo %d\n",bst_depth(t));
  print_tree(t);
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
