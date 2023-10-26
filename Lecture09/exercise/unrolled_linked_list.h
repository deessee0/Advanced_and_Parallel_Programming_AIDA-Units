#ifndef _UNROLLED_LINKED_LIST_H
#define _UNROLLED_LINKED_LIST_H

#include <stdbool.h>

#define UNROLLED_SIZE 16

struct _unrolled_node {
  int keys[UNROLLED_SIZE];
  bool valid[UNROLLED_SIZE];
  struct _unrolled_node * next;
};

typedef struct _unrolled_node * unode;

struct _unrolled_linked_list {
  unode head;
};

typedef struct _unrolled_linked_list * unrolled_linked_list;

unrolled_linked_list ulst_make(void);

/* Elimina la lista e tutto il suo contenuto */
void ulst_delete(unrolled_linked_list lst);

/* Aggiunge alla testa della lista un nuovo nodo con la chiave indicata */
void ulst_add(unrolled_linked_list lst, int key);

/* Ritorna vero se e solo se il valore cercato è presente nella lista */
bool ulst_search(unrolled_linked_list lst, int key);

/* Stampa il contenuto della lista */
void ulst_print(unrolled_linked_list lst);

#endif
