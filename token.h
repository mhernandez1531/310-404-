//this is an interface
#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <stdio.h>
#include "int_stack.h"

typedef enum token_type_t {
    NUMBER,
    OPERATOR,
    SYMBOL,
    WORD,
    ILLEGAL,
    VARIABLE,
    CONSTANT

} token_type_t;

typedef struct token_t {
    token_type_t type;
    char* text;
} token_t;

extern void separate_token(int_stack_t *stk, char *text);
extern token_type_t get_token_type(const char* token);
extern token_t* intialize_token(token_type_t type, const char* text);
extern void print_forth(int_stack_t *stk);

#endif
