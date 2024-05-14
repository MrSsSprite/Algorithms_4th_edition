#include "RandomQueue.h"

#include <stdlib.h>
#include <time.h>

#include <stdio.h>

struct random_queue
{ RANDOMQUEUE_DATATYPE *st, *cav, *ed; };


static inline int _RandomQueue_resize(struct random_queue *this, size_t new_cap);
static inline int _RandomQueue_expand(struct random_queue *this);
static inline int _RandomQueue_shrink(struct random_queue *this);
static inline void _RandomQueue_exch(RANDOMQUEUE_DATATYPE *lhs, RANDOMQUEUE_DATATYPE *rhs);

void print_arr(struct random_queue *this)
{
  putchar('{');
  for (RANDOMQUEUE_DATATYPE *iter = this->st; iter < this->cav; iter++)
    printf("%d, ", *iter);
  putchar('}');
  putchar('\n');
}


void RandomQueue_seed_initializer(void)
{ srand(time(NULL)); }

struct random_queue *init_RandomQueue(void)
{
  struct random_queue *ret = malloc(sizeof (struct random_queue));

  if (ret == NULL)
    return NULL;

  ret->st = ret->cav = ret->ed = NULL;

  return ret;
}

void RandomQueue_cleanup(struct random_queue *this)
{
  free(this->st);
  free(this);
}

int RandomQueue_enqueue(struct random_queue *this, RANDOMQUEUE_DATATYPE item)
{
  if (this->cav == this->ed && _RandomQueue_expand(this))
    return 1;

  *this->cav++ = item;

  return 0;
}

RANDOMQUEUE_DATATYPE RandomQueue_dequeue(struct random_queue *this)
{
  RANDOMQUEUE_DATATYPE ret;

  if (this->st == this->cav)
    return ret;

  _RandomQueue_exch(this->cav - 1, this->st + (rand() % (this->cav - this->st)));

  ret = *--this->cav;

  _RandomQueue_shrink(this);

  return ret;
}

RANDOMQUEUE_DATATYPE RandomQueue_sample(struct random_queue *this)
{
  RANDOMQUEUE_DATATYPE ret;

  if (this->st == this->cav)
    return ret;

  ret = *(this->st + rand() % (this->cav - this->st));

  return ret;
}

int RandomQueue_isEmpty(struct random_queue *this)
{ return this->cav == this->st; }


// Aux. Func.
static inline int _RandomQueue_resize(struct random_queue *this, size_t new_cap)
{
  RANDOMQUEUE_DATATYPE *new_st = realloc(this->st, new_cap * sizeof(RANDOMQUEUE_DATATYPE));
  size_t size;

  if (new_st == NULL)
    return 1;

  size = this->cav - this->st;
  this->st = new_st;
  this->cav = new_st + (new_cap < size ? new_cap : size);
  this->ed = new_st + new_cap;

  return 0;
}

static inline int _RandomQueue_expand(struct random_queue *this)
{ return _RandomQueue_resize(this, this->st == this->ed ? 1 : (this->ed - this->st) * 2); }

static inline int _RandomQueue_shrink(struct random_queue *this)
{
  size_t new_cap = this->ed - this->st, size = this->cav - this->st;
  while (size * 4 < new_cap)
    new_cap /= 2;

  if (new_cap != this->ed - this->st)
    return _RandomQueue_resize(this, new_cap);
  else
    return 0;
}

static inline void _RandomQueue_exch(RANDOMQUEUE_DATATYPE *lhs, RANDOMQUEUE_DATATYPE *rhs)
{
  if (lhs == rhs)
    return;
  *lhs ^= *rhs;
  *rhs ^= *lhs;
  *lhs ^= *rhs;
}
