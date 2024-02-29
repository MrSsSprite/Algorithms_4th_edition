/**
 * @file    main.c
 * @brief   take a line of math expression (infix) from stdin,
 *          and convert it to postfix version.
 * @note    the program must be compiled with ALL .c files in ../expression_parser
 *          EXCEPT for the drivers in ../expression_parser/test_source directory
 */
#include "../expression_parser/parser.h"

#include <stdio.h>
#include <stdlib.h>

static char * get_line(void);

int main(void)
{
  char *string;
  Expression exp;

  string = get_line();
  if (string == NULL)
    return 1;

  exp = expression_parser(string);
  free(string);

  if (exp == NULL)
    return 2;

  string = expression_to_string_postfix(exp);
  puts(string);
  free(string);

  cleanup_expression(exp);

  return 0;
}

static char * get_line(void)
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

  if (temp == NULL)
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
