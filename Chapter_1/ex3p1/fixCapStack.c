#include "fixCapStack.h"

#include <stdlib.h>
#include <string.h>

struct FixCapStackStr
{
  char **arr;
  size_t size, cap;
};

FixCapStackStr * init_FixCapStackStr(size_t cap)
{
  FixCapStackStr *this = malloc(sizeof (FixCapStackStr));
  if (this == NULL)
    return NULL;

  this->arr = malloc(cap * sizeof (char*));
  if (this->arr == NULL)
  {
    free(this);
    return NULL;
  }
  this->size = 0;
  this->cap = cap;

  return this;
}

int isFull(FixCapStackStr *this)
{
  return this->size == this->cap;
}

int push(FixCapStackStr *this, char *item)
{
  if (isFull(this))
    return 1;

  this->arr[this->size] = malloc(strlen(item) + 1);
  if (this->arr[this->size] == NULL)
    return 2;
  strcpy(this->arr[this->size], item);

  this->size++;
  return 0;
}

char * pop(FixCapStackStr *this)
{
  if (this->size == 0)
    return NULL;

  return this->arr[--this->size];
}

void clean_FixCapStackStr(FixCapStackStr *this)
{
  while (this->size)
    free(this->arr[--this->size]);

  free(this);
}
