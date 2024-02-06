// compiled with ../algo_1p2/stack.c

#include "bag.h"

#include "../algo_1p2/stack.h"

#include <stdlib.h>

// actually should return int for malloc failure
// but I'm too indolent to fix it
void init_Bag(Bag *this, size_t item_size)
{
  this->interface = malloc(sizeof (struct Stack));
  init_Stack(this->interface, item_size);
}

int add(Bag *this, void *item)
{
  return push(this->interface, item);
}

Bag_iter get_bag_iter(Bag *this)
{
  return this->interface->first;
}

size_t bag_size(Bag *this)
{
  return this->interface->size;
}

void clear(Bag *this)
{
  void *data;

  while ((data = pop(this->interface)))
    free(data);

  free(this->interface);
}
