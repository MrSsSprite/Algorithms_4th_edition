#include "stack.h"

#include <stdlib.h>
#include "expression.h"

struct _stack_node
{
  union stack_item item;
  struct _stack_node *next;
};

struct stack 
{
  struct _stack_node *head;
  unsigned long count;
  enum stack_type type;
};

struct stack * init_stack(enum stack_type type)
{
  struct stack *ret = malloc(sizeof (struct stack));

  if (ret == NULL)
    return NULL;

  ret->head = NULL;
  ret->count = 0;
  ret->type = type;

  return ret;
}

void cleanup_stack(struct stack *this)
{
  struct _stack_node *temp;

  if (this == NULL)
    return;

  while (this->head)
  {
    // extract head
    temp = this->head;
    this->head = temp->next;

    // cleanup head
    if (this->type == ST_EXP)
      cleanup_expression(temp->item.exp);
    free(temp);
  }

  free(this);
}

int stack_push(struct stack *this, void *item)
{
  struct _stack_node *newNode = malloc(sizeof (struct _stack_node));

  if (newNode == NULL)
    return 1;

  switch (this->type)
  {
  case ST_CHAR: newNode->item.ch = *(char*)item;
                break;
  case ST_EXP:  newNode->item.exp = (struct expression *)item;
                break;
  case ST_UL:   newNode->item.ul = *(unsigned long*)item;
                break;
  default:
                return 2;
  }
  newNode->next = this->head;
  this->head = newNode;

  this->count++;
  return 0;
}

union stack_item stack_pop(struct stack *this)
{
  union stack_item ret;
  struct _stack_node *temp;

  if (this->head == NULL)
  {
    ret.ch = '\0';
    return ret;
  }

  ret = this->head->item;

  temp = this->head;
  this->head = temp->next;
  free(temp);

  this->count--;
  return ret;
}

unsigned long stack_count(struct stack *this)
{ return this->count; }

union stack_item stack_first(struct stack *this)
{ 
  union stack_item ret;
  if (this->head == NULL)
  {
    ret.ch = '\0';
    return ret;
  }

  return this->head->item;
}
