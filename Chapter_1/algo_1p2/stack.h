#ifndef STACK_H
#define STACK_H

#include <stddef.h>

struct _stack_node;

typedef struct Stack
{
  struct _stack_node *first;
  size_t size, elem_size;
}
Stack;

/**
 * @brief   initialize the given Stack
 * @param   this        the address of the Stack
 * @param   item_size   the size of one element in bytes
 */
void init_Stack(Stack *this, size_t item_size);
/**
 * @brief   push one element to the Stack
 * @param   this    the Stack client
 * @param   value   the address of the value to be copied
 * @return  0 for successful; non-0 for failure
 */
int push(Stack *this, void *value);
/**
 * @brief   remove and return the last element
 * @param   this    the Stack object
 * @return  an address to the last element, which is dynamically allocated.
 *          This address is also the only reference to that block of memory.
 *          NULL if not applicable or error captured
 */
void * pop(Stack *this);

#endif
