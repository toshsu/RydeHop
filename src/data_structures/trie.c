#include "trie.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

Trie* create_trie() {
    Trie *trie = (Trie*)malloc(sizeof(Trie));
    trie->root = (TrieNode*)calloc(1, sizeof(TrieNode));
    return trie;
}

int char_to_index(char c) {
    c = tolower(c);
    if (c >= 'a' && c <= 'z') return c - 'a';
    return -1;
}

void trie_insert(Trie *trie, char *key, void *data) {
    TrieNode *current = trie->root;
    
    for (int i = 0; key[i] != '\0'; i++) {
        int index = char_to_index(key[i]);
        if (index == -1) continue;
        
        if (current->children[index] == NULL) {
            current->children[index] = (TrieNode*)calloc(1, sizeof(TrieNode));
        }
        current = current->children[index];
    }
    
    current->is_end_of_word = 1;
    current->data = data;
}

void* trie_search(Trie *trie, char *key) {
    TrieNode *current = trie->root;
    
    for (int i = 0; key[i] != '\0'; i++) {
        int index = char_to_index(key[i]);
        if (index == -1 || current->children[index] == NULL) {
            return NULL;
        }
        current = current->children[index];
    }
    
    return (current != NULL && current->is_end_of_word) ? current->data : NULL;
}

void free_trie_recursive(TrieNode *node) {
    if (node == NULL) return;
    
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        free_trie_recursive(node->children[i]);
    }
    
    free(node);
}

void free_trie(Trie *trie) {
    free_trie_recursive(trie->root);
    free(trie);
}