#include "bst.h"
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
}