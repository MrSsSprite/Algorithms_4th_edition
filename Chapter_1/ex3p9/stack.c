#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct _stack_node
{
  union Stack_item item;
  struct _stack_node *next;
};

struct stack
{
  struct _stack_node *first;
  size_t count;
  enum data_type data_type;
};

struct stack * init_stack(enum data_type data_type)
{
  struct stack *ret = malloc(sizeof (struct stack));
  if (ret == NULL)
    return NULL;

  ret->first = NULL;
  ret->count = 0;
  ret->data_type = data_type;

  return ret;
}

int stack_push(struct stack *this, char *item)
{
  struct _stack_node *newHead = malloc(sizeof (struct _stack_node));
  if (newHead == NULL)
    return 1;

  newHead->next = this->first;
  switch (this->data_type)
  {
    case operator:
      newHead->item.op = *item;
      break;
    case expression:
      newHead->item.string = item;
      break;
    default:
      fputs("Invalid data_type of this detected in stack_push\n", stderr);
      return -1;
  }

  this->first = newHead;
  this->count++;
  return 0;
}

union Stack_item stack_pop(struct stack *this)
{
  union Stack_item ret;
  struct _stack_node *temp = this->first;
  if (temp == NULL)
  {
    if (this->data_type == expression)
      ret.string = NULL;
    else
      ret.op = '\0';
    return ret;
  }

  this->first = temp->next;
  this->count--;
  ret = temp->item;
  free(temp);

  return ret;
}

void stack_cleanup(struct stack *this)
{
  struct _stack_node *temp;
  while ((temp = this->first))
  {
    this->first = temp->next;
    if (this->data_type == expression)
      free(temp->item.string);
    free(temp);
  }

  free(this);
}

size_t stack_count(struct stack *this)
{ return this->count; }
