#include "parser.h"

#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
#include "stack.h"
#include "expression.h"

static enum
{
  SUCCESS = 0,
  MALLOC_ERR,
  INVALID_INPUT,
} error_code = 0;

int exp_parser_error(void)
{ return error_code; }

struct stackSet { Stack expStack, opStack, ctStack; };

static char * get_num(const char **strptr);
static void cleanup_stackSet(struct stackSet *this);
static struct stackSet * init_stackSet(void);

static int evaluate_one(Stack expStack, char op);
int get_op_precedence(char op);

struct expression * expression_parser(const char *string)
{
  struct expression *temp_exp;
  const char *iter = string;
  char *temp_str;
  unsigned long count;
  int precedence;
  int paren_flag = 0;
  struct stackSet *stackSet = init_stackSet();

  if (stackSet == NULL)
  {
    error_code = MALLOC_ERR;
    return NULL;
  }

  while (1)
  {
    switch (*iter)
    {
    case '\0':
      goto end_read_loop;
    case ' ':
      break;
    case '(':
      count = stack_count(stackSet->expStack) + 1;
      if (stack_push(stackSet->ctStack, &count))
      {
        error_code = MALLOC_ERR;
        cleanup_stackSet(stackSet);
        return NULL;
      }
      paren_flag = 1;
      break;
    case ')':
      count = stack_pop(stackSet->ctStack).ul;
      while (stack_count(stackSet->expStack) > count)
        if (evaluate_one(stackSet->expStack, stack_pop(stackSet->opStack).ch))
        {
          cleanup_stackSet(stackSet);
          return NULL;
        }
      break;
    case '+':
    case '-':
      // if expected to find a number
      if (stack_count(stackSet->expStack) == stack_count(stackSet->opStack))
        goto handle_digit;
    case '*':
    case '/':
      if (paren_flag)
      {
        paren_flag = 0;
      }
      else
      {
        precedence = get_op_precedence(*iter);
        while (precedence <= get_op_precedence(stack_first(stackSet->opStack).ch))
        {
          // if in parentheses, cannot go across open paren
          if (stack_count(stackSet->ctStack) &&
              stack_count(stackSet->expStack) <= stack_first(stackSet->ctStack).ul)
            break;
          if (evaluate_one(stackSet->expStack, stack_pop(stackSet->opStack).ch))
          {
            cleanup_stackSet(stackSet);
            return NULL;
          }
        }
      }
      if (stack_push(stackSet->opStack, (void*)iter))
      {
        error_code = MALLOC_ERR;
        cleanup_stackSet(stackSet);
        return NULL;
      }
      break;
    default:
      if (isdigit(*iter))
      {
handle_digit:
        temp_str = get_num(&iter);
        if (temp_str == NULL)
        {
          error_code = MALLOC_ERR;
          cleanup_stackSet(stackSet);
          return NULL;
        }
        temp_exp = malloc(sizeof (struct expression));
        if (temp_exp == NULL)
        {
          error_code = MALLOC_ERR;
          cleanup_stackSet(stackSet);
          return NULL;
        }
        temp_exp->type = DIGIT;
        temp_exp->dig = temp_str;
        temp_exp->op = '\0';
        if (stack_push(stackSet->expStack, temp_exp))
        {
          error_code = MALLOC_ERR;
          cleanup_stackSet(stackSet);
          return NULL;
        }

        // get_num already lead iter to the next character, so don't increment
        continue;
      }
      else
      {
        error_code = INVALID_INPUT;
        cleanup_stackSet(stackSet);
        return NULL;
      }
      break;
    }

    iter++;
  }
end_read_loop:

  while (stack_count(stackSet->opStack))
    if (evaluate_one(stackSet->expStack, stack_pop(stackSet->opStack).ch))
    {
      cleanup_stackSet(stackSet);
      return NULL;
    }

  if (stack_count(stackSet->expStack) != 1)
  {
    error_code = INVALID_INPUT;
    cleanup_stackSet(stackSet);
    return NULL;
  }

  if (stack_count(stackSet->expStack) != 1 ||
      stack_count(stackSet->opStack) != 0  ||
      stack_count(stackSet->ctStack) != 0)
  {
    error_code = INVALID_INPUT;
    cleanup_stackSet(stackSet);
    return NULL;
  }

