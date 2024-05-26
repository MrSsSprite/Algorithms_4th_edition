#ifndef DATE_H
#define DATE_H

enum month { Jan = 1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec };

typedef struct Date
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

#endif
