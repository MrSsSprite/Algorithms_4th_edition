#ifndef FIXCAPSTACK_H
#define FIXCAPSTACK_H

#include <stddef.h>

typedef struct FixCapStackStr FixCapStackStr;

/**
 * @brief   initialize a new FixCapStackStr
 * @param   cap   capacity of the Stack
 * @return  pointer to the Stack dynamically allocated; 
 *          NULL for failure
 */
FixCapStackStr * init_FixCapStackStr(size_t cap);
/**
 * @brief   push an item to the Stack
 * @param   this    the Stack object
 * @param   item    item to be pushed (copied but not taken over)
 * @return  0 for successful; non-0 otherwise.
 *          1: full stack, 2: malloc error
 */
int push(FixCapStackStr *this, char *item);
/**
 * @brief   pop item from Stack
 * @param   this    Stack object
 * @return  address to the string (Stack no longer reference to it)
 */
char * pop(FixCapStackStr *this);
/**
 * @brief   free all memory allocated for the Stack,
 *          (except for those poped, as they are taken over)
 * @param   this    the Stack object to be cleaned
 */
void clean_FixCapStackStr(FixCapStackStr *this);

#endif
