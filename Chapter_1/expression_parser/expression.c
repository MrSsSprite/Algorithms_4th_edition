#include "expression.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_op_precedence(char op);

struct _string { char *st, *cav, *term; };
inline static int _string_resize(struct _string *this, size_t new_cap);
inline static int _exptostr(const struct expression *exp, struct _string *str);
inline static int _exptostr_postfix(const struct expression *exp, struct _string *str);

void cleanup_expression(struct expression *exp)
{
  struct expression *ptr;

  if (exp->type == EXPRESSION)
  {
    cleanup_expression(exp->exp[0]);
    cleanup_expression(exp->exp[1]);
  }
  else
    free(exp->dig);

  free(exp);
}

char * expression_to_string(struct expression *exp)
{
  struct _string ret;
  ret.st = malloc(1);
  if (ret.st == NULL)
    return NULL;
  ret.cav = ret.st;
  ret.term = ret.st + 1;

  if (_exptostr(exp, &ret))
  {
    free(ret.st);
    return NULL;
  }

  if (ret.cav == ret.term && _string_resize(&ret, ret.term - ret.st + 1))
  {
    free(ret.st);
    return NULL;
  }
  *ret.cav = '\0';

  return ret.st;
}

char * expression_to_string_postfix(Expression exp)
{
  struct _string ret;
  ret.st = malloc(1);
  if (ret.st == NULL)
    return NULL;
  ret.cav = ret.st;
  ret.term = ret.st + 1;

  if (_exptostr_postfix(exp, &ret))
  {
    free(ret.st);
    return NULL;
  }

  if (ret.cav == ret.term && _string_resize(&ret, ret.term - ret.st + 1))
  {
    free(ret.st);
    return NULL;
  }
  *ret.cav = '\0';

  return ret.st;
}

long expression_evaluate_long(Expression exp)
{
  long lhs, rhs;
  
  if (exp->type == EXPRESSION)
  {
    lhs = expression_evaluate_long(exp->exp[0]);
    rhs = expression_evaluate_long(exp->exp[1]);
    switch (exp->op)
    {
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    default:
      return 0;
    }
  }
  else
  {
    if (sscanf(exp->dig, "%ld", &lhs) != 1)
      return 0;
    else
      return lhs;
  }
}

double expression_evaluate_double(Expression exp)
{
  double lhs, rhs;
  
  if (exp->type == EXPRESSION)
  {
    lhs = expression_evaluate_long(exp->exp[0]);
    rhs = expression_evaluate_long(exp->exp[1]);
    switch (exp->op)
    {
    case '+':
      return lhs + rhs;
    case '-':
      return lhs - rhs;
    case '*':
      return lhs * rhs;
    case '/':
      return lhs / rhs;
    default:
      return 0;
    }
  }
  else
  {
    if (sscanf(exp->dig, "%lf", &lhs) != 1)
      return 0;
    else
      return lhs;
  }
}

inline static int _string_resize(struct _string *this, size_t new_cap)
{
  char *temp;
  size_t size = this->cav - this->st;

  if (new_cap == 0)
  {
    free(this->st);
    this->st = this->cav = this->term = NULL;
    return 0;
  }
  if (new_cap < size)
    size = new_cap;

  temp = realloc(this->st, size);
  if (temp == NULL)
    return 1;

  this->st = temp;
  this->cav = temp + size;
  this->term = temp + new_cap;

  return 0;
}

inline static int _string_expand(struct _string *this)
{ return _string_resize(this, this->st == NULL ? 1 : (this->term - this->st) * 2); }

inline static int _exptostr(const struct expression *exp, struct _string *str)
{
  int status;

  if (exp->type == EXPRESSION)
  {
    int need_paren;

    // concatenate lhs
    if (exp->exp[0]->type == EXPRESSION &&
        get_op_precedence(exp->exp[0]->op) < get_op_precedence(exp->op))
      need_paren = 1;
    else
      need_paren = 0;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = '(';
    }
    if ((status = _exptostr(exp->exp[0], str)))
      return status;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = ')';
    }

    // concatenate operator
    while (str->term - str->cav < 3)
      if ((status = _string_expand(str)))
        return status;
    *str->cav++ = ' ';
    *str->cav++ = exp->op;
    *str->cav++ = ' ';

    // concatenate rhs
    if (exp->exp[1]->type == EXPRESSION &&
        get_op_precedence(exp->exp[1]->op) <= get_op_precedence(exp->op))
      need_paren = 1;
    else
      need_paren = 0;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = '(';
    }
    if ((status = _exptostr(exp->exp[1], str)))
      return status;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = ')';
    }
  }
  else  // exp->type == DIGIT
  {
    for (const char *iter = exp->dig; *iter != '\0'; iter++)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = *iter;
    }
  }

  return 0;
}

inline static int _exptostr_postfix(const struct expression *exp, struct _string *str)
{
  int status;

  if (exp->type == EXPRESSION)
  {
    int need_paren;

    // concatenate lhs
    if (exp->exp[0]->type == EXPRESSION &&
        get_op_precedence(exp->exp[0]->op) < get_op_precedence(exp->op))
      need_paren = 1;
    else
      need_paren = 0;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = '(';
    }
    if ((status = _exptostr_postfix(exp->exp[0], str)))
      return status;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = ')';
    }

    // concatenate separate space
    if (str->cav == str->term && _string_expand(str))
      return 1;
    *str->cav++ = ' ';

    // concatenate rhs
    if (exp->exp[1]->type == EXPRESSION &&
        get_op_precedence(exp->exp[1]->op) <= get_op_precedence(exp->op))
      need_paren = 1;
    else
      need_paren = 0;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = '(';
    }
    if ((status = _exptostr_postfix(exp->exp[1], str)))
      return status;
    if (need_paren)
    {
      if (str->cav == str->term && ((status = _string_expand(str))))
          return status;
      *str->cav++ = ')';
    }

    // concatenate operator
    while (str->term - str->cav < 2)
      if ((status = _string_expand(str)))
        return status;
    *str->cav++ = ' ';
    *str->cav++ = exp->op;
  }
  else  // exp->type == DIGIT
  {
    for (const char *iter = exp->dig; *iter != '\0'; iter++)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = *iter;
    }
  }

  return 0;
}
