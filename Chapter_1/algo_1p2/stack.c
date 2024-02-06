#include "stack.h"

#include <stdlib.h>
#include <string.h>

#include "_stack_node.h"

void init_Stack(Stack *this, size_t item_size)
{
  this->first = NULL;
  this->size = 0;
  this->elem_size = item_size;
}

int push(Stack *this, void *value)
{
  struct _stack_node *oldFirst = this->first;

  this->first = malloc(sizeof (struct _stack_node));
  if (this->first == NULL)
    return 1;

  this->first->item = malloc(this->elem_size);
  if (this->first->item == NULL)
  {
    free(this->first);
    this->first = oldFirst;
    return 2;
  }
  memcpy(this->first->item, value, this->elem_size);

  this->first->next = oldFirst;

  this->size++;
  return 0;
}

void * pop(Stack *this)
{
  if (this->first == NULL)
    return NULL;

  void *ret = this->first->item;

  struct _stack_node *temp = this->first;
  this->first = temp->next;
  free(temp);
  this->size--;

  return ret;
}
