#include <stdio.h>
#include <stdlib.h>

#include "random_bag.h"

int main(int argc, char **argv)
{
  unsigned long data_size = 50;
  char *endptr;
  RandomBag container;
  RandomBagIter iter;

  if (argc > 2)
  {
    fprintf(stderr, "Usage: %s [data_size=50]\n", argv[0]);
    return 2;
  }

  if (argc > 1)
  {
    data_size = strtoul(argv[1], &endptr, 10);
    if (!*argv[1] || *endptr)
    {
      fputs("data_size must be pure (positive) number.\n", stderr);
      return 2;
    }
  }

  container = init_RandomBag();
  if (container == NULL)
  {
    fputs("Failed to initialize RandomBag\n", stderr);
    return 1;
  }

  fputs("Adding: {", stdout);
  for (int i = 0; i < data_size; i++)
  {
    printf("%d, ", i);
    RandomBag_add(container, i);
  }
  putchar('}');
  putchar('\n');

  RandomBagIter_seed_initializer();
  for (int i = 0; i < 5; i++)
  {
    putchar('{');
    for (iter = init_RandomBagIter(container); !RandomBagIter_end(iter); RandomBagIter_next(iter))
      printf("%d, ", RandomBagIter_deref(iter));
    putchar('}');
    putchar('\n');
    RandomBagIter_cleanup(iter);
  }

  RandomBag_cleanup(container);
  return 0;
}
