// int_stack.c

#include "int_stack.h"

#include <stdlib.h>
#include <stdio.h>

void int_stack_init(int_stack_t *stk, int capacity) {
    SLIST_INIT(&stk->head);
    stk->size = 0;
    stk->capacity = capacity;
}

int int_stack_push(int_stack_t *stk, int value) {
    if (stk->size >= stk->capacity) {
        printf("Stack is at full capacity.\n");
        return 0; // fail
    }

    int_entry_t *newEntry = malloc(sizeof(int_entry_t));
    if (newEntry) {
        newEntry->value = value;
        SLIST_INSERT_HEAD(&stk->head, newEntry, entries);
        stk->size++;
        return 1; //success
    }
    return 0; // fail
}

int int_stack_pop(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        int value = entry->value;
        SLIST_REMOVE_HEAD(&stk->head, entries);
        free(entry);
        stk->size--;
        *top_value = value;
        return 1; // success
    }
    return 0; // fail
}

int int_stack_top(int_stack_t *stk, int *top_value) {
    int_entry_t *entry = SLIST_FIRST(&stk->head);
    if (entry) {
        *top_value = entry->value;
        return 1; // success
    }
    return 0; // fail
}

/* Functions for FORTH langauge stack operators */

int int_stack_dup(int_stack_t *stk) {
    if (stk->size < 1)
        return 0;
    int top_value;
    int_stack_top(stk, &top_value);
    return int_stack_push(stk, top_value); // success only if last operation succeeds
}

int int_stack_swap(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    int_stack_push(stk, top_value);
    return int_stack_push(stk, next_to_top_value); // success only if last operation succeeds
}

/* Example of how to create a binary operator that works o top two elements (if present) */


//arithmetic

int int_stack_add(int_stack_t *stk) {
    if (stk->size < 2)
        return 0;
    int top_value, next_to_top_value;
    int_stack_pop(stk, &top_value);
    int_stack_pop(stk, &next_to_top_value);
    return int_stack_push(stk, top_value + next_to_top_value);
}

int int_stack_subtraction(int_stack_t *stk){
	if(stk ->size < 2)
		return 0;
	int top_value, next_to_top_value;
	int_stack_pop(stk, &top_value);
	int_stack_pop(stk, &next_to_top_value);
	return int_stack_push(stk, top_value - next_to_top_value);
}

int int_stack_multiply(int_stack_t *stk){
	if(stk->size < 2)
		return 0; 
	int top_value, next_to_top_value;
	int_stack_pop(stk, &top_value);
	int_stack_pop(stk, &next_to_top_value);
	return int_stack_push(stk, top_value * next_to_top_value);
}

int int_stack_divide(int_stack_t *stk) {
	if (stk->size < 2)
		return 0;
	int top_value, next_to_top_value;
	int_stack_pop(stk, &top_value);
	int_stack_pop(stk, &next_to_top_value);
	return int_stack_push(stk, top_value / next_to_top_value);
}

int int_stack_divmod(int_stack_t *stk) {
	if (stk->size < 2)
		return 0;
	int divisor, dividend;
	int_stack_pop(stk, &divisor);
	int_stack_pop(stk, &dividend);
	int remainder = dividend % divisor;
	int quotient = dividend / divisor;
	int_stack_push(stk, remainder);
	return int_stack_push(stk, quotient);
}

int int_stack_mod(int_stack_t *stk) {
	if(stk->size < 2)
		return 0;
	int divisor, dividend;
	int_stack_pop(stk, &divisor);
	int_stack_pop(stk, &dividend);	
	return int_stack_push(stk, dividend % divisor);
}

//stack manipulation 
int int_stack_over(int_stack_t *stk) {
	if(stk->size < 2)
		return 0;
	int top_value, next_to_top_value;
	int_stack_pop(stk, &top_value);
	int_stack_pop(stk, &next_to_top_value);
	int_stack_push(stk, next_to_top_value);
	int_stack_push(stk, top_value);
	return int_stack_push(stk, next_to_top_value);
}

//int int_stack_rot(int_stack_t *stk) {
//	if(stk->size < 3) 
//		return 0;//error code for not enough elements 
//	int top, middle, bottom;
//	int stack_pop(stk, &top);
//	int stack_pop(stk, &middle);
//	int stack_pop(stk, &bottom);
//	int stack_push(stk, middle);
//	int stack_push(stk, top);
//	return int_stack_push(stk, bottom);
//}

int int_stack_rot(int_stack_t *stk){
	if(stk->size < 2)
		return 0;
	int v1, v2, v3;
	int_stack_pop(stk, &v1);
	int_stack_pop(stk, &v2);
	int_stack_pop(stk, &v3);
	int_stack_push(stk, v2);
	int_stack_push(stk, v1);
	return int_stack_push(stk, v3);
}
int int_stack_drop(int_stack_t *stk){
	if(stk->size == 0)
		return -1;//error code for stack underflow 
	int top_value;
	return int_stack_pop(stk, &top_value);
}

//double element operations 

int int_stack_2swap(int_stack_t *stk) {
	if(stk->size < 4)
		return 0;// error code for not enough elements 
	int d1_top, d1_bottom, d2_top, d2_bottom;
	int_stack_pop(stk, &d1_top);
	int_stack_pop(stk, &d1_bottom);
	int_stack_pop(stk, &d2_top);
	int_stack_pop(stk, &d2_bottom);
	int_stack_push(stk, d1_bottom);
	int_stack_push(stk, d1_top);
	int_stack_push(stk, d2_bottom);
	return int_stack_push(stk, d2_top);
	
}

int int_stack_2dup(int_stack_t *stk) {
	if(stk->size < 2)
		return 0; // error code for not enough elements
	int s1, s2;
	int_stack_pop(stk, &s1);
	int_stack_pop(stk, &s2);
	int_stack_push(stk, s2);
	int_stack_push(stk, s1);
	int_stack_push(stk, s2);
	return int_stack_push(stk, s1); 
}

int int_stack_2over(int_stack_t *stk) {
	if (stk->size < 4)
		return 0; // Error code for not enough elements
	int s1, s2, s3, s4;
	int_stack_pop(stk, &s1);
	int_stack_pop(stk, &s2);
	int_stack_pop(stk, &s3);
	int_stack_pop(stk, &s4);
	int_stack_push(stk, s4);
	int_stack_push(stk, s3);
	int_stack_push(stk, s2);
	int_stack_push(stk, s1);
	int_stack_push(stk, s4);
	return int_stack_push(stk, s3);
}

int int_stack_2drop(int_stack_t *stk) {
	if (stk->size < 2)
		return 0; // Error code for not enough elements
	int top_value;
	int_stack_pop(stk, &top_value);
	int_stack_pop(stk, &top_value);
	return 0; // Success
}



void int_stack_print(int_stack_t *stk, FILE *file) {
    int_entry_t *entry;
    int pos = 0;
    if (stk->size == 0) {
        fprintf(file, "empty stack\n");
    }

    SLIST_FOREACH(entry, &stk->head, entries) {
        fprintf(file, "%d: %d\n", pos, entry->value);
        pos++;
    }
    printf("\n");
}

int int_stack_size(int_stack_t* stk) {
    return stk->size;
}

int int_stack_capacity(int_stack_t* stk) {
    return stk->capacity;
}


