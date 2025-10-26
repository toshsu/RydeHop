/*#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end_of_word;
    void *data;
} TrieNode;

typedef struct {
    TrieNode *root;
} Trie;

Trie* create_trie();
void trie_insert(Trie *trie, char *key, void *data);
void* trie_search(Trie *trie, char *key);
void free_trie(Trie *trie);

#endif
*/
#ifndef TRIE_H
#define TRIE_H

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int is_end_of_word;
    void *data;
} TrieNode;

typedef struct {
    TrieNode *root;
} Trie;

Trie* create_trie();
void trie_insert(Trie *trie, char *key, void *data);
void* trie_search(Trie *trie, char *key);
void free_trie(Trie *trie);

#endif
