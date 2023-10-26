#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdbool.h>

struct _node {
  int key;
  struct _node * next;
};

typedef struct _node * node;

struct _linked_list {
  node head;
};

typedef struct _linked_list * linked_list;

linked_list lst_make(void);

/* Elimina la lista e tutto il suo contenuto */
void lst_delete(linked_list lst);

/* Aggiunge alla testa della lista un nuovo nodo con la chiave indicata */
void lst_add(linked_list lst, int key);

/* Ritorna vero se e solo se il valore cercato è presente nella lista */
bool lst_search(linked_list lst, int key);

/* Stampa il contenuto della lista */
void lst_print(linked_list lst);

#endif
