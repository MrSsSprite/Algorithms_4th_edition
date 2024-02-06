#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

struct _queue_node;

typedef struct
{
  struct _queue_node *first;
  struct _queue_node *last;
  size_t size;
  size_t elem_size;
}
Queue;

/**
 * @brief   initialize a Queue
 * @param   this        Queue to be initialized
 * @param   item_size   size of an element in Queue in byte(s)
 */
void init_Queue(Queue *this, size_t item_size);
/**
 * @brief   enque an item to the list
 * @param   this    Queue object
 * @param   item    item to be copied into the queue
 * @return  0 for successful; non-0 for failure
 */
int enqueue(Queue *this, void *item);

/**
 * @brief   dequeue an item from the list
 * @param   this    Queue object
 * @return  address to the dequeued item
 *          (the item is dynamically allocated. Plus, the returned pointer should be 
 *          the only reference to the block of memeory.)
 */
void * dequeue(Queue *this);

#endif
