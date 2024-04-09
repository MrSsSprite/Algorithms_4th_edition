#include "steque.h"

#include <stdio.h>
#include <stdlib.h>

void display_steque(Steque this);

int main(int argc, char **argv)
{
  unsigned long test_size = 10;
  char *endptr;
  int ival;
  Steque container = init_steque();

  if (container == NULL)
  {
    fputs("Failure: init_steque\n", stderr);
    return 1;
  }

  if (argc != 1 && argc != 2)
  {
    fprintf(stderr, "Usage: %s [test_size]\n", argv[0]);
    return 2;
  }

  if (argc == 2)
  {
    test_size = strtoul(argv[1], &endptr, 10);
    if (*argv[1] == '\0' || *endptr != '\0')
    {
      fputs("test_size must be a positive integer\n", stderr);
      return 2;
    }
  }

  printf("Pushing 1...%lu - 1 to the Steque\n", test_size);
  for (unsigned long i = 1; i < test_size; i++)
    steque_push(container, i);

  fputs("Steque Content: ", stdout);
  display_steque(container);

  for (unsigned long i = 0; i < test_size / 2; i++)
    steque_pop(container);
  puts("Half items have been poped.");

  printf("Enqueuing 0...%lu - 1 to the Steque\n", test_size * 2);
  for (unsigned long i = 0; i < test_size * 2; i++)
    steque_enqueue(container, i);
  fputs("Steque Content: ", stdout);
  display_steque(container);

  printf("Poping %lu items from the Steque...", test_size);
  for (unsigned long i = 0; i < test_size; i++)
  {
    ival = steque_pop(container);
    printf("%d, ", ival);
  }
  putchar('\n');

  printf("Pushing -1...-%lu to the Steque...\n", test_size / 3);
  for (int i = -1, i_ed = -(test_size / 3); i >= i_ed; i--)
    ival = steque_push(container, i);
  fputs("Steque Content: ", stdout);
  display_steque(container);

  printf("Enqueuing %lu 0s to the Steque...\n", test_size / 2);
  for (int i = 0, i_ed = test_size / 2; i < i_ed; i++)
    steque_enqueue(container, 0);
  fputs("Steque Content: ", stdout);
  display_steque(container);

  puts("Poping All items from the Steque...");
  while (steque_size(container))
  {
    ival = steque_pop(container);
    printf("%d, ", ival);
  }
  putchar('\n');

  clean_steque(container);

  return 0;
}

void display_steque(Steque this)
{
  Steque_iter iter;

  iter = steque_first(this);
  
  while (iter)
  {
    printf("%d, ", iter->item);
    iter = iter->next;
  }

  putchar('\n');
}
