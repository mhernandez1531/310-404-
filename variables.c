// variables.c
#include "variables.h"
#include <stdlib.h>
#include <string.h>

void var_list_init(VarNode** head) {
    *head = NULL;
}

bool var_list_add(VarNode** head, const char* name, int value, bool isConstant) {
    VarNode* newNode = malloc(sizeof(VarNode));
    if (!newNode) return false;

    newNode->name = strdup(name); // Copy the name
    newNode->value = value;
    newNode->isConstant = isConstant;
    newNode->next = *head;
    *head = newNode;

    return true;
}

bool var_list_set(VarNode* head, const char* name, int value) {
    VarNode* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && !current->isConstant) {
            current->value = value;
            return true;
        }
        current = current->next;
    }
    return false;
}

VarNode* var_list_find(VarNode* head, const char* name) {
    VarNode* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void var_list_destroy(VarNode* head) {
    VarNode* current = head;
    VarNode* next;

    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }
}


