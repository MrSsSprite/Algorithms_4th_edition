#include "stack.h"

#include <stdlib.h>
#include <stddef.h>

static int pop_failure = 0;

struct _stack_node
{
  int value;
  struct _stack_node *next;
};

struct stack
{
  struct _stack_node *first;
  size_t size;
};

Stack init_stack(void)
{
  struct stack *ret = malloc(sizeof (struct stack));

  if (ret == NULL)
    return NULL;

  ret->first = NULL;
  ret->size = 0;

  return ret;
}

int push(Stack this, int value)
{
  struct _stack_node *oldFirst = this->first;
  this->first = malloc(sizeof (struct _stack_node));
  if (this->first == NULL)
    return 1;

  this->first->value = value;
  this->first->next = oldFirst;

  return 0;
}

int pop(Stack this)
{
  int ret;

  if (first)
