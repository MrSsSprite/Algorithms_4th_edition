#include "union_find.h"

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

size_t UF_find(struct union_find *this, size_t p)
{ return id[p]; }

int UF_union(struct union_find *this, size_t p, size_t q)
{
  size_t pID = this->id[p], qID = this->id[q];

  if (pID == qID) 
    return 0;

  for (size_t i = 0; i < this->data_size; i++)
    if (this->id[i] == pID)
      this->id[i] = qID;

  count--;

  return 1;
}

void clean_UF(struct union_find *this)
{
  free(this->id);
  free(this);
}
