#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "unrolled_linked_list.h"

unrolled_linked_list ulst_make(void)
{
  unrolled_linked_list un_list = (unrolled_linked_list)malloc(sizeof(struct _unrolled_linked_list));
  un_list->head = NULL;
  return un_list;
}

void ulst_delete(unrolled_linked_list lst)
{
  if (lst == NULL)
  {
    return;
  }

  unode current = lst->head;
  while (current != NULL)
  {
    unode prev = current;
    current = current->next;
    free(prev);
  }
  free(lst);
}

void ulst_add(unrolled_linked_list lst, int key)
{
  if (lst == NULL)
  {
    return;
  }

  bool trovato = 0;
  if (lst->head != NULL)
  {
    for (int i = 0; i < UNROLLED_SIZE; i++)
    {
      if (lst->head->valid[i] == 0)
      {
        lst->head->keys[i] = key;
        lst->head->valid[i] = 1;
        trovato = 1;
        break;
      }
    }
  }

  if (trovato == 0)
  {
    unode new = (unode)malloc(sizeof(struct _unrolled_node));
    for (int i = 0; i < UNROLLED_SIZE; i++)
    {
      new->valid[i] = 0;
    }

    new->keys[0] = key;
    new->valid[0] = 1;
    new->next = lst->head;
    lst->head = new;
  }
}

bool ulst_search(unrolled_linked_list lst, int key)
{ 
  if ((lst == NULL) || (lst->head == NULL))
  {
    return false;
  }

  unode current = lst->head;
  while (current != NULL)
  {
    for (int i = 0; i < UNROLLED_SIZE; i++)
    {
      if ((current->keys[i] == key) && (current->valid[i] == 1))
      {
        return true;
      }
    }
    current = current->next;
  }

  return false;
}

void ulst_print(unrolled_linked_list lst)
{
  if (lst == NULL)
  {
    printf("NIL");
    return;
  }
  printf("(");
  unode current = lst->head;
  while (current != NULL)
  {
    printf("[");
    for (int i = 0; i < UNROLLED_SIZE; i++)
    {
      if (current->valid[i])
      {
        printf("%d", current->keys[i]);
      }
      else
      {
        printf(".");
      }
      if (i < UNROLLED_SIZE - 1)
      {
        printf(" ");
      }
    }
    printf("]");
    if (current->next != NULL)
    {
      printf(" ");
    } 
    current = current->next;
  }
  printf(")");
}