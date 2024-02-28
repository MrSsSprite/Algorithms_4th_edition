#ifndef STACK_H
#define STACK_H

typedef struct stack* Stack;
typedef union stack_item
{
  struct expression *exp;
  char ch;
  unsigned long ul;
} Stack_item;

enum stack_type { ST_EXP, ST_CHAR, ST_UL };

Stack init_stack(enum stack_type type);
// accept and skip NULL pointer
void cleanup_stack(Stack this);

int stack_push(Stack this, void *item);
Stack_item stack_pop(Stack this);

unsigned long stack_count(Stack this);
/**
 * @brief   peek the first item of the stack
 * @param   this    the Stack obj
 * @return  the first item; if empty, return_value.ch guaranteed to be 0
 */
Stack_item stack_first(Stack this);

#endif
