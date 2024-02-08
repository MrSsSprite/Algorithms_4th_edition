/**
 * @file    stack.h
 * @brief   header for int Stack
 */
#ifndef STACK_H
#define STACK_H

typedef struct stack* Stack;

/**
 * @brief   get a new stack, which is initialized and dynamically allocated
 * @return  the Stack object, which is evaluated to 0 if failed, non-0 otherwise
 *          the Stack object also needs to be cleaned up by using clean_stack.
 */
Stack init_stack(void);
/**
 * @brief   push a value to the Stack
 * @param   this    the Stack object
 * @param   value   value to be pushed
 * @return  0 for successful, non-0 otherwise
 */
int push(Stack this, int value);

#endif
