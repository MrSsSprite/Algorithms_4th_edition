#include "crate_list.h"

#include <stdio.h>
#include <stdlib.h>


static inline int _crate_list_expand(struct crate_list *this);


void init_crate_list(struct crate_list *this)
{
  this->shipping_dates = this->shipping_dates_cav = this->shipping_dates_ed = NULL;
}


int crate_list_add(struct crate_list *this, Date new_crate)
{
  if (this->shipping_dates_cav == this->shipping_dates_ed &&
      _crate_list_expand(this))
    return 1;

  *this->shipping_dates_cav++ = new_crate;

  return 0;
}

void crate_list_print(struct crate_list *this)
{
  char *month;

  putchar('{');
  for (Date *iter = this->shipping_dates; iter < this->shipping_dates_cav; iter++)
  {
    switch (iter->month)
    {
      case Jan:
        month = "Jan";
        break;
      case Feb:
        month = "Feb";
        break;
      case Mar:
        month = "Mar";
        break;
      case Apr:
        month = "Apr";
        break;
      case May:
        month = "May";
        break;
      case Jun:
        month = "Jun";
        break;
      case Jul:
        month = "Jul";
        break;
      case Aug:
        month = "Aug";
        break;
      case Sep:
        month = "Sep";
        break;
      case Oct:
        month = "Oct";
        break;
      case Nov:
        month = "Nov";
        break;
      case Dec:
        month = "Dec";
        break;
      default:
        month = "Error";
    }
    printf("%s %u, %d; ", month, iter->day, iter->year);
  }
  putchar('}');
  putchar('\n');
}


// helper func
static inline int _crate_list_expand(struct crate_list *this)
{
  size_t new_cap = (this->shipping_dates_ed - this->shipping_dates) * 2;
  Date *temp;

  if (new_cap == 0)
    new_cap = 1;

  temp = realloc(this->shipping_dates, new_cap * sizeof(Date));
  if (temp == NULL)
    return 1;

  this->shipping_dates_cav = temp + (this->shipping_dates_cav - this->shipping_dates);
  this->shipping_dates = temp;
  this->shipping_dates_ed = temp + new_cap;

  return 0;
}
