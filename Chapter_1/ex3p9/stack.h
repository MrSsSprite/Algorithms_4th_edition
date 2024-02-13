/**
 * @file    stack.h
 * @brief   interfaces of Stack
 */
#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct stack* Stack;
union Stack_item { char op; char *string; };
enum data_type { operator, expression };

/**
 * @brief   initialize a new Stack obj
 * @param   data_type   data_type stored in the Stack: operator or expression
 * @return  the initialized Stack obj., which has to be cleaned up by calling stack_cleanup
 */
Stack init_stack(enum data_type data_type);
/**
 * @brief   push an item to the stack
 * @param   this    Stack obj
 * @param   item    item to be pushed;
 *                  for string, pointer is passed and take over control (NOT copied);
 *                  for char, pointer to char is passed, and the char is COPIED
 * @return  0 for successful, non-0 otherwise
 */
int stack_push(Stack this, char *item);
/**
 * @brief   pop an item from the Stack
 * @param   this    Stack obj
 * @return  the poped item
 */
union Stack_item stack_pop(Stack this);
/**
 * @brief   clean up Stack, balance each init_stack call
 * @param   this    Stack obj to be cleaned up
 */
void stack_cleanup(Stack this);
size_t stack_count(Stack this);

#endif
