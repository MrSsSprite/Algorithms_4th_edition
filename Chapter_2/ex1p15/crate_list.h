#ifndef CRATE_LIST_H
#define CRATE_LIST_H

#include "date.h"

struct crate_list
{
  Date *shipping_dates, *shipping_dates_cav, *shipping_dates_ed;
};


void init_crate_list(struct crate_list *this);
int crate_list_add(struct crate_list *this, Date new_crate);
void crate_list_print(struct crate_list *this);

#endif
