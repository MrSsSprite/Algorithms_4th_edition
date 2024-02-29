#ifndef PARSER_H
#define PARSER_H

typedef struct expression* Expression;

void cleanup_expression(Expression exp);
char * expression_to_string(Expression exp);
char * expression_to_string_postfix(Expression exp);
long expression_evaluate_long(Expression exp);
double expression_evaluate_double(Expression exp);

Expression expression_parser(const char *string);
Expression expression_parser_postfix(const char *string);
/**
 * @brief     return the error type of last expression parse run
 * @return    0: SUCCESS,
 *            1: MALLOC_ERR, 2: INVALID_INPUT
 */
int exp_parser_error(void);

#endif
