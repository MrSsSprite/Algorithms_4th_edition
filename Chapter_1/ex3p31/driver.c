#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "doublyll.h"

static inline void dbll_print(DoublyLinkedList this);

int main(int argc, char **argv)
{
  int data_size;
  long lmax;
  char *endptr;
  DoublyLinkedList dbll;
  dbll_iter iter;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: %s data_size\n", argv[0]);
    return 2;
  }

  lmax = strtol(argv[1], &endptr, 10);
  if (endptr == argv[1])
  {
    fputs("data_size must be proper numerical value.\n", stderr);
    return 2;
  }
  if (lmax > INT_MAX)
  {
    fprintf(stderr, "data_size(%ld) must not be greater than %d\n", lmax, INT_MAX);
    return 2;
  }
  if (lmax < 1)
  {
    fprintf(stderr, "data_size(%ld) must be at least 1\n", lmax);
    return 2;
  }
  data_size = lmax;

  dbll = init_dbll();
  if (dbll == NULL)
  {
    fputs("Failed to initialize the doubly linked-list.\n", stderr);
    return 1;
  }

  puts("Content:");
  for (int i = 0; i < data_size; i++)
  {
    if (dbll_push_back(dbll, i))
    {
      fputs("Failed to push back.\n", stderr);
      cleanup_dbll(dbll);
      return 3;
    }
  }

  dbll_print(dbll);

  for (iter = dbll_begin(dbll); iter->item < data_size / 2; iter = iter->next)
    continue;
  printf("Inserting -123 after %d...\n", iter->item);
  if (dbll_insert_after(dbll, iter, -123) == NULL)
  {
      fputs("dbll Insertion failed\n", stderr);
      cleanup_dbll(dbll);
      return 3;
  }
  puts("Content:");
  dbll_print(dbll);

  for (int i = -1; i > -data_size; i--)
    if (dbll_push_front(dbll, i))
      fputs("Failed to push front.\n", stderr);
  puts("Content:");
  dbll_print(dbll);

  for (iter = dbll_begin(dbll); iter->item != 0; iter = iter->next)
    continue;
  if (dbll_insert_after(dbll, iter, 123) == NULL)
  {
    fputs("Failed to insert 123 after 0\n", stderr);
    cleanup_dbll(dbll);
    return 3;
  }
  if (dbll_insert_before(dbll, iter, 321) == NULL)
  {
    fputs("Failed to insert 321 before 0\n", stderr);
    cleanup_dbll(dbll);
    return 3;
  }
  puts("Content:");
  dbll_print(dbll);

  if (dbll_erase(dbll, iter) == NULL)
  {
    fputs("Failed to erase 0\n", stderr);
    cleanup_dbll(dbll);
    return 3;
  }

  puts("Final content:");
  while (dbll_count(dbll))
    printf("%d, ", dbll_pop_front(dbll));
  putchar('\n');
  cleanup_dbll(dbll);
  return 0;
}

static inline void dbll_print(DoublyLinkedList this)
{
  for (dbll_iter iter = dbll_begin(this); iter; iter = iter->next)
    printf("%d, ", iter->item);
  putchar('\n');
}
