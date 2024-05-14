#include "random_bag.h"

#include <stdlib.h>
#include <time.h>

struct random_bag
{ RANDOM_BAG_DATA_TYPE *st, *cav, *ed; };

struct random_bag_iter
{
  size_t *st, *ed, *pos;
  RANDOM_BAG_DATA_TYPE *arr;
};

static inline int _RandomBag_resize(struct random_bag *this, size_t new_cap);
static inline int _RandomBag_expand(struct random_bag *this);
static inline void _RBI_exch(size_t *lhs, size_t *rhs);

struct random_bag *init_RandomBag(void)
{
  struct random_bag *ret = malloc(sizeof (struct random_bag));

  if (ret == NULL)
    return NULL;

  ret->st = ret->cav = ret->ed = NULL;

  return ret;
}

void RandomBag_cleanup(struct random_bag *this)
{
  free(this->st);
  free(this);
}

int RandomBag_add(struct random_bag *this, RANDOM_BAG_DATA_TYPE item)
{
  if (this->cav == this->ed && _RandomBag_expand(this))
    return 1;

  *this->cav++ = item;

  return 0;
}

void RandomBagIter_seed_initializer(void)
{ srand(time(NULL)); }

struct random_bag_iter *init_RandomBagIter(struct random_bag *target)
{
  size_t size;
  struct random_bag_iter *ret = malloc(sizeof (struct random_bag_iter));

  if (ret == NULL)
    return NULL;

  size = target->cav - target->st;
  ret->st = malloc(size * sizeof (size_t));
  if (ret->st == NULL)
  {
    free(ret);
    return NULL;
  }
  ret->ed = ret->st + size;
  ret->pos = ret->st;
  ret->arr = target->st;

  for (size_t i = 0; i < size; i++)
  {
    *(ret->st + i) = i;
    _RBI_exch(ret->st + i, ret->st + (rand() % (i + 1)));
  }

  return ret;
}

void RandomBagIter_cleanup(struct random_bag_iter *this)
{
  free(this->st);
  free(this);
}

int RandomBagIter_next(struct random_bag_iter *this)
{
  if (this->pos == this->ed)
    return 2;

  this->pos++;
  return 0;
}

int RandomBagIter_prev(struct random_bag_iter *this)
{
  if (this->pos == this->st)
    return 2;

  this->pos--;
  return 0;
}

RANDOM_BAG_DATA_TYPE RandomBagIter_deref(struct random_bag_iter *this)
{ return this->arr[*this->pos]; }

int RandomBagIter_end(struct random_bag_iter *this)
{ return this->pos == this->ed; }


// Aux Func.
static inline int _RandomBag_resize(struct random_bag *this, size_t new_cap)
{
  RANDOM_BAG_DATA_TYPE *new_arr = realloc(this->st, new_cap);

  if (new_arr == NULL)
    return 1;

  this->cav = new_arr + (this->cav - this->st);
  this->st = new_arr;
  this->ed = new_arr + new_cap;

  return 0;
}

static inline int _RandomBag_expand(struct random_bag *this)
{ return _RandomBag_resize(this, (this->ed - this->st) * 2); }

static inline void _RBI_exch(size_t *lhs, size_t *rhs)
{
  size_t temp;
  temp = *lhs;
  *lhs = *rhs;
  *rhs = temp;
}
