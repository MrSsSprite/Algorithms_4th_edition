#ifndef PARSER_H
#define PARSER_H

typedef struct expression* Expression;

void cleanup_expression(Expression exp);
Expression expression_parser(const char *string);
char * expression_to_string(Expression exp);
char * expression_to_string_postfix(Expression exp);

#endif
