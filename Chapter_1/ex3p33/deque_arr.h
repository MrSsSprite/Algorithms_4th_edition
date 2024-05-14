#ifndef DEQUE_ARR_H
#define DEQUE_ARR_H

#include "stddef.h"

#define DEQUE_DATA_TYPE int

typedef struct deque* Deque;
typedef DEQUE_DATA_TYPE* Deque_iter;

Deque init_deque(void);
void deque_cleanup(Deque this);

Deque_iter deque_begin(Deque this);
Deque_iter deque_end(Deque this);
Deque_iter deque_iter_next(Deque this, Deque_iter iter);
Deque_iter deque_iter_prev(Deque this, Deque_iter iter);
size_t deque_size(Deque this);
size_t deque_cap(Deque this);

int deque_pushLeft(Deque this, DEQUE_DATA_TYPE item);
int deque_pushRight(Deque this, DEQUE_DATA_TYPE item);
DEQUE_DATA_TYPE deque_popLeft(Deque this);
DEQUE_DATA_TYPE deque_popRight(Deque this);

#endif
