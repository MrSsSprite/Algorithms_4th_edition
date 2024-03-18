#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <stddef.h>

void quick_sort(void *first, void *const last, size_t elem_size,
                int (*cmpfunc)(const void*, const void*));

#endif
