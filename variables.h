// variables.h
#ifndef VARIABLES_H
#define VARIABLES_H

#include <stdbool.h>

typedef struct VarNode {
    char* name;
    int value;
    bool isConstant;
    struct VarNode* next;
} VarNode;

void var_list_init(VarNode** head);
bool var_list_add(VarNode** head, const char* name, int value, bool isConstant);
bool var_list_set(VarNode* head, const char* name, int value);
VarNode* var_list_find(VarNode* head, const char* name);
void var_list_destroy(VarNode* head);

#endif // VARIABLES_H


