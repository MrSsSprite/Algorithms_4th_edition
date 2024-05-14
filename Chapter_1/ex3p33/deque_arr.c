#include "deque_arr.h"

#include <stdlib.h>

struct deque
{
  DEQUE_DATA_TYPE *arr, *arr_ed,
                  *head, *tail;
  size_t size, cap;
};

/**
 *  General Rule:
 *  1.  head should always be dereferencable (unless cap == 0, garbage if size == 0)
 *  2.  tail is one-pass last item (may be dereferencable but garbage data)
 */

static inline int _deque_resize(struct deque *this, size_t new_cap);
static inline int _deque_expand(struct deque *this);
static inline int _deque_shrink(struct deque *this);

struct deque *init_deque(void)
{
  struct deque *ret = malloc(sizeof (struct deque));

  if (ret == NULL)
    return NULL;

  ret->arr = ret->arr_ed = ret->head = ret->tail = NULL;
  ret->size = ret->cap = 0;

  return ret;
}

void deque_cleanup(struct deque *this)
{
  free(this->arr);
  free(this);
}

DEQUE_DATA_TYPE *deque_begin(struct deque *this)
{ return this->head; }

DEQUE_DATA_TYPE *deque_end(struct deque *this)
{ return this->tail; }

DEQUE_DATA_TYPE *deque_iter_next(struct deque *this, DEQUE_DATA_TYPE *iter)
{
  if (iter == this->tail)
    return NULL;
  if (++iter == this->tail)
    return iter;
  if (iter == this->arr_ed)
    iter = this->arr;

  return iter;
}

DEQUE_DATA_TYPE *deque_iter_prev(struct deque *this, DEQUE_DATA_TYPE *iter)
{
  if (iter == this->head)
    return NULL;
  if (iter == this->arr)
    iter = this->arr_ed;
  
  return --iter;
}

size_t deque_size(struct deque *this)
{ return this->size; }

size_t deque_cap(struct deque *this)
{ return this->cap; }

int deque_pushLeft(struct deque *this, DEQUE_DATA_TYPE item)
{
  if (this->size == this->cap && _deque_expand(this))
    return 1;

  if (this->size)
  {
    if (this->head == this->arr)
      this->head = this->arr_ed;
    *--this->head = item;
  }
  else
    *this->tail++ = item;

  this->size++;

  return 0;
}

int deque_pushRight(struct deque *this, DEQUE_DATA_TYPE item)
{
  if (this->size == this->cap && _deque_expand(this))
    return 1;

  if (this->tail == this->arr_ed)
    this->tail = this->arr;
  *this->tail++ = item;

  this->size++;

  return 0;
}

DEQUE_DATA_TYPE deque_popLeft(struct deque *this)
{
  DEQUE_DATA_TYPE ret;

  if (this->size) ret = *this->head++;
  else return ret;

  // keep head dereferencable
  // special case: tail == arr_ed
  //    handled by _deque_shrink,
  //      size == 0, cap shrink to 0
  if (this->head == this->arr_ed)
    this->head = this->arr;

  this->size--;
  _deque_shrink(this);

  return ret;
}

DEQUE_DATA_TYPE deque_popRight(struct deque *this)
{
  DEQUE_DATA_TYPE ret;
  if (this->size) ret = *--this->tail;
  else return ret;

  // special case: tail == arr_ed
  //    handled by _deque_shrink,
  //      size == 0, cap shrink to 0
  if (this->tail == this->arr)
    this->tail = this->arr_ed;

  this->size--;
  _deque_shrink(this);

  return ret;
}


// Aux Func
static inline int _deque_resize(struct deque *this, size_t new_cap)
{
  DEQUE_DATA_TYPE *new_arr, *new_arr_ed, *new_tail;

  if (new_cap == 0)
  {
    free(this->arr);
    this->arr = this->arr_ed = this->head = this->tail = NULL;
    this->size = this->cap = 0;
    return 0;
  }

  new_arr = malloc(new_cap * sizeof (DEQUE_DATA_TYPE));
  if (new_arr == NULL)
    return 1;
  new_tail = new_arr;
  new_arr_ed = new_arr + new_cap;

  if (this->size)
    *new_tail++ = *this->head++;
  while (this->head != this->tail && new_tail != new_arr_ed)
  {
    if (this->head == this->arr_ed)
      this->head = this->arr;
    *new_tail++ = *this->head++;
  }

  free(this->arr);
  this->head = this->arr = new_arr;
  this->arr_ed = new_arr_ed;
  this->tail = new_tail;
  this->cap = new_cap;
  this->size = new_tail - new_arr;

  return 0;
}

static inline int _deque_expand(struct deque *this)
{ return _deque_resize(this, this->cap ? this->cap * 2 : 1); }

static inline int _deque_shrink(struct deque *this)
{
  size_t new_cap = this->cap;
  while (this->size * 4 < new_cap)
    new_cap /= 2;
  if (new_cap != this->cap)
    return _deque_resize(this, new_cap);

  return 0;
}
