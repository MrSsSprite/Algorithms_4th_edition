#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct stack* Stack;
typedef const struct stack* const_Stack;
typedef struct _stack_node
{
  void *item;
  struct _stack_node *next;
}* Stack_iter;

Stack init_stack(size_t item_size);
void cleanup_stack(Stack this);
Stack cpy_stack(Stack src);

int stack_push(Stack this, void *item);
// stack_push_mv take over control of item while stack_push copies the memory block
int stack_push_mv(Stack this, void *item);
void *stack_pop(Stack this);

Stack_iter stack_begin(Stack this);
size_t stack_count(Stack this);

#endif
