#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arrQueue.h"

int main(void)
{
  ArrQueue queue;
  int *iptr;
  double *dptr, dval;

  srand(time(NULL));

  // first test: 10 ints
  queue = init_arrQueue(10, sizeof (int));
  if (queue == NULL)
  {
    fputs("Failed to initialize queue.\n", stderr);
    return 1;
  }
  for (int i = 0; i < 10; i++)
    if (enqueue(queue, &i))
    {
      fputs("Failed to enqueue.\n", stderr);
      cleanup_arrQueue(queue);
      return 1;
    }
    else
      printf("Enqueued one item, used_size = %zd, cap = %zd\n",
             arrQueue_count(queue), arrQueue_capacity(queue));

  while ((iptr = dequeue(queue)))
  {
    printf("%d, used_size = %zd, cap = %zd\n", *iptr,
           arrQueue_count(queue), arrQueue_capacity(queue));
    free(iptr);
  }
  cleanup_arrQueue(queue);

  queue = init_arrQueue(2, sizeof (double));
  if (queue == NULL)
  {
    fputs("Failed to initialize queue.\n", stderr);
    return 1;
  }
  for (int i = 0; i < 50; i++)
  {
    dval = (double) rand() / RAND_MAX;
    if (enqueue(queue, &dval))
    {
      fputs("Failed to enqueue.\n", stderr);
      cleanup_arrQueue(queue);
      return 1;
    }
    printf("Enqueued one item, used_size = %zd, cap = %zd\n",
           arrQueue_count(queue), arrQueue_capacity(queue));
  }
  for (int i = 0; i < 45; i++)
  {
    dptr = dequeue(queue);
    if (dptr == NULL)
    {
      fputs("Error: dequeue failed\n", stderr);
      cleanup_arrQueue(queue);
      return 3;
    }
    printf("%f, used_size = %zd, cap = %zd\n", *dptr,
           arrQueue_count(queue), arrQueue_capacity(queue));
    free(dptr);
  }
  for (int i = 0; i < 20; i++)
  {
    dval = (double) rand() / RAND_MAX;
    if (enqueue(queue, &dval))
    {
      fputs("Failed to enqueue.\n", stderr);
      cleanup_arrQueue(queue);
      return 1;
    }
    printf("Enqueued one item, used_size = %zd, cap = %zd\n",
           arrQueue_count(queue), arrQueue_capacity(queue));
  }
  while ((dptr = dequeue(queue)))
  {
    printf("%f, used_size = %zd, cap = %zd\n", *dptr,
           arrQueue_count(queue), arrQueue_capacity(queue));
    free(dptr);
  }
  cleanup_arrQueue(queue);

  return 0;
}
