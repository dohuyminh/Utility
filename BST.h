#include <stdbool.h>

#ifndef BST_H_
#define BST_H_

typedef struct t_node t_node_t;

struct t_node {
    void* val;
    t_node_t* left;
    t_node_t* right;
};

typedef struct {
    t_node_t* root;
    int (*cmp_func)(void*, void*);
} tree_t;

tree_t* new_BST(int func(void*, void*));

bool BST_is_empty(tree_t* tree);

void BST_insert(tree_t* tree, void* data);

bool BST_search(tree_t* tree, void* data);

void BST_remove(tree_t* tree, void* data);

void BST_delete_tree(tree_t* tree);

#endif
