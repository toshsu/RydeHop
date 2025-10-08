#include "linked_list.h"
#include <stdlib.h>

LinkedList* create_linked_list() {
    LinkedList *list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_insert(LinkedList *list, void *data) {
    ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
    new_node->data = data;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
}

void* list_remove(LinkedList *list, void *data, int (*compare)(void*, void*)) {
    ListNode *current = list->head;
    ListNode *prev = NULL;
    
    while (current != NULL) {
        if (compare(current->data, data) == 0) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            void *removed_data = current->data;
            free(current);
            list->size--;
            return removed_data;
        }
        prev = current;
        current = current->next;
    }
    return NULL;
}

void* list_find(LinkedList *list, void *data, int (*compare)(void*, void*)) {
    ListNode *current = list->head;
    while (current != NULL) {
        if (compare(current->data, data) == 0) {
            return current->data;
        }
        current = current->next;
    }
    return NULL;
}

void free_linked_list(LinkedList *list) {
    ListNode *current = list->head;
    while (current != NULL) {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}