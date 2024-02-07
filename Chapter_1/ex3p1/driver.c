#include <stdio.h>
#include <stdlib.h>

#include "fixCapStack.h"

int main(void)
{
  int status;
  FixCapStackStr *stack = init_FixCapStackStr(3);
  char *ptr;

  if (stack)
    puts("FixCapStackStr of size 3 initialized.");
  else
  {
    puts("Initialization of a FixCapStackStr of size 3 FAILED!");
    puts("Leaving the program...");
    return -1;
  }

  puts("pushing \"value 1\" to it...");
  if ((status = push(stack, "value 1")))
    printf("FAILED, error code: %d\n", status);
  puts("pushing \"another string\" to it...");
  if ((status = push(stack, "another string")))
    printf("FAILED, error code: %d\n", status);
  puts("pushing \"final char arr\" to it...");
  if ((status = push(stack, "final char arr")))
    printf("FAILED, error code: %d\n", status);
  puts("pushing \"exessive value\" to it...");
  if ((status = push(stack, "exessive value")))
    printf("FAILED, error code: %d\n", status);

  puts("Poping the items:\n");
  while ((ptr = pop(stack)))
  {
    puts(ptr);
    free(ptr);
  }

  clean_FixCapStackStr(stack);

  puts("Finished.");

  return 0;
}
