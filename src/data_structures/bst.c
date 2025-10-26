/*#include "bst.h"
#include <stdlib.h>

BST* create_bst(int (*compare)(void*, void*)) {
    BST *tree = (BST*)malloc(sizeof(BST));
    tree->root = NULL;
    tree->compare = compare;
    return tree;
}

BSTNode* bst_insert_recursive(BSTNode *node, void *data, int (*compare)(void*, void*)) {
    if (node == NULL) {
        BSTNode *new_node = (BSTNode*)malloc(sizeof(BSTNode));
        new_node->data = data;
        new_node->left = NULL;
        new_node->right = NULL;
        return new_node;
    }
    
    if (compare(data, node->data) < 0) {
        node->left = bst_insert_recursive(node->left, data, compare);
    } else {
        node->right = bst_insert_recursive(node->right, data, compare);
    }
    
    return node;
}

void bst_insert(BST *tree, void *data) {
    tree->root = bst_insert_recursive(tree->root, data, tree->compare);
}

BSTNode* bst_search_recursive(BSTNode *node, void *data, int (*compare)(void*, void*)) {
    if (node == NULL) return NULL;
    
    int cmp = compare(data, node->data);
    if (cmp == 0) return node;
    if (cmp < 0) return bst_search_recursive(node->left, data, compare);
    return bst_search_recursive(node->right, data, compare);
}

void* bst_search(BST *tree, void *data) {
    BSTNode *result = bst_search_recursive(tree->root, data, tree->compare);
    return result ? result->data : NULL;
}

void free_bst_recursive(BSTNode *node) {
    if (node == NULL) return;
    free_bst_recursive(node->left);
    free_bst_recursive(node->right);
    free(node);
}

void free_bst(BST *tree) {
    free_bst_recursive(tree->root);
    free(tree);
}  */

#include "bst.h"

// =============================
// Helper: Create a new node
// =============================
static BSTNode* create_node(void *data) {
    BSTNode *newNode = (BSTNode*)malloc(sizeof(BSTNode));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// =============================
// Create a new BST
// =============================
BST* create_bst(int (*compare)(void*, void*)) {
    BST *tree = (BST*)malloc(sizeof(BST));
    if (!tree) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    tree->root = NULL;
    tree->compare = compare;
    return tree;
}

// =============================
// Recursive Insert Helper
// =============================
static BSTNode* insert_node(BSTNode *node, void *data, int (*compare)(void*, void*)) {
    if (node == NULL) {
        return create_node(data);
    }

    int cmp = compare(data, node->data);

    if (cmp < 0)
        node->left = insert_node(node->left, data, compare);
    else if (cmp > 0)
        node->right = insert_node(node->right, data, compare);
    else
        ; // Duplicate data — ignore or handle as needed

    return node;
}

// =============================
// Insert into BST
// =============================
void bst_insert(BST *tree, void *data) {
    if (!tree) return;
    tree->root = insert_node(tree->root, data, tree->compare);
}

// =============================
// Recursive Search Helper
// =============================
static void* search_node(BSTNode *node, void *data, int (*compare)(void*, void*)) {
    if (node == NULL)
        return NULL;

    int cmp = compare(data, node->data);

    if (cmp == 0)
        return node->data;
    else if (cmp < 0)
        return search_node(node->left, data, compare);
    else
        return search_node(node->right, data, compare);
}

// =============================
// Search in BST
// =============================
void* bst_search(BST *tree, void *data) {
    if (!tree || !tree->root)
        return NULL;
    return search_node(tree->root, data, tree->compare);
}

// =============================
// In-order Traversal Helper
// =============================
static void inorder_traverse(BSTNode *node, void (*callback)(void*)) {
    if (node == NULL) return;
    inorder_traverse(node->left, callback);
    callback(node->data);
    inorder_traverse(node->right, callback);
}

// =============================
// Public In-order Traversal
// =============================
void bst_inorder(BST *tree, void (*callback)(void*)) {
    if (!tree || !tree->root) return;
    inorder_traverse(tree->root, callback);
}

// =============================
// Recursive Free Helper
// =============================
static void free_node(BSTNode *node) {
    if (node == NULL) return;
    free_node(node->left);
    free_node(node->right);
    free(node);
}

// =============================
// Free Entire BST
// =============================
void free_bst(BST *tree) {
    if (!tree) return;
    free_node(tree->root);
    free(tree);
}

// =============================
// Optional: Delete a Node
// =============================
static BSTNode* find_min(BSTNode *node) {
    while (node && node->left != NULL)
        node = node->left;
    return node;
}

static BSTNode* delete_node(BSTNode *root, void *data, int (*compare)(void*, void*)) {
    if (root == NULL)
        return root;

    int cmp = compare(data, root->data);

    if (cmp < 0)
        root->left = delete_node(root->left, data, compare);
    else if (cmp > 0)
        root->right = delete_node(root->right, data, compare);
    else {
        // Node with one or no child
        if (root->left == NULL) {
            BSTNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            BSTNode *temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        BSTNode *temp = find_min(root->right);
        root->data = temp->data;
        root->right = delete_node(root->right, temp->data, compare);
    }
    return root;
}

void bst_delete(BST *tree, void *data) {
    if (!tree) return;
    tree->root = delete_node(tree->root, data, tree->compare);
}
