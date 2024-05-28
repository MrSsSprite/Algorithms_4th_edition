#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "../ex1p15/date.h"

#include <stdio.h>

typedef struct transaction
{
  Date date;
  unsigned int amount;
} Transaction;

static int transaction_cmp_amount(Transaction *lhs, Transaction *rhs)
{ return lhs->amount - rhs->amount; }

static void transaction_print(Transaction *this)
{
  Date_print(&this->date);
  printf(": %u", this->amount);
}

#endif
