#ifndef RANDOMQUEUE_H
#define RANDOMQUEUE_H

#define RANDOMQUEUE_DATATYPE int

typedef struct random_queue* RandomQueue;

void RandomQueue_seed_initializer(void);
RandomQueue init_RandomQueue(void);
void RandomQueue_cleanup(RandomQueue this);

int RandomQueue_enqueue(RandomQueue this, RANDOMQUEUE_DATATYPE item);
RANDOMQUEUE_DATATYPE RandomQueue_dequeue(RandomQueue this);
RANDOMQUEUE_DATATYPE RandomQueue_sample(RandomQueue this);

int RandomQueue_isEmpty(RandomQueue this);

void print_arr(struct random_queue *this);

#endif
