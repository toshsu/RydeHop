#ifndef BST_H
#define BST_H

typedef struct BSTNode {
    void *data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

typedef struct {
    BSTNode *root;
    int (*compare)(void*, void*);
} BST;

BST* create_bst(int (*compare)(void*, void*));
void bst_insert(BST *tree, void *data);
void* bst_search(BST *tree, void *data);
void free_bst(BST *tree);

#endif