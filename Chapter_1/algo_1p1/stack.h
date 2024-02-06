#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct Stack
{
  void *elem;
  size_t elem_size;
  size_t size, capacity;
};

void init_Stack(struct Stack *this, size_t item_size);
/**
 * @brief   resize a Stack to have a new capacity
 * @param   this     the Stack
 * @param   new_cap  new capacity
 * @return  0 for successful; non-0 for failure
 */
int resize(struct Stack *this, size_t new_cap);
/**
 * @brief   push an item to the Stack
 * @param   this  the Stack
 * @param   item  the address of item to be pushed
 * @return  0 for sucessful; non-0 for failure
 */
int push(struct Stack *this, void *item);
/**
 * @brief   pop the last item from the Stack
 * @param   the Stack
 * @return  a void pointer pointing to a copy of the deleted element,
 *          or NULL if any error occurred
 */
void *pop(struct Stack *this);

#endif
