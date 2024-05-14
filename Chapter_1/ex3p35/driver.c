#include <stdio.h>
#include <stdlib.h>

#include "RandomQueue.h"

int main(int argc, char **argv)
{
  unsigned long sample_size = 50;
  char *endptr;
  RandomQueue container;

  if (argc > 2)
  {
    fprintf(stderr, "Usage: %s [sample_size=50]\n", argv[0]);
    return 2;
  }

  if (argc > 1)
  {
    sample_size = strtoul(argv[1], &endptr, 10);
    if (*endptr)
    {
      fputs("sample_size must be pure positive number\n", stderr);
      return 2;
    }
  }

  container = init_RandomQueue();
  if (container == NULL)
  {
    fputs("Failed to initialize RandomQueue\n", stderr);
    return 1;
  }
  RandomQueue_seed_initializer();

  fputs("Enqueuing: {", stdout);
  for (int i = 0; i < sample_size; i++)
  {
    printf("%d, ", i);
    RandomQueue_enqueue(container, i);
  }
  puts("}");

  fputs("Container: ", stdout);
  print_arr(container);

  if (RandomQueue_isEmpty(container))
  {
    fputs("container is empty.\n", stderr);
    goto final_cleanup;
  }
  printf("Drawing %lu samples: {", sample_size / 2);
  for (unsigned long i = 0, i_ed = sample_size / 2; i < i_ed; i++)
    printf("%d, ", RandomQueue_sample(container));
  puts("}");

  fputs("Dequeuing: {", stdout);
  while (!RandomQueue_isEmpty(container))
    printf("%d, ", RandomQueue_dequeue(container));
  puts("}");

final_cleanup:
  RandomQueue_cleanup(container);
  return 0;
}
