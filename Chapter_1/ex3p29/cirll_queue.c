#include "cirll_queue.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

struct _list_node
{
  void *item;
  struct _list_node *next;
};

struct cirll_queue
{
  struct _list_node *tail;
  size_t count, item_size;
};

struct cirll_queue * init_CirLLQueue(size_t item_size)
{
  struct cirll_queue *ret = malloc(sizeof (struct cirll_queue));

  if (ret == NULL)
    return NULL;

  ret->tail = NULL;
  ret->count = 0;
  ret->item_size = item_size;

  return ret;
}

void cleanup_CirLLQueue(struct cirll_queue *this)
{
  struct _list_node *tempNode;

  if (this->tail != NULL)
  {
    while (this->tail->next != this->tail)
    {
      tempNode = this->tail->next;
      this->tail = tempNode->next;
      free(tempNode);
    }

    free(this->tail);
  }

  free(this);
}

int cirll_enqueue(struct cirll_queue *this, void *item)
{
  struct _list_node *newNode = malloc(sizeof (struct _list_node));

  if (newNode == NULL)
    return 1;

  newNode->item = malloc(this->item_size);
  if (newNode->item == NULL)
  {
    free(newNode);
    return 1;
  }

  memcpy(newNode->item, item, this->item_size);

  if (this->tail == NULL)
  {
    newNode->next = newNode;
    this->tail = newNode;
  }
  else
  {
    newNode->next = this->tail->next;
    this->tail->next = newNode;
    this->tail = newNode;
  }

  this->count++;
  return 0;
}

int cirll_enqueue_mv(struct cirll_queue *this, void *item)
{
  struct _list_node *newNode = malloc(sizeof (struct _list_node));

  if (newNode == NULL)
    return 1;

  newNode->item = item;
  newNode->next = this->tail->next;
  this->tail->next = newNode;

  this->count++;
  return 0;
}

void * cirll_dequeue(struct cirll_queue *this)
{
  if (this->tail == NULL)
    return NULL;

  struct _list_node *tempNode = this->tail->next;
  void *ret = tempNode->item;

  if (tempNode == this->tail)
    this->tail = NULL;
  else
    this->tail->next = tempNode->next;

  free(tempNode);

  this->count--;
  return ret;
}

size_t cirll_count(struct cirll_queue *this)
{ return this->count; }
