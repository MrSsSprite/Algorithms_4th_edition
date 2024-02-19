#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

inline static void stackSet_cleanup(Stack digStack, Stack opStack);
inline static int evaluate_one(Stack digStack, Stack opStack);
inline static char * get_num(void);

int main(void)
{
  Stack digStack, opStack;
  int ch;
  char *string;

  digStack = init_stack(ST_STR);
  opStack = init_stack(ST_CH);
  if (digStack == NULL || opStack == NULL)
  {
    stackSet_cleanup(digStack, opStack);
    return 1;
  }

  while (1)
  {
    switch (ch = getchar())
    {
    case EOF:
    case '\n':
      goto end_of_input_loop;
    case '+':
    case '-':
      if (stack_count(digStack) == stack_count(opStack))
        goto handle_digit;
    case '*':
    case '/':
      stack_push(opStack, &ch);
      break;
    case '(':
    case ' ':
      continue;
    case ')':
      if (evaluate_one(digStack, opStack))
      {
        stackSet_cleanup(digStack, opStack);
        return 2;
      }
      break;
    default:
      if (isdigit(ch))
      {
handle_digit:
        ungetc(ch, stdin);
        string = get_num();
        if (string == NULL || stack_push(digStack, string))
        {
          stackSet_cleanup(digStack, opStack);
          return 1;
        }
        break;
      }

      stackSet_cleanup(digStack, opStack);
      return 2;
    }
  }
end_of_input_loop:

  if (stack_count(opStack) != 0 || stack_count(digStack) != 1)
  {
    stackSet_cleanup(digStack, opStack);
    return 2;
  }

  string = stack_pop(digStack).dig;
  puts(string);
  free(string);

  stackSet_cleanup(digStack, opStack);
  return 0;
}

inline static void stackSet_cleanup(Stack digStack, Stack opStack)
{
  cleanup_stack(digStack);
  cleanup_stack(opStack);
}

inline static int evaluate_one(Stack digStack, Stack opStack)
{
  char op;
  char *lhs, *rhs, *res;
  char *ptr;
  const char *iter;

  if (stack_count(digStack) < 2 || stack_count(opStack) < 1)
    return 2;

  op = stack_pop(opStack).op;
  lhs = stack_pop(digStack).dig;
  rhs = stack_pop(digStack).dig;

  // () + \0
  res = malloc(strlen(lhs) + strlen(rhs) + 6);
  if (res == NULL)
    return 1;
  ptr = res;

  *ptr++ = '(';
  for (iter = rhs; *iter != '\0'; iter++)
    *ptr++ = *iter;
  *ptr++ = ' ';
  *ptr++ = op;
  *ptr++ = ' ';
  for (iter = lhs; *iter != '\0'; iter++)
    *ptr++ = *iter;
  *ptr++ = ')';

  free(lhs);
  free(rhs);

  stack_push(digStack, res);

  return 0;
}

inline static char * get_num(void)
{
  size_t cap = 1;
  char *st = malloc(cap), *cav = st, *term = st + cap;
  char *temp;
  int ch;
  int encountered_dot = 0;
  int has_sign = 0;
  int in_dig = 0;
  int is_valid = 1;

  if (st == NULL)
    return NULL;

  while (1)
  {
    switch (ch = getchar())
    {
      case '.':
        if (encountered_dot)
          is_valid = 0;
        else
          encountered_dot = 1;
        break;
      case '+':
      case '-':
        if (has_sign || in_dig)
          is_valid = 0;
        else
          has_sign = 1;
        break;
      default:
        if (!isdigit(ch))
          is_valid = 0;
        else
          in_dig = 1;
    }

    if (is_valid)
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
    else
      break;
  }

  ungetc(ch, stdin);

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
