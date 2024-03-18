#ifndef KNUTH_SHUFFLE_H
#define KNUTH_SHUFFLE_H

#include <stddef.h>

void knuth_shuffle(void *first, void *const last, size_t elem_size);

#endif
