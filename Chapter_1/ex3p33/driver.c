#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "deque_arr.h"

void print_deque(Deque this);

int main(int argc, char **argv)
{
  unsigned long data_size = 50;
  char *endptr;
  Deque container;

  srand(time(NULL));

  // parse zone
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
      fputs("data_size must be pure number\n", stderr);
      return 2;
    }
  }

  // test zone
  container = init_deque();
  if (container == NULL)
  {
    fputs("Failed to initialize container.\n", stderr);
    return 1;
  }

  for (int i = 0; i < data_size / 4; i++)
    deque_pushLeft(container, i);
  print_deque(container);

  for (int i = 0; i < data_size; i++)
    deque_pushRight(container, i);
  print_deque(container);

  puts("Resetting Container...");
  deque_cleanup(container);
  container = init_deque();

  for (int i = 0; i < data_size; i++)
    if (i % 2)
      deque_pushLeft(container, i);
    else
      deque_pushRight(container, i);
  print_deque(container);

  fputs("Poping: ", stdout);
  for (int i = data_size - 1; i >= 0; i--)
    if (i % 2)
      printf("(l)%d, ", deque_popLeft(container));
    else
      printf("(r)%d, ", deque_popRight(container));
  putchar('\n');
  print_deque(container);

  for (int i = 0; i < data_size; i++)
    deque_pushRight(container, rand() % (data_size * 10));
  print_deque(container);
  fputs("Poping: ", stdout);
  while (deque_size(container))
    printf("(l)%d, ", deque_popLeft(container));
  putchar('\n');
  print_deque(container);

  for (int i = 0; i < data_size; i++)
    deque_pushRight(container, rand() % (data_size * 10));
  print_deque(container);
  fputs("Poping: ", stdout);
  while (deque_size(container))
    printf("(r)%d, ", deque_popRight(container));
  putchar('\n');
  print_deque(container);

  deque_cleanup(container);
  return 0;
}

void print_deque(Deque this)
{
  printf("size = %zd, cap = %zd\n", deque_size(this), deque_cap(this));
  putchar('{');
  for (Deque_iter iter = deque_begin(this);
       iter != deque_end(this); iter = deque_iter_next(this, iter))
    printf("%d, ", *iter);
  putchar('}');
  putchar('\n');
}
