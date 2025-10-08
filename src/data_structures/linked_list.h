#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include "../src/data_structures/linked_list.h"

typedef struct ListNode
{
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct
{
    ListNode *head;
    int size;
} LinkedList;

LinkedList *create_linked_list();
void list_insert(LinkedList *list, void *data);
void *list_remove(LinkedList *list, void *data, int (*compare)(void *, void *));
void *list_find(LinkedList *list, void *data, int (*compare)(void *, void *));
void free_linked_list(LinkedList *list);

#endif