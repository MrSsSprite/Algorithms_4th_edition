#include "arrQueue.h"

#include <stdlib.h>
#include <string.h>

struct arrQueue
{
  void **arr, **arr_ed;
  void **first;
  size_t item_size, used_size, cap;
};

static int _arrQueue_resize(struct arrQueue *this, size_t size);
static inline int _arrQueue_expand(struct arrQueue *this)
{
  if (this->cap == 0)
    return _arrQueue_resize(this, 1);
  return _arrQueue_resize(this, this->cap * 2);
}
static inline int _arrQueue_shrink(struct arrQueue *this)
{
  if (this->used_size <= this->cap / 4)
    return _arrQueue_resize(this, this->cap / 2);
  else
    return -1;
}

struct arrQueue * init_arrQueue(size_t size, size_t item_size)
{
  struct arrQueue *ret = malloc(sizeof (struct arrQueue));

  if (ret == NULL)
    return NULL;

  ret->arr = malloc(size * sizeof (void*));
  if (ret->arr == NULL)
  {
    free(ret);
    return NULL;
  }

  ret->arr_ed = ret->arr + size;
  ret->first = ret->arr;
  ret->cap = size;
  ret->item_size = item_size;
  ret->used_size = 0;

  return ret;
}

void cleanup_arrQueue(struct arrQueue *this)
{
  while (this->used_size)
  {
    if (this->first == this->arr_ed)
      this->first = this->arr;
    free(this->first++);
    this->used_size--;
  }

  free(this->arr);
  free(this);
}

int enqueue(struct arrQueue *this, void *item)
{
  void **iter;
  size_t cav;

  if (this->used_size == this->cap
      && _arrQueue_expand(this))
    return 1;
  
  cav = this->arr_ed - this->first;
  if (cav <= this->used_size)
    iter = this->arr + (this->used_size - cav);
  else
    iter = this->first + this->used_size;
  
  *iter = malloc(this->item_size);
  if (*iter == NULL)
    return 1;

  memcpy(*iter, item, this->item_size);
  this->used_size++;

  return 0;
}

int enqueue_mv(struct arrQueue *this, void *item)
{
  void **iter;
  size_t cav;

  if (this->used_size == this->cap
      && _arrQueue_expand(this))
    return 1;
  
  cav = this->arr_ed - this->first;
  if (cav <= this->used_size)
    iter = this->arr + (this->used_size - cav);
  else
    iter = this->first + this->used_size;
  
  *iter = item;
  this->used_size++;

  return 0;
}

void * dequeue(struct arrQueue *this)
{
  void *ret;

  if (this->used_size == 0)
    return NULL;

  ret = *this->first++;

  if (this->first == this->arr_ed)
    this->first = this->arr;
  this->used_size--;
  _arrQueue_shrink(this);

  return ret;
}

size_t arrQueue_count(struct arrQueue *this)
{ return this->used_size; }

size_t arrQueue_capacity(struct arrQueue *this)
{ return this->cap; }

static int _arrQueue_resize(struct arrQueue *this, size_t size)
{
  void **newArr = malloc(size * sizeof (void*)), **newArr_ed = newArr + size;
  void **iter;
  size_t i, i_ed;

  if (newArr == NULL)
    return 1;

  // copy the pointers (references) to newArr
  for (iter = newArr, i = 0, i_ed = (size > this->used_size) ? this->used_size : size;
       i < i_ed; i++)
  {
    if (this->first == this->arr_ed)
      this->first = this->arr;
    *iter++ = *this->first++;
  }

  // free the discarded items, if any
  for (size_t j = i_ed; j < this->used_size; j++)
  {
    if (this->first == this->arr_ed)
      this->first = this->arr;
    free(*this->first++);
  }

  // free the original reference array
  free(this->arr);

  this->first = this->arr = newArr;
  this->arr_ed = newArr_ed;
  this->cap = size;
  if (this->used_size > size)
    this->used_size = size;

  return 0;
}
