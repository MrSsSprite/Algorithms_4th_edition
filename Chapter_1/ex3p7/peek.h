#ifndef STACK_PEEK_H
#define STACK_PEEK_H

#include "../algo_1p2/stack.h"
#include "../algo_1p2/_stack_node.h"

void * peek(Stack *this)
{
  if (this->first)
    return this->first->item;
  else
    return NULL;
}

#endif
