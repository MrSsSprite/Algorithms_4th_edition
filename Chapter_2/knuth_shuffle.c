#include "knuth_shuffle.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

static inline
void _swap(void *lhs, void *rhs, size_t elem_size);
static inline
unsigned long rand_extended(void);

static const unsigned int _RAND_LSHFTBIT = (unsigned int) (log(RAND_MAX + 1) / log(2));
static int _lshft_num;

void knuth_shuffle(void *first, void *const last, size_t elem_size)
{
  void *shuffled = first;
  size_t arr_sz = (last - first) / elem_size;
  size_t n = 0;

  srand(time(NULL));

  if (arr_sz > RAND_MAX + 1)
  {
    for (_lshft_num = 1; pow(2, 15 * (1 + _lshft_num)) < arr_sz; _lshft_num++)
      continue;
    while (shuffled < last)
    {
      _swap(shuffled, first + elem_size * (rand_extended() % ++n), elem_size);
      shuffled += elem_size;
    }
  }
  else
  {
    while (shuffled < last)
    {
      _swap(shuffled, first + elem_size * (rand() % ++n), elem_size);
      shuffled += elem_size;
    }
  }
}

static inline
void _swap(void *lhs, void *rhs, size_t elem_size)
{
  char temp[elem_size];

  memcpy(temp, lhs, elem_size);
  memcpy(lhs, rhs, elem_size);
  memcpy(rhs, temp, elem_size);
}

static inline
unsigned long rand_extended(void)
{
  unsigned long ret = rand();

  for (int i = 0; i < _lshft_num; i++)
  {
    ret <<= _RAND_LSHFTBIT;
    ret |= rand();
  }

  return ret;
}
