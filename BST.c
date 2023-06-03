#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "BST.h"

/*
    NOTE: DO NOT USE BST_REMOVE FUCTION!!!
    The function is buggy, and will leave 
    erroneous tree and memory leak
    
    Or use it, if you are a sadist who enjoys your computer being held
    on life support from all the memory leaks that you caused by
    ignoring this warning
*/

void rec_insert(t_node_t* root, void* data, int cmp_f(void*, void*));
bool rec_search(t_node_t* root, void* data, t_node_t* pos, int cmp_f(void*, void*));
void rec_delete(t_node_t* root);

tree_t* new_BST(int cmp_func(void*, void*)) {
    tree_t* new = (tree_t*)malloc(sizeof(tree_t));
    assert(new);
    new->root = NULL;
    new->cmp_func = cmp_func;
    return new;
}

bool BST_is_empty(tree_t* tree) {
    assert(tree);
    return (!tree->root);
}

void BST_insert(tree_t* tree, void* n) {
	t_node_t* node = (t_node_t*)malloc(sizeof(t_node_t));
	assert(tree && node);
	node->left = node->right = NULL;
	node->val = n;
	
	if (!tree->root) {
		tree->root = node;
		return;
	}
	
	int compare = (*tree->cmp_func)(tree->root->val, n); 
	if (compare == 0) {
		free(node); node = NULL;
		return;
	} else if (compare > 0 && !tree->root->left) {
		tree->root->left = node;
		return;
	} else if (compare < 0 && !tree->root->right) {
		tree->root->right = node;
		return;
	}
	
	free(node); node = NULL;
	if (compare > 0) {
		rec_insert(tree->root->left, n, tree->cmp_func);
	} else {
		rec_insert(tree->root->right, n, tree->cmp_func);
	}
	
	return;
}

void rec_insert(t_node_t* v, void* n, int cmp(void*, void*)) {
	t_node_t* node = (t_node_t*)malloc(sizeof(t_node_t));
	assert(node);
	node->left = node->right = NULL;
	node->val = n;
	
	int compr = (*cmp)(v->val, n);
	if (compr == 0)	{
		free(node); node = NULL;
		return;
	} else if (compr > 0 && !v->left) {
		v->left = node;
		return;
	}
	else if (compr < 0 && !v->right) {
		v->right = node;
		return;
	}

	free(node); node = NULL;
	if (compr > 0) {
		rec_insert(v->left, n, cmp);
	} else {
		rec_insert(v->right, n, cmp);
	}

	return;
}

bool BST_search(tree_t* tree, void* data, t_node_t* pos) {
    assert(tree);
    if (BST_is_empty(tree))
        return false;
    return rec_search(tree->root, data, pos, tree->cmp_func);
}

bool rec_search(t_node_t* root, void* data, t_node_t* pos, int cmp_f(void*, void*)) {
    if (!root)
        return false;
    
    int compr = (*cmp_f)(data, root->val);
    if (compr == 0) {
        pos = root;
        return true;
    } else if (compr < 0) {
        return rec_search(root->left, data, pos, cmp_f);
    } else {
        return rec_search(root->right, data, pos, cmp_f);
    }
}

void BST_remove(tree_t* tree, void* data) {
    assert(tree);
    t_node_t* pos = NULL;
    bool is_there = BST_search(tree, data, pos);
    
    if (!is_there) 
        return;

    free(pos->val);
    free(pos);
    return;
}

void BST_delete_tree(tree_t* tree) {
    assert(tree);
    rec_delete(tree->root);
    free(tree);
}

void rec_delete (t_node_t* root) {
    if (root) {
        rec_delete(root->left);
        rec_delete(root->right);
        free(root->val);
        free(root);
    }
}
