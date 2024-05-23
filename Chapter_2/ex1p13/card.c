#include "card.h"

int card_cmp(const struct card *lhs, const struct card *rhs)
{
  int ret = lhs->suit - rhs->suit;
  if (ret)
    return ret;
  else
    return lhs->rank - rhs->rank;
}

int card_cmp_wrapper(const void *lhs, const void *rhs)
{ return card_cmp((const struct card*) lhs, (const struct card*)rhs); }
