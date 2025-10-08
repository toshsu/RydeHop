#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

typedef struct {
    LinkedList *list;
} Stack;

Stack* create_stack();
void push(Stack *stack, void *data);
void* pop(Stack *stack);
int is_stack_empty(Stack *stack);
void free_stack(Stack *stack);

#endif