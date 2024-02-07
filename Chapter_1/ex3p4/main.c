/**
 * @file    main.c
 * @brief   check balance the parentheses
 */
#include <stdio.h>
#include <stdlib.h>
#include "../algo_1p2/stack.h"

int Parentheses(void);

int main(void)
{
  while (!feof(stdin))
    if (Parentheses())
      puts("false");
    else
      puts("true");

  return 0;
}

void cleanup_stack(Stack *this)
{
  while (this->size)
    free(pop(this));
}

int stack_check(Stack *this, char ch)
{
  int ret;
  char *cptr = pop(this);
  if (cptr == NULL)
    return 1;

  switch (ch)
  {
  case ']':
    ch = '[';
    break;
  case '}':
    ch = '{';
    break;
  case ')':
    ch = '(';
    break;
  default:
    fputs("Function Designed Error Captured in stack_check\n", stderr);
    return 1;
  }

  ret = ch != *cptr;
  free(cptr);

  return ret;
}

void consume_line(void)
{
  int ch;

  while ((ch = getchar()) != EOF && ch != '\n')
    continue;
}

int Parentheses(void)
{
  int ch;
  Stack paren_stack;

  init_Stack(&paren_stack, sizeof (char));

  while ((ch = getchar()) != EOF)
  {
    if (ch == '\n')
      break;

    switch (ch)
    {
    case '[':
    case '{':
    case '(':
      push(&paren_stack, &ch);
      break;
    case ']':
    case '}':
    case ')':
      if (stack_check(&paren_stack, ch))
      {
        cleanup_stack(&paren_stack);
        consume_line();
        return 1;
      }
      break;
    default:
      fputs("Invalid Input detected Please Retry\n", stderr);
      consume_line();
      cleanup_stack(&paren_stack);
      return -1;
    }
  }

  if (paren_stack.size)
  {
    cleanup_stack(&paren_stack);
    return 1;
  }
  else
    return 0;
}
