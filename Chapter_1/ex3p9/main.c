#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>

#include "stack.h"

char * get_num(void);
char * combine_expression(const char *lhs, const char *rhs, char op);

int main(void)
{
  Stack opStack, expStack;
  char *string[2], *temp;
  int ch;

  opStack = init_stack(operator);
  if (opStack == NULL)
  {
    fputs("Failed to initialize opStack.\n", stderr);
    return -1;
  }
  expStack = init_stack(expression);
  if (expStack == NULL)
  {
    fputs("Failed to initialize expStack.\n", stderr);
    stack_cleanup(opStack);
    return -2;
  }

  while ((ch = getchar()) != EOF && ch != '\n')
  {
    if (isdigit(ch))
    {
      ungetc(ch, stdin);
      string[0] = get_num();
      if (string[0] == NULL)
      {
        fputs("Failed to get_num.\n", stderr);
        stack_cleanup(opStack);
        stack_cleanup(expStack);
        return -3;
      }
      stack_push(expStack, string[0]);
    }
    else switch (ch)
    {
    case ' ':
    case '(':
      continue;
    case '+':
    case '-':
    case '*':
    case '/':
      stack_push(opStack, (char*)&ch);
      break;
    case ')':
      string[0] = stack_pop(expStack).string;
      string[1] = stack_pop(expStack).string;
      ch = stack_pop(opStack).op;
      if (string[0] == NULL || string[1] == NULL || ch == '\0')
      {
        fputs("Fatal Parsing Error.\n", stderr);
        stack_cleanup(opStack);
        stack_cleanup(expStack);
        return 1;
      }
      temp = combine_expression(string[0], string[1], ch);
      if (temp == NULL)
      {
        fputs("Failed to combine_expression.\n", stderr);
        stack_cleanup(opStack);
        stack_cleanup(expStack);
        return 2;
      }
      free(string[0]);
      free(string[1]);
      stack_push(expStack, temp);
      break;
    default:
      fputs("Invalid Symbol Detected and skipped.\n", stderr);
    }
  }
  if (stack_count(opStack) != 0 || stack_count(expStack) != 1)
    fputs("Invalid Format!\n", stdout);
  else
  {
    temp = stack_pop(expStack).string;
    puts(temp);
    free(temp);
  }

  stack_cleanup(opStack);
  stack_cleanup(expStack);

  return 0;
}

char * get_num(void)
{
  size_t cap = 0;
  char *string = malloc(cap), *cavity = string, *terminal = string + cap;
  char *temp;
  int ch;

  if (string == NULL)
    return NULL;

  while (isdigit(ch = getchar()))
  {
    if (cavity == terminal)
    {
      temp = realloc(string, cap * 2);
      if (temp == NULL)
      {
        free(string);
        return NULL;
      }
      string = temp;
      cavity = temp + cap;
      terminal = temp + (cap *= 2);
    }

    *cavity++ = ch;
  }

  if (cavity == terminal)
  {
    temp = realloc(string, cap + 1);
    if (temp == NULL)
    {
      free(string);
      return NULL;
    }
    string = temp;
    cavity = temp + cap;
  }

  *cavity = '\0';

  return string;
}

char * combine_expression(const char *lhs, const char *rhs, char op)
{
  char *ret = malloc(strlen(lhs) + strlen(rhs) + 6);
  char *iter = ret;

  if (ret == NULL)
    return NULL;

  *iter++ = '(';

  while (*rhs != '\0')
    *iter++ = *rhs++;

  *iter++ = ' ';
  *iter++ = op;
  *iter++ = ' ';

  while (*lhs != '\0')
    *iter++ = *lhs++;
  
  *iter++ = ')';

  return ret;
}
