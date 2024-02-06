#include <stdio.h>

#include "../algo_1p2/_stack_node.h"
#include "bag.h"

int main(void)
{
  int a = 1, b = 2, c = 3;
  Bag_iter iter;
  Bag bag;
  init_Bag(&bag, sizeof (int));

  add(&bag, &a);
  add(&bag, &b);
  add(&bag, &c);

  iter = get_bag_iter(&bag);
  if (iter == NULL)
  {
    fputs("Error Captured.\n", stderr);
    clear(&bag);
    return -1;
  }

  for (int i = 0; iter; i++, iter = iter->next)
    printf("Element #%d: %d\n", i, *((int*) iter->item));

  puts("Finished.");
  clear(&bag);
  puts("Memory Cleared");

  return 0;
}
