#include "union_find.h"

#include <stdio.h>
#include <stdlib.h>

struct union_find
{
  size_t *id, *sz;
  size_t data_size;
  size_t count;
};

struct union_find * init_UF(size_t data_size)
{
  // memory allocation
  struct union_find *ret = malloc(sizeof (struct union_find));
  if (ret == NULL)
    return NULL;
  ret->id = malloc(data_size * sizeof (size_t));
  if (ret->id == NULL)
  {
    free(ret);
    return NULL;
  }
  ret->sz = malloc(data_size * sizeof (size_t));
  if (ret->sz == NULL)
  {
    free(ret->id);
    free(ret);
    return NULL;
  }

  // initialization
  for (size_t i = 0; i < data_size; i++)
  {
    ret->id[i] = i;
    ret->sz[i] = 1;
  }
  ret->count = ret->data_size = data_size;

  return ret;
}

size_t UF_count(struct union_find *this)
{ return this->count; }

size_t UF_find(struct union_find *this, size_t p)
{
  size_t cur = p, prev;
  while (p != this->id[p])
    p = this->id[p];

  while (cur != p)
  {
    prev = cur;
    cur = this->id[cur];
    this->id[prev] = p;
  }

  return p;
}

int UF_union(struct union_find *this, size_t p, size_t q)
{
  p = UF_find(this, p);
  q = UF_find(this, q);
  
  if (p == q)
    return 0;

  // smaller root point to larger root
  if (this->sz[p] < this->sz[q])
  {
    this->id[p] = q;
    this->sz[q] += this->sz[p];
  }
  else
  {
    this->id[q] = p;
    this->sz[p] = this->sz[q];
  }

  this->count--;
  return 1;
}

void clean_UF(struct union_find *this)
{
  free(this->sz);
  free(this->id);
  free(this);
}

void print_sz(struct union_find *this)
{
    fputs("sz:\n", stdout);
    for (size_t i = 0; i < this->data_size; i++)
    {
      if (i % 8 == 0)
        putchar('\n');
      printf("%5d: %5d, ", i, this->id[i]);
    }
    putchar('\n');
}
