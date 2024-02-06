#ifndef _STACK_NODE
#define _STACK_NODE

struct _stack_node
{
  void *item;
  struct _stack_node *next;
};

#endif
