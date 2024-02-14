#ifndef MERGESOORT_H
#define MERGESOORT_H

#include <stddef.h>

void merge_sort(void *first, void *const last, size_t elem_size,
                int (*cmpfunc)(const void*, const void*));
void BU_merge_sort(void *first, void *const last, size_t elem_size,
                   int (*cmpfunc)(const void*, const void*));

#endif
