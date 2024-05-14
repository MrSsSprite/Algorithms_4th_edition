#ifndef RANDOM_BAG_H
#define RANDOM_BAG_H

#include <stddef.h>

#define RANDOM_BAG_DATA_TYPE int

typedef struct random_bag* RandomBag;
typedef struct random_bag_iter* RandomBagIter;

RandomBag init_RandomBag(void);
void RandomBag_cleanup(RandomBag this);
int RandomBag_add(RandomBag this, RANDOM_BAG_DATA_TYPE item);

void RandomBagIter_seed_initializer(void);
RandomBagIter init_RandomBagIter(RandomBag target);
void RandomBagIter_cleanup(RandomBagIter this);
int RandomBagIter_next(RandomBagIter this);
int RandomBagIter_prev(RandomBagIter this);
RANDOM_BAG_DATA_TYPE RandomBagIter_deref(RandomBagIter this);
int RandomBagIter_end(RandomBagIter this);

#endif
