#include "stack.h"
#include <stdlib.h>

Stack* create_stack() {
    Stack *stack = (Stack*)malloc(sizeof(Stack));
    stack->list = create_linked_list();
    return stack;
}

void push(Stack *stack, void *data) {
    list_insert(stack->list, data);
}

void* pop(Stack *stack) {
    if (stack->list->head == NULL) return NULL;
    
    ListNode *node = stack->list->head;
    void *data = node->data;
    stack->list->head = node->next;
    free(node);
    stack->list->size--;
    return data;
}

int is_stack_empty(Stack *stack) {
    return stack->list->head == NULL;
}

void free_stack(Stack *stack) {
    free_linked_list(stack->list);
    free(stack);
}