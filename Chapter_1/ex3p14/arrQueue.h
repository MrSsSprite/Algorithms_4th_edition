#ifndef ARRQUEUE_H
#define ARRQUEUE_H

#include <stddef.h>

typedef struct arrQueue* ArrQueue;

ArrQueue init_arrQueue(size_t size, size_t item_size);
void cleanup_arrQueue(ArrQueue this);

int enqueue(ArrQueue this, void *item);
int enqueue_mv(ArrQueue this, void *item);
void * dequeue(ArrQueue this);

size_t arrQueue_count(ArrQueue this);
size_t arrQueue_capacity(ArrQueue this);

#endif
