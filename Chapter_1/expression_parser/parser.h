#ifndef PARSER_H
#define PARSER_H

typedef struct expression* Expression;

void cleanup_expression(Expression exp);
Expression expression_parser(const char *string);
char * expression_to_string(Expression exp);
char * expression_to_string_postfix(Expression exp);
/**
 * @brief     return the error type of last expression parse run
 * @return    0: SUCCESS,
 *            1: MALLOC_ERR, 2: INVALID_INPUT
 */
int exp_parser_error(void);

#endif
