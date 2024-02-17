#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

char * get_line(void);

int main(void)
{
  char *string;
  Expression exp;

  string = get_line();
  if (string == NULL)
    return 1;

  exp = expression_parser(string);
  if (exp == NULL)
    return 2;

  free(string);

  string = expression_to_string(exp);
  puts("Normal:");
  puts(string);
  free(string);

  string = expression_to_string_postfix(exp);
  puts("Postfix:");
  puts(string);
  free(string);

  cleanup_expression(exp);

  return 0;
}

char * get_line(void)
{
  size_t cap = 1;
  char *st = malloc(cap), *cav = st, *term = st + cap;
  char *temp;
  int ch;

  if (st == NULL)
    return NULL;

  while ((ch = getchar()) != EOF && ch != '\n')
  {
    if (cav == term)
    {
      temp = realloc(st, cap * 2);
      if (temp == NULL)
      {
        free(st);
        return NULL;
      }
      st = temp;
      cav = st + cap;
      term = st + (cap *= 2);
    }

    *cav++ = ch;
  }

  if (cav == term)
  {
    temp = realloc(st, cap + 1);
    if (temp == NULL)
    {
      free(st);
      return NULL;
    }
    st = temp;
    cav = st + cap;
  }

  *cav = '\0';

  return st;
}
