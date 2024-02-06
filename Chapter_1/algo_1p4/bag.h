#ifndef BAG_H
#define BAG_H

#include <stddef.h>

struct Stack;
typedef struct Bag
{
  struct Stack *interface;
}
Bag;
typedef struct _stack_node *Bag_iter;

void init_Bag(Bag *this, size_t item_size);
int add(Bag *this, void *item);
size_t bag_size(Bag *this);
void clear(Bag *this);
Bag_iter get_bag_iter(Bag *this);

#endif
