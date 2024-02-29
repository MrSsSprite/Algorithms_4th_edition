#ifndef CIRLL_QUEUE_H
#define CIRLL_QUEUE_H

#include <stddef.h>

typedef struct cirll_queue* CirLLQueue;

CirLLQueue init_CirLLQueue(size_t item_size);
void cleanup_CirLLQueue(CirLLQueue this);

int cirll_enqueue(CirLLQueue this, void *item);
int cirll_enqueue_mv(CirLLQueue this, void *item);
void * cirll_dequeue(CirLLQueue this);

size_t cirll_count(CirLLQueue this);

#endif
