#include "stack.h"

#include <stdlib.h>
#include <string.h>

struct stack
{
  struct _stack_node *head;
  size_t item_size, count;
};

struct stack * init_stack(size_t item_size)
{
  struct stack *ret = malloc(sizeof (struct stack));
  
  if (ret == NULL)
    return NULL;

  ret->item_size = item_size;
  ret->count = 0;
  ret->head = NULL;

  return ret;
}

void cleanup_stack(struct stack *this)
{
  struct _stack_node *temp;

  if (this == NULL)
    return;

  while ((temp = this->head))
  {
    this->head = temp->next;
    free(temp->item);
    free(temp);
  }

  free(this);
}

struct stack * cpy_stack(struct stack *src)
{
  struct stack *ret = init_stack(src->item_size);
  struct _stack_node *iter = src->head;
  struct _stack_node *last;

  if (ret == NULL)
    return NULL;

  if (iter)
  {
    if (stack_push(ret, iter->item))
    {
      cleanup_stack(ret);
      return NULL;
    }
    last = ret->head;
    iter = iter->next;
  }

  while (iter)
  {
    last->next = malloc(sizeof (struct _stack_node));
    if (last->next == NULL)
    {
      cleanup_stack(ret);
      return NULL;
    }
    last->next->item = malloc(ret->item_size);
    if (last->next->item == NULL)
    {
      free(last->next);
      last->next = NULL;
      cleanup_stack(ret);
      return NULL;
    }
    last = last->next;
    memcpy(last->item, iter->item, ret->item_size);
    ret->count++;

    iter = iter->next;
  }

  return ret;
}

int stack_push(struct stack *this, void *item)
{
  struct _stack_node *newNode = malloc(sizeof (struct _stack_node));

  if (newNode == NULL)
    return 1;
  newNode->item = malloc(this->item_size);
  if (newNode->item == NULL)
  {
    free(newNode);
    return 1;
  }

  memcpy(newNode->item, item, this->item_size);
  newNode->next = this->head;
  this->head = newNode;

  this->count++;
  return 0;
}

int stack_push_mv(struct stack *this, void *item)
{
  struct _stack_node *newNode = malloc(sizeof (struct _stack_node));

  if (newNode == NULL)
    return 1;

  newNode->item = item;
  newNode->next = this->head;
  this->head = newNode;

  this->count++;
  return 0;
}

void *stack_pop(struct stack *this)
{
  struct _stack_node *temp;
  void *ret;

  if ((temp = this->head) == NULL)
    return NULL;

  ret = temp->item;
  this->head = temp->next;

  free(temp);

  this->count--;
  return ret;
}

struct _stack_node * stack_begin(struct stack *this)
{ return this->head; }

size_t stack_count(struct stack *this)
{ return this->count; }
