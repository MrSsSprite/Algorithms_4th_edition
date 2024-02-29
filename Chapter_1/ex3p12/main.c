#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

#define LINE_LENGTH 80

static inline unsigned int dig_len(long value);
static inline void print_stack(Stack_iter iter, unsigned int max_dig, unsigned int value_per_line);

int main(int argc, char **argv)
{
  long low_bound = 0, up_bound = 10;
  char *ptr;
  int status;
  unsigned int max_dig_len[2], value_per_line, counter;
  Stack_iter iter;
  Stack source_stack, dest_stack;

  switch (argc)
  {
  case 1:
    break;
  case 3:
    low_bound = strtol(argv[1], &ptr, 10);
    if (*ptr != '\0')
    {
      fputs("low_bound must be pure integer number.\n", stderr);
      return 2;
    }
    up_bound = strtol(argv[2], &ptr, 10);
    if (*ptr != '\0')
    {
      fputs("up_bound must be pure integer number.\n", stderr);
      return 2;
    }

    if (low_bound >= up_bound)
    {
      fputs("up_bound must be greater than low_bound.\n", stderr);
      return 2;
    }

    break;
  default:
    fprintf(stderr, "Usage: %s [low_bound up_bound]\n", argv[0]);
    return 2;
  }

  source_stack = init_stack(sizeof (long));
  if (source_stack == NULL)
  {
    fputs("Failed to initialize source_stack.\n", stderr);
    return 1;
  }

  for (long i = low_bound; i < up_bound; i++)
    if ((status = stack_push(source_stack, &i)))
    {
      cleanup_stack(source_stack);
      return status;
    }

  // calculation for formatting
  max_dig_len[0] = dig_len(low_bound);
  max_dig_len[1] = dig_len(up_bound);
  if (max_dig_len[0] < max_dig_len[1])
    max_dig_len[0] = max_dig_len[1];
  value_per_line = LINE_LENGTH / (max_dig_len[0] + 2);
  if (value_per_line == 0)
    value_per_line = 1;

  printf("%ld numbers loaded to the source stack successfully.\n", up_bound - low_bound);
  print_stack(stack_begin(source_stack), max_dig_len[0], value_per_line);

  dest_stack = cpy_stack(source_stack);
  if (dest_stack == NULL)
  {
    fputs("Failed to copy source_stack to dest_stack.\n", stderr);
    cleanup_stack(source_stack);
    return 1;
  }
  else
    puts("Copied source_stack to dest_stack successfully.");
  print_stack(stack_begin(dest_stack), max_dig_len[0], value_per_line);

  cleanup_stack(dest_stack);
  cleanup_stack(source_stack);
  return 0;
}

static inline unsigned int dig_len(long value)
{
  unsigned int len = 0;

  // for the negative sign
  if (value < 0)
    len++;

  while (value)
  {
    len++;
    value /= 10;
  }

  if (len == 0)
    len = 1;

  return len;
}

static inline void print_stack(Stack_iter iter, unsigned int max_dig, unsigned int value_per_line)
{
  unsigned int counter;
  puts("The content:");
  for (counter = 0; iter; iter = iter->next)
  {
    printf("%*ld, ", max_dig, *(long*)iter->item);
    counter++;
    if (counter == value_per_line)
    {
      counter = 0;
      putchar('\n');
    }
  }
  if (counter)
    putchar('\n');
}
