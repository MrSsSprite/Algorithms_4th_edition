#include "expression.h"
#include "parser.h"

#include <stdlib.h>
#include <string.h>

int get_op_precedence(char op);

struct _string { char *st, *cav, *term; };
inline static int _string_resize(struct _string *this, size_t new_cap);
static int _exptostr(struct expression *exp, struct _string *str);
static int _exptostr_postfix(struct expression *exp, struct _string *str);

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
{ return _string_resize(this, this->st == NULL ? 3 : (this->term - this->st) * 2); }

static int _exptostr(struct expression *exp, struct _string *str)
{
  char *iter;
  int has_lower_precedence = 0;

  if (exp->type == EXPRESSION)
  {
    // left expression
    // check precedence of subexpression
    if (exp->exp[0]->type == EXPRESSION &&
        get_op_precedence(exp->exp[0]->op) < get_op_precedence(exp->op))
      has_lower_precedence = 1;
    else
      has_lower_precedence = 0;
    // print content
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = '(';
    }
    if (_exptostr(exp->exp[0], str))
      return 1;
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = ')';
    }

    // operator
    while (str->term - str->cav < 3)
      if (_string_expand(str))
        return 1;
    *str->cav++ = ' ';
    *str->cav++ = exp->op;
    *str->cav++ = ' ';

    // right expression
    // check precedence of subexpression
    if (exp->exp[1]->type == EXPRESSION &&
        get_op_precedence(exp->exp[1]->op) <= get_op_precedence(exp->op))
      has_lower_precedence = 1;
    else
      has_lower_precedence = 0;
    // print content
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = '(';
    }
    if (_exptostr(exp->exp[1], str))
      return 1;
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = ')';
    }
  }
  else
  {
    while (str->term - str->cav < strlen(exp->dig))
      if (_string_expand(str))
        return 1;

    iter = exp->dig;
    while (*iter != '\0')
      *str->cav++ = *iter++;
  }

  return 0;
}

static int _exptostr_postfix(struct expression *exp, struct _string *str)
{
  char *iter;
  int has_lower_precedence = 0;

  if (exp->type == EXPRESSION)
  {
    // left expression
    // check precedence of subexpression
    if (exp->exp[0]->type == EXPRESSION &&
        get_op_precedence(exp->exp[0]->op) < get_op_precedence(exp->op))
      has_lower_precedence = 1;
    else
      has_lower_precedence = 0;
    // print content
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = '(';
    }
    if (_exptostr_postfix(exp->exp[0], str))
      return 1;
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = ')';
    }

    // separate lhs and rhs
    while (str->term - str->cav < 1)
      if (_string_expand(str))
        return 1;
    *str->cav++ = ' ';

    // right expression
    // check precedence of subexpression
    if (exp->exp[1]->type == EXPRESSION &&
        get_op_precedence(exp->exp[1]->op) <= get_op_precedence(exp->op))
      has_lower_precedence = 1;
    else
      has_lower_precedence = 0;
    // print content
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = '(';
    }
    if (_exptostr_postfix(exp->exp[1], str))
      return 1;
    if (has_lower_precedence)
    {
      if (str->cav == str->term && _string_expand(str))
        return 1;
      *str->cav++ = ')';
    }

    // operator
    while (str->term - str->cav < 2)
      if (_string_expand(str))
        return 1;
    *str->cav++ = ' ';
    *str->cav++ = exp->op;
  }
  else
  {
    while (str->term - str->cav < strlen(exp->dig))
      if (_string_expand(str))
        return 1;

    iter = exp->dig;
    while (*iter != '\0')
      *str->cav++ = *iter++;
  }

  return 0;
}
