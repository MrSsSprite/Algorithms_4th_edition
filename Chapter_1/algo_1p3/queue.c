#include "queue.h"

#include <stdlib.h>
#include <string.h>

struct _queue_node
{
  void *item;
  struct _queue_node *next;
};

void init_Queue(Queue *this, size_t item_size)
{
  this->first = this->last = NULL;
  this->size = 0;
  this->elem_size = item_size;
}

int enqueue(Queue *this, void *item)
{
  struct _queue_node *oldLast = this->last;

  this->last = malloc(sizeof (struct _queue_node));
  if (this->last == NULL)
  {
    this->last = oldLast;
    return 1;
  }
  this->last->item = malloc(this->elem_size);
  if (this->last->item == NULL)
  {
    free(this->last);
    this->last = oldLast;
    return 1;
  }

  memcpy(this->last->item, item, this->elem_size);
  this->last->next = NULL;

  if (this->first == NULL)  this->first = this->last;
  else                      oldLast->next = this->last;

  this->size++;
  return 0;
}

void * dequeue(Queue *this)
{
  void *ret;
  if (this->first)
    ret = this->first->item;
  else
    return NULL;

  struct _queue_node *temp = this->first;
  this->first = temp->next;
  free(temp);
  
  if (--this->size == 0)
    this->last = NULL;
  return ret;
}
