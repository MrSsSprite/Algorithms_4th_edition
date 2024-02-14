#include "mergesort.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

static void merge(void *first, void *mid, void *const last, void *aux_arr,
                  size_t elem_size, int (*cmpfunc)(const void *, const void*))
{
  char *aux_iter, *iter, *mid_iter;
  void *aux_ed;
  aux_ed = aux_arr + (mid - first);

  // copy every byte in the left half
  for (aux_iter = aux_arr, iter = first;
       iter != mid; iter++, aux_iter++)
    *aux_iter = *iter;

  iter = first;
  mid_iter = mid;
  for (aux_iter = aux_arr;
       aux_iter != aux_ed && mid_iter != last;
       iter += elem_size)
    if (cmpfunc(aux_iter, mid_iter) > 0)
    {
      memcpy(iter, mid_iter, elem_size);
      mid_iter += elem_size;
    }
    else
    {
      memcpy(iter, aux_iter, elem_size);
      aux_iter += elem_size;
    }

  // consume the remaining items
  while (aux_iter != aux_ed)
    *iter++ = *aux_iter++;
  while (mid_iter != last)
    *iter++ = *mid_iter++;
}

static void _merge_sort(void *first, void *const last, void *aux_arr, 
                        size_t elem_size, int (*cmpfunc)(const void*, const void*));

void merge_sort(void *first, void *const last, size_t elem_size,
          int (*cmpfunc)(const void*, const void*))
{
  if (first == last)
    return;
  void *aux_arr = malloc((last - first) / elem_size / 2 * elem_size);
  if (aux_arr == NULL)
    return;

  _merge_sort(first, last, aux_arr, elem_size, cmpfunc);
  
  free(aux_arr);
}

static void _merge_sort(void *first, void *const last, void *aux_arr, 
                        size_t elem_size, int (*cmpfunc)(const void*, const void*))
{
  size_t arr_size = (last - first) / elem_size;
  if (arr_size <= 1)
    return;

  void *mid = first + arr_size / 2 * elem_size;
  _merge_sort(first, mid, aux_arr, elem_size, cmpfunc);
  _merge_sort(mid, last, aux_arr, elem_size, cmpfunc);
  merge(first, mid, last, aux_arr, elem_size, cmpfunc);
}

void BU_merge_sort(void *first, void *const last, size_t elem_size,
                   int (*cmpfunc)(const void*, const void*))
{
  size_t arr_size = (last - first) / elem_size;
  void *aux_arr = malloc(arr_size * elem_size);
  char *iter, *mid, *ed;
  if (aux_arr == NULL)
    return;

  for (size_t merge_sz = 1, interval = 2 * merge_sz * elem_size;
       merge_sz < arr_size;
       merge_sz *= 2, interval = 2 * merge_sz * elem_size)
    for (iter = first, mid = iter + interval / 2, ed = iter + interval;
         (void*)mid < last;
         iter += interval, mid += interval, ed += interval)
      merge(iter, mid, (void*)ed < last ? ed : last, aux_arr, elem_size, cmpfunc);
}
