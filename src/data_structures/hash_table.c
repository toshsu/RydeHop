#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

HashTable* create_hash_table() {
    HashTable *table = (HashTable*)malloc(sizeof(HashTable));
    table->buckets = (LinkedList**)malloc(TABLE_SIZE * sizeof(LinkedList*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->buckets[i] = create_linked_list();
    }
    table->size = TABLE_SIZE;
    return table;
}

unsigned int hash_function(char *key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

int hash_entry_compare(void *a, void *b) {
    HashEntry *entry_a = (HashEntry*)a;
    HashEntry *entry_b = (HashEntry*)b;
    return strcmp(entry_a->key, entry_b->key);
}

void hash_insert(HashTable *table, char *key, void *data) {
    unsigned int index = hash_function(key);
    HashEntry *entry = (HashEntry*)malloc(sizeof(HashEntry));
    entry->key = strdup(key);
    entry->data = data;
    
    // Remove existing entry if present
    HashEntry search_entry = {key, NULL};
    list_remove(table->buckets[index], &search_entry, hash_entry_compare);
    
    list_insert(table->buckets[index], entry);
}

void* hash_get(HashTable *table, char *key) {
    unsigned int index = hash_function(key);
    HashEntry search_entry = {key, NULL};
    HashEntry *found = (HashEntry*)list_find(table->buckets[index], &search_entry, hash_entry_compare);
    return found ? found->data : NULL;
}

void hash_remove(HashTable *table, char *key) {
    unsigned int index = hash_function(key);
    HashEntry search_entry = {key, NULL};
    HashEntry *removed = (HashEntry*)list_remove(table->buckets[index], &search_entry, hash_entry_compare);
    if (removed) {
        free(removed->key);
        free(removed);
    }
}

void free_hash_table(HashTable *table) {
    for (int i = 0; i < table->size; i++) {
        ListNode *current = table->buckets[i]->head;
        while (current != NULL) {
            HashEntry *entry = (HashEntry*)current->data;
            free(entry->key);
            free(entry);
            current = current->next;
        }
        free_linked_list(table->buckets[i]);
    }
    free(table->buckets);
    free(table);
}