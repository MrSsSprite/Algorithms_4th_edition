#include "stack.h"

#include <stdlib.h>
#include <string.h>

void init_Stack(struct Stack *this, size_t item_size)
{
  this->elem = NULL;
  this->elem_size = item_size;
  this->size = this->capacity = 0;
}

int resize(struct Stack *this, size_t new_cap)
{
  void *temp;

  if (new_cap == 0)
  {
    free(this->elem);
    this->elem = NULL;
  }
  else
  {
    temp = realloc(this->elem, new_cap * this->elem_size);
    if (temp == NULL)
      return 1;
    this->elem = temp;
  }

  this->capacity = new_cap;

  return 0;
}

int push(struct Stack *this, void *item)
{
  int status;

  // guarantee enough space
  if (this->size == this->capacity)
  {
    status = resize(this,
                    this->elem ? this->capacity * 2 : 1);
    if (status)
      return status;
  }

  memcpy((char*) this->elem + this->size * this->elem_size,
         item, this->elem_size);

  this->size++;

  return 0;
}

void *pop(struct Stack *this)
{
  void *ret = malloc(this->elem_size);

  if (ret == NULL)
    return NULL;

  if (this->size == 0)
  {
    free(ret);
    return NULL;
  }

  memcpy(ret, (char*)this->elem + --this->size * this->elem_size, this->elem_size);
  
  if (this->size == this->capacity / 4)
    resize(this, this->capacity / 2);

  return ret;
}
