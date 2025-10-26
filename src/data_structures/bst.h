/*#ifndef BST_H
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
*/
#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

// =============================
// Binary Search Tree Node
// =============================
typedef struct BSTNode {
    void *data;                  // Pointer to any type of data (e.g., Ride, User, etc.)
    struct BSTNode *left;        // Left child
    struct BSTNode *right;       // Right child
} BSTNode;

// =============================
// Binary Search Tree Structure
// =============================
typedef struct {
    BSTNode *root;               // Root node of the tree
    int (*compare)(void*, void*); // Comparison function to decide ordering
} BST;

// =============================
// Function Declarations
// =============================

// Creates a new BST
BST* create_bst(int (*compare)(void*, void*));

// Inserts data into the BST
void bst_insert(BST *tree, void *data);

// Searches for a node containing 'data' in the BST
void* bst_search(BST *tree, void *data);

// Traverses the BST in-order (sorted order) and applies callback on each node
void bst_inorder(BST *tree, void (*callback)(void*));

// Deletes the entire BST and frees memory
void free_bst(BST *tree);

// Helper function to delete a specific node (optional, for advanced use)
void bst_delete(BST *tree, void *data);

#endif // BST_H
