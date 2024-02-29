#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cirll_queue.h"

int main(void)
{
  CirLLQueue queue;
  int *iptr;
  double *dptr, dval;

  srand(time(NULL));

  // first test: 10 ints
  queue = init_CirLLQueue(sizeof (int));
  if (queue == NULL)
  {
    fputs("Failed to initialize queue.\n", stderr);
    return 1;
  }
  for (int i = 0; i < 10; i++)
    if (cirll_enqueue(queue, &i))
    {
      fputs("Failed to enqueue.\n", stderr);
      cleanup_CirLLQueue(queue);
      return 1;
    }
    else
      printf("Enqueued one item, used_size = %zd\n",
             cirll_count(queue));

  while ((iptr = cirll_dequeue(queue)))
  {
    printf("%d, used_size = %zd\n", *iptr, cirll_count(queue));
    free(iptr);
  }
  cleanup_CirLLQueue(queue);

  queue = init_CirLLQueue(sizeof (double));
  if (queue == NULL)
  {
    fputs("Failed to initialize queue.\n", stderr);
    return 1;
  }
  for (int i = 0; i < 50; i++)
  {
    dval = (double) rand() / RAND_MAX;
    if (cirll_enqueue(queue, &dval))
    {
      fputs("Failed to enqueue.\n", stderr);
      cleanup_CirLLQueue(queue);
      return 1;
    }
    printf("Enqueued one item, used_size = %zd\n", cirll_count(queue));
  }
  for (int i = 0; i < 45; i++)
  {
    dptr = cirll_dequeue(queue);
    if (dptr == NULL)
    {
      fputs("Error: dequeue failed\n", stderr);
      cleanup_CirLLQueue(queue);
      return 3;
    }
    printf("%f, used_size = %zd\n", *dptr, cirll_count(queue));
    free(dptr);
  }
  for (int i = 0; i < 20; i++)
  {
    dval = (double) rand() / RAND_MAX;
    if (cirll_enqueue(queue, &dval))
    {
      fputs("Failed to enqueue.\n", stderr);
      cleanup_CirLLQueue(queue);
      return 1;
    }
    printf("Enqueued one item, used_size = %zd\n", cirll_count(queue));
  }
  while ((dptr = cirll_dequeue(queue)))
  {
    printf("%f, used_size = %zd\n", *dptr, cirll_count(queue));
    free(dptr);
  }
  cleanup_CirLLQueue(queue);

  return 0;
}
