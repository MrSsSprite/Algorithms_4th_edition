#include "union_find.h"
#include "base_structure.h"

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
