#include "steque.h"

#include <stdlib.h>

struct steque
{
  struct _steque_node *first, *last;
  size_t size;
};

struct steque * init_steque(void)
{
  struct steque *ret = malloc(sizeof (struct steque));

  if (ret == NULL)
    return NULL;

  ret->first = ret->last = NULL;
  ret->size = 0;

  return ret;
}

void clean_steque(struct steque *this)
{
  struct _steque_node *temp;

  if (this == NULL)
    return;

  while ((temp = this->first))
  {
    this->first = temp->next;
    free(temp);
  }

  free(this);
}

int steque_push(struct steque *this, _STEQUE_DATA_TYPE item)
{
  struct _steque_node *node = malloc(sizeof (struct _steque_node));

  if (node == NULL)
    return 1;

  node->item = item;
  node->next = this->first;
  
  this->first = node;
  if (this->size++ == 0)
    this->last = node;

  return 0;
}

int steque_enqueue(struct steque *this, _STEQUE_DATA_TYPE item)
{
  struct _steque_node *node = malloc(sizeof (struct _steque_node));

  if (node == NULL)
    return 1;

  node->item = item;
  node->next = NULL;

  if (this->size++ == 0)
    this->first = this->last = node;
  else
  {
    this->last->next = node;
    this->last = node;
  }

  return 0;
}

_STEQUE_DATA_TYPE steque_pop(struct steque *this)
{
  _STEQUE_DATA_TYPE ret;
  struct _steque_node *node;

  if (this == NULL || this->first == NULL)
    return ret;

  node = this->first;
  this->first = node->next;

  ret = node->item;
  if (--this->size == 0)
    this->last = NULL;

  return ret;
}

struct _steque_node * steque_first(struct steque *this)
{ return this->first; }

struct _steque_node * steque_last(struct steque *this)
{ return this->last; }

_STEQUE_DATA_TYPE steque_front(struct steque *this)
{ return this->first->item; }

_STEQUE_DATA_TYPE steque_back(struct steque *this)
{ return this->last->item; }

size_t steque_size(struct steque *this)
{ return this->size; }
