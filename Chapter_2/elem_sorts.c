#include <stdlib.h>
#include <stddef.h>
#include <string.h>

void selection_sort(void *first, void *const last, size_t elem_size,
                    int (*cmpfunc)(const void*, const void*))
{
  char *iter, *min;
  char *temp = malloc(elem_size);
  if (temp == NULL)
    return;

  for (; first != last; first = first + elem_size)
  {
    for (iter = first + elem_size, min = first;
         iter != last; iter += elem_size)
      if (cmpfunc(iter, min) < 0)
        min = iter;
    if (min != first)
    {
      memcpy(temp, first, elem_size);
      memcpy(first, min, elem_size);
      memcpy(min, temp, elem_size);
    }
  }
  
  free(temp);
}

void insertion_sort(void *first, void *const last, size_t elem_size,
                    int (*cmpfunc)(const void*, const void*))
{
  char *sorted_ed, *iter;
  void *temp = malloc(elem_size);
  if (temp == NULL)
    return;

  for (sorted_ed = first; sorted_ed != last; sorted_ed += elem_size)
    for (iter = sorted_ed;
         iter != first && cmpfunc(iter, iter - elem_size) < 0;
         iter -= elem_size)
    {
      memcpy(temp, iter, elem_size);
      memcpy(iter, iter - elem_size, elem_size);
      memcpy(iter - elem_size, temp, elem_size);
    }

  free(temp);
}

void shell_sort(void *first, void *const last, size_t elem_size,
                    int (*cmpfunc)(const void*, const void*))
{
  char *range_ed, *sorted_ed, *iter, *prev;
  void *temp = malloc(elem_size);
  size_t h = 1, arr_sz = (last - first) / elem_size;

  if (temp == NULL)
    return;
  while (h < arr_sz / 3)
    h = 3 * h + 1;

  while (h >= 1)
  {
    // h-sort
    for (range_ed = sorted_ed = first + (h * elem_size);
         sorted_ed != last; sorted_ed += elem_size)
      for (iter = sorted_ed;
           iter >= range_ed && cmpfunc(iter, prev = iter - h * elem_size) < 0;
           iter = prev)
      {
        memcpy(temp, iter, elem_size);
        memcpy(iter, prev, elem_size);
        memcpy(prev, temp, elem_size);
      }

    h /= 3;
  }

  free(temp);
}
