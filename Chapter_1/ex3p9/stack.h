#ifndef STACK_H
#define STACK_H

#include <stddef.h>

typedef struct stack* Stack;
typedef union stack_item
{
  char *dig;
  char op;
}
Stack_item;
enum stack_type { ST_CH, ST_STR };

Stack init_stack(enum stack_type type);
void cleanup_stack(Stack this);

int stack_push(Stack this, void *item);
Stack_item stack_pop(Stack this);

size_t stack_count(Stack this);

#endif
