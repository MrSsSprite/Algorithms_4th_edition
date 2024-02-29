#ifndef DOUBLYLL_H
#define DOUBLYLL_H

#include <stddef.h>

#define DBLL_ITEM_TYPE int

typedef struct dbll_node
{
  DBLL_ITEM_TYPE item;
  struct dbll_node *prev, *next;
} *dbll_iter;
typedef struct dbll* DoublyLinkedList;

DoublyLinkedList init_dbll(void);
void cleanup_dbll(DoublyLinkedList this);

int dbll_push_front(DoublyLinkedList this, DBLL_ITEM_TYPE item);
int dbll_push_back(DoublyLinkedList this, DBLL_ITEM_TYPE item);
DBLL_ITEM_TYPE dbll_pop_front(DoublyLinkedList this);
DBLL_ITEM_TYPE dbll_pop_back(DoublyLinkedList this);
dbll_iter dbll_insert_before(DoublyLinkedList this, dbll_iter pos, DBLL_ITEM_TYPE item);
dbll_iter dbll_insert_after(DoublyLinkedList this, dbll_iter pos, DBLL_ITEM_TYPE item);
dbll_iter dbll_erase(DoublyLinkedList this, dbll_iter pos);

dbll_iter dbll_begin(DoublyLinkedList this);
dbll_iter dbll_end(DoublyLinkedList this);
DBLL_ITEM_TYPE dbll_front(DoublyLinkedList this);
DBLL_ITEM_TYPE dbll_back(DoublyLinkedList this);
size_t dbll_count(DoublyLinkedList this);

#endif
