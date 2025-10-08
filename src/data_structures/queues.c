#include "queues.h"
#include <stdlib.h>

Queue* create_queue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    queue->list = create_linked_list();
    return queue;
}

void enqueue(Queue *queue, void *data) {
    list_insert(queue->list, data);
}

void* dequeue(Queue *queue) {
    if (queue->list->head == NULL) return NULL;
    
    // Find the last node
    ListNode *current = queue->list->head;
    ListNode *prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    
    void *data = current->data;
    if (prev == NULL) {
        queue->list->head = NULL;
    } else {
        prev->next = NULL;
    }
    free(current);
    queue->list->size--;
    return data;
}

int is_queue_empty(Queue *queue) {
    return queue->list->head == NULL;
}

void free_queue(Queue *queue) {
    free_linked_list(queue->list);
    free(queue);
}