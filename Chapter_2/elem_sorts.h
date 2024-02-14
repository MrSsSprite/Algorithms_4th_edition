#ifndef ELEM_SORTS_H
#define ELEM_SORTS_H

void selection_sort(void *first, void *const last, size_t elem_size,
                    int (*cmpfunc)(const void*, const void*));
void insertion_sort(void *first, void *const last, size_t elem_size,
                    int (*cmpfunc)(const void*, const void*));
void shell_sort(void *first, void *const last, size_t elem_size,
                    int (*cmpfunc)(const void*, const void*));

#endif
