#include "union_find.h"
#include "base_structure.h"

size_t UF_find(struct union_find *this, size_t p)
{
  while (this->id[p] != p)
    p = this->id[p];

  return p;
}

int UF_union(struct union_find *this, size_t p, size_t q)
{
  p = UF_find(this, p);
  q = UF_find(this, q);

  if (p == q)
    return 0;

  this->id[p] = q;

  this->count--;
  
  return 1;
}
