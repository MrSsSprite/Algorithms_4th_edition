#ifndef EXPRESSION_H
#define EXPRESSION_H

struct expression
{
  union { struct expression *exp[2];
          char *dig;};
  enum { EXPRESSION, DIGIT } type;
  char op;
};

void cleanup_expression(struct expression *exp);

#endif
