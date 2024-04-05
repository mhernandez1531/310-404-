#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include <ctype.h>
#include <string.h>
#include "int_stack.h"
#include "variables.h" 

token_t* intialize_token(token_type_t type, const char* text){
    token_t* newToken = (token_t*)malloc(sizeof(token_t));
    if (newToken == NULL) {
        
        return NULL;
    }
}

token_type_t get_token_type(const char* token){
    if (*token == '+' || *token == '-' || *token == '*' || *token == '/' || *token == '.') {
        return OPERATOR;
    } else if (*token == ';' || *token == ':'){
        return SYMBOL;
    } else if (isdigit((unsigned char)*token)){
        const char* p = token + 1; 
        while (*p) {
            if (!isdigit((unsigned char)*p)) {
                
                return WORD;
            }
            p++;
        }
        return NUMBER;
    } else {
        return WORD;
    }
}

const char* token_type_to_string(token_type_t type) {
    switch (type) {
        case OPERATOR:
            return "OPERATOR";
        case NUMBER:
            return "NUMBER";
        case SYMBOL:
            return "SYMBOL";
        case WORD:
            return "WORD";
        default:
            return "ILLEGAL";
    }
}

void separate_token(int_stack_t *stk, char *text) {
    const char *space = " ";
    char *token;
    char *rest = text;

    while ((token = strtok_r(rest, space, &rest))) {
        token_type_t type = get_token_type(token);
        //printf("Token: %s, Type: %s\n", token, token_type_to_string(type));
        if (type == NUMBER) {
            int_stack_push(stk, atoi(token));
        } else if (type == OPERATOR) {
            int top_value;
            if (stk->size > 1){     
                if (strcmp(token, "+") == 0) {        
                    int_stack_add(stk);
                } else if (strcmp(token, "-") == 0) {
                    int_stack_subtraction(stk);
                } else if (strcmp(token, "*") == 0){
                    int_stack_multiply(stk);
                } else if (strcmp(token, "/mod")==0){
                    int_stack_divmod(stk);
                } else if (strcmp(token, ".")==0){
                    int_stack_pop(stk, &top_value);
                } else {
                    int_stack_divide(stk);
                } 
            } else {
                int_stack_pop(stk, &top_value);
                printf("Stack underflow\n");
                
                //exit(EXIT_FAILURE);
            } 
        } else if (type == WORD){
            int top_value;
            if (strcmp(token, "over")==0){
                int_stack_over(stk);
            } else if (strcmp(token, "drop")==0){
                int_stack_pop(stk, &top_value);
            } else if (strcmp(token, "rot")==0){
                int_stack_rot(stk);
            } else if (strcmp(token, "dup")==0){
                int_stack_dup(stk);
            } else if (strcmp(token, "swap")==0){
                int_stack_swap(stk);
            } else if (strcmp(token, "2swap")==0){
                int_stack_2swap(stk);
            } else if (strcmp(token, "2dup")==0){
                int_stack_2dup(stk);
            } else if (strcmp(token, "2over")==0){
                int_stack_2over(stk);
            } else if (strcmp(token, "2drop")==0){
                int_stack_2drop(stk);
            } else if (strcmp(token, "mod")==0){
                int_stack_mod(stk);
            } else {
                printf("unknown\n");
            }
        }
    }
}

token_t* initialize_token(token_type_t type, const char* text){
    token_t* newToken = (token_t*)malloc(sizeof(token_t));
    if (newToken == NULL) {
        return NULL;
    }
    newToken->type = type; // Set type
    newToken->text = strdup(text); // Duplicate and assign the text
    return newToken;
}
