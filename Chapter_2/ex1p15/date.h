#ifndef DATE_H
#define DATE_H

#include <stdio.h>

enum month { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };

typedef struct date
{
  enum month month;
  unsigned int day;
  int year;
} Date;

static inline int Date_cmp(Date lhs, Date rhs)
{
  if (lhs.year != rhs.year)
    return lhs.year - rhs.year;
  if (lhs.month != rhs.month)
    return lhs.month - rhs.month;
  return lhs.day - rhs.day;
}

static inline void Date_print(Date *this)
{
  char *month;

  switch (this->month)
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
  printf("%s %u, %d", month, this->day, this->year);
}

#endif
