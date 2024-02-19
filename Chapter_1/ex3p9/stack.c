#include "stack.h"

#include <stdlib.h>

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
  struct stack * ret = malloc(sizeof (struct stack));
  
  if (ret == NULL)
    return NULL;

  ret->head = NULL;
  ret->count = 0;
  ret->type = type;

  return ret;
}

void cleanup_stack(struct stack *this)
{
  if (this == NULL)
    return;

  struct _stack_node *temp;

  if (this->type == ST_STR)
  {
    while ((temp = this->head))
    {
      this->head = temp->next;
      free(temp->item.dig);
      free(temp);
    }
  }
  else
  {
    while ((temp = this->head))
    {
      this->head = temp->next;
      free(temp);
    }
  }

  free(this);
}

int stack_push(struct stack *this, void *item)
{
  struct _stack_node *newNode = malloc(sizeof (struct _stack_node));

  if (newNode == NULL)
    return 1;

  newNode->next = this->head;

  if (this->type == ST_CH)
    newNode->item.op = *(char*)item;
  else
    newNode->item.dig = (char*)item;

  this->head = newNode;

  this->count++;
  return 0;
}

union stack_item stack_pop(struct stack *this)
{
  union stack_item ret;
  struct _stack_node *temp;

  if ((temp = this->head) == NULL)
  {
    ret.op = '\0';
    return ret;
  }

  this->head = temp->next;
  ret = temp->item;
  free(temp);

  this->count--;
  return ret;
}

size_t stack_count(Stack this)
{ return this->count; }
