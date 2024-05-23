#include "knuth_shuffle.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

static inline
void _swap(void *lhs, void *rhs, size_t elem_size);
static inline
unsigned long rand_extended(void);

static unsigned int _RAND_LSHFTBIT = 0;   // treated as constant
static int _lshft_num;


static void initialize_RAND_LSHFTBIT(void)
{
#if RAND_MAX == 2147483647
  _RAND_LSHFTBIT = 31;
#elif RAND_MAX == 32767
  _RAND_LSHFTBIT = 15;
#else
  _RAND_LSHFTBIT = log2l((long double)RAND_MAX + 1);
#endif
}

void knuth_shuffle(void *first, void *const last, size_t elem_size)
{
  void *shuffled = first;
  size_t arr_sz = (last - first) / elem_size;
  size_t n = 0;

  srand(time(NULL));

  // initialize_RAND_LSHFTBIT if not already done
  if (_RAND_LSHFTBIT == 0)
    initialize_RAND_LSHFTBIT();

  if (arr_sz - 1> RAND_MAX)
  {
    for (_lshft_num = 1; pow(2, _RAND_LSHFTBIT * (1 + _lshft_num)) < arr_sz; _lshft_num++)
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
