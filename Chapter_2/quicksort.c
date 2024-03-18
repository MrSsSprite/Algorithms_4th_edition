#include "quicksort.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "knuth_shuffle.h"

static void * _partition(void *first, void *const last, size_t elem_size,
                         int (*cmpfunc)(const void*, const void*));
static void _quick_sort_impl(void *first, void *const last, size_t elem_size,
                             int (*cmpfunc)(const void*, const void*));
static inline
void _swap(void *lhs, void *rhs, size_t elem_size);

void quick_sort(void *first, void *const last, size_t elem_size,
                int (*cmpfunc)(const void*, const void*))
{
  srand(time(NULL));

  knuth_shuffle(first, last, elem_size);

  _quick_sort_impl(first, last, elem_size, cmpfunc);
}

static void * _partition(void *first, void *const last, size_t elem_size,
                         int (*cmpfunc)(const void*, const void*))
{
  if (first + elem_size >= last)
    return first;

  void *liter = first + elem_size, *riter = last - elem_size;

  while (1)
  {
    // find the first elem that's >= *first
    while (liter < riter && cmpfunc(liter, first) < 0)
      liter += elem_size;

    // find the first elem that's <= *first
    while (cmpfunc(riter, first) > 0)
      riter -= elem_size;

    if (liter >= riter)
      break;
    _swap(liter, riter, elem_size);
    liter += elem_size;
    riter -= elem_size;
  }

  _swap(first, riter, elem_size);

  return riter;
}

static void _quick_sort_impl(void *first, void *const last, size_t elem_size,
                             int (*cmpfunc)(const void*, const void*))
{
  // base case
  if (first + elem_size >= last)
    return;

  void *const pivot = _partition(first, last, elem_size, cmpfunc);
  _quick_sort_impl(first, pivot, elem_size, cmpfunc);
  _quick_sort_impl(pivot + elem_size, last, elem_size, cmpfunc);
}

static inline
void _swap(void *lhs, void *rhs, size_t elem_size)
{
  char temp[elem_size];
  memcpy(temp, lhs, elem_size);
  memcpy(lhs, rhs, elem_size);
  memcpy(rhs, temp, elem_size);
}