  temp_exp = stack_pop(stackSet->expStack).exp;
  cleanup_stackSet(stackSet);

  return temp_exp;
}

struct expression * expression_parser_postfix(const char *string)
{
  Stack expStack;
  const char *iter = string;
  char *temp_str;
  struct expression *temp_exp;

  while (1)
  {
    switch (*iter)
    {
    case ' ':
    case '(':
    case ')':
      continue;
    case '\0':
      goto end_read_loop;
    case '+':
    case '-':
      if (isdigit(*(iter + 1)))
        goto handle_digit;
    case '*':
    case '/':
      if (evaluate_one(expStack, *iter))
      {
        cleanup_stack(expStack);
        return NULL;
      }

      break;
    default:
      if (isdigit(*iter))
      {
handle_digit:
        temp_str = get_num(&iter);
        if (temp_str == NULL)
        {
          error_code = MALLOC_ERR;
          cleanup_stack(expStack);
          return NULL;
        }
        temp_exp = malloc(sizeof (struct expression));
        if (temp_exp == NULL)
        {
          error_code = MALLOC_ERR;
          cleanup_stack(expStack);
          return NULL;
        }
        temp_exp->type = DIGIT;
        temp_exp->dig = temp_str;
        temp_exp->op = '\0';
        if (stack_push(expStack, temp_exp))
        {
          error_code = MALLOC_ERR;
          cleanup_stack(expStack);
          return NULL;
        }

        // get_num already lead iter to the next character, so don't increment
        continue;
      }
      else
      {
        error_code = INVALID_INPUT;
        cleanup_stack(expStack);
        return NULL;
      }
      break;
    }

    iter++;
  }
end_read_loop:

  if (stack_count(expStack) != 1)
  {
    error_code = INVALID_INPUT;
    cleanup_stack(expStack);
    return NULL;
  }

  temp_exp = stack_pop(expStack).exp;

  cleanup_stack(expStack);
  return temp_exp;
}

static char * get_num(const char **strptr)
{
  size_t cap = 1;
  char *string = malloc(cap), *cavity = string, *terminal = string + cap;
  char *temp;
  int encountered_dot = 0;
  int has_sign = 0;
  int in_dig = 0;
  int is_valid = 1;

  if (string == NULL)
    return NULL;

  while (1)
  {
    switch (**strptr)
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
      if (isdigit(**strptr))
        in_dig = 1;
      else
        is_valid = 0;
    }

    if (is_valid)
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
        cavity = string + cap;
        terminal = string + (cap *= 2);
      }

      *cavity++ = *(*strptr)++;
    }
    else
      break;
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
    cavity = string + cap;
  }
  
  *cavity = '\0';

  return string;
}

static void cleanup_stackSet(struct stackSet *this)
{
    cleanup_stack(this->expStack);
    cleanup_stack(this->opStack);
    cleanup_stack(this->ctStack);
    free(this);
}

static struct stackSet * init_stackSet(void)
{
  struct stackSet *ret = malloc(sizeof (struct stackSet));
  if (ret == NULL)
    return NULL;

  ret->expStack = init_stack(ST_EXP);
  ret->opStack = init_stack(ST_CHAR);
  ret->ctStack = init_stack(ST_UL);

  if (ret->expStack == NULL || ret->opStack == NULL || ret->ctStack == NULL)
  {
    cleanup_stackSet(ret);
    return NULL;
  }

  error_code = SUCCESS;
  return ret;
}

static int evaluate_one(Stack expStack, char op)
{
  struct expression *res = malloc(sizeof (struct expression));

  if (res == NULL)
  {
    error_code = MALLOC_ERR;
    return 1;
  }
  if (stack_count(expStack) < 2)
  {
    error_code = INVALID_INPUT;
    return 1;
  }

  res->type = EXPRESSION;

  // right-hand-side
  res->exp[1] = stack_pop(expStack).exp;
  // left-hand-side
  res->exp[0] = stack_pop(expStack).exp;
  res->op = op;

  stack_push(expStack, res);

  return 0;
}

int get_op_precedence(char op)
{
  switch (op)
  {
  case 0:
    return 0;
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  default:
    return 100;
  }
}
