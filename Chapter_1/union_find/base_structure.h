#ifndef BASE_STRUCTURE_H
#define BASE_STRUCTURE_H

#include <stddef.h>
#include <stdlib.h>

struct union_find
{
  size_t *id;
  size_t data_size;
  size_t count;
};

struct union_find * init_UF(size_t data_size)
{
  // allocate memory for UF obj
  struct union_find *ret = malloc(sizeof (struct union_find));
  if (ret == NULL)
    return NULL;
  ret->id = malloc(data_size * sizeof(size_t));
  if (ret->id == NULL)
  {
    free(ret);
    return NULL;
  }

  // initialization
  for (size_t i = 0; i < data_size; i++)
    ret->id[i] = i;
  ret->count = ret->data_size = data_size;

  return ret;
}

size_t UF_count(struct union_find *this)
{ return this->count; }

void clean_UF(struct union_find *this)
{
  free(this->id);
  free(this);
}

#endif
