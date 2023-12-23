#include <stdlib.h>
#include <stdio.h>

#include "unrolled_linked_list.h"

unrolled_linked_list ulst_make(void)
{
  /* TODO */
}

void ulst_delete(unrolled_linked_list lst)
{
  /* TODO */
}

void ulst_add(unrolled_linked_list lst, int key)
{
  /* TODO */
}

bool ulst_search(unrolled_linked_list lst, int key)
{
    /* TODO */
}

void ulst_print(unrolled_linked_list lst)
{
  if (lst == NULL) {
    printf("NIL");
    return;
  }
  printf("(");
  unode current = lst->head;
  while (current != NULL) {
    printf("[");
    for (int i = 0; i < UNROLLED_SIZE; i++) {
      if (current->valid[i]) {
	printf("%d", current->keys[i]);
      } else {
	printf(".");
      }
      if (i < UNROLLED_SIZE - 1) {
	printf(" ");
      }
    }
    printf("]");
    if (current->next != NULL) {
      printf(" ");
    }
    current = current->next;
  }
  printf(")");
}
