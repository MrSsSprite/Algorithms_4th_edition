#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int a = 1, b = 2, c = 3;
  int *p;
  struct Stack stack;

  init_Stack(&stack, sizeof(int));

  push(&stack, &a);
  push(&stack, &b);
  push(&stack, &c);

  for (int i = 0; i < 3; i++)
  {
    p = pop(&stack);
    printf("%d ", *p);
    free(p);
  }
  putchar('\n');
  printf("Done.\n");

  return 0;
}
