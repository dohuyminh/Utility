#include <stdlib.h>
#include <assert.h>

#include "hash_table.h"

#define TABLE_SIZE 26

/*
    NOTE: The function delete_table will free all the contents
    in the table, use with caution
*/

static chain_t* new_chain();
static bool search_chain(chain_t* chain, void* elem, int cmp(void*, void*));
static void insert_chain(chain_t* chain, void* val);
static void chain_remove(chain_t* chain, void* val, int cmp(void*, void*));
static void free_chain(chain_t* chain);

hash_table_t* new_hash_table(int hash_func(void*), int cmpfunc(void*, void*)) {
    hash_table_t* new = (hash_table_t*)malloc(sizeof(hash_table_t));
    assert(new);

    new->size = TABLE_SIZE;

    new->table = (chain_t**)malloc(TABLE_SIZE * sizeof(chain_t*));
    for (int i = 0; i < TABLE_SIZE; ++i) {
        new->table[i] = new_chain();
    }

    new->func = hash_func;
    new->cmp = cmpfunc;
    return new;
}

static chain_t* new_chain() {
    chain_t* new = (chain_t*)malloc(sizeof(chain_t));
    assert(new);
    new->head = NULL;
    return new;
}

bool ht_is_empty(hash_table_t* tab) {
    for (size_t i = 0; i < tab->size; ++i) {
        if (tab->table[i])
            return false;
    }   
    return true;
}

bool ht_find(hash_table_t* tab, void* val) {
    int in_chain = (*tab->func)(val);
    if (search_chain(tab->table[in_chain], val, tab->cmp))
        return true;
    return false;
}

static bool search_chain(chain_t* chain, void* val, int cmp(void*, void*)) {
    c_node_t* tmp = chain->head;
    while (tmp) {
        if ((*cmp)(val, tmp->val) == 0)
            return true;
        tmp = tmp->next;
    }
    return false;
}

void ht_insert(hash_table_t* tab, void* val) {
    int c = (*tab->func)(val);
    if (search_chain(tab->table[c], val, tab->cmp))
        return;

    insert_chain(tab->table[c], val);
}

static void insert_chain(chain_t* chain, void* val) {
    c_node_t* new = (c_node_t*)malloc(sizeof(c_node_t));
    assert(new);
    new->next = NULL;
    new->val = val;

    if (!chain->head) {
        chain->head = new;
        return;
    }

    new->next = chain->head;
    chain->head = new;
    return;
}

void ht_remove(hash_table_t* tab, void* val) {
    int c = (*tab->func)(val);
    chain_remove(tab->table[c], val, tab->cmp);
    return;
}

static void chain_remove(chain_t* chain, void* val, int cmp(void*, void*)) {
    c_node_t* tmp = chain->head;
    if (!tmp)
        return;

    if ((*cmp)(val, tmp->val) == 0) {
        chain->head = chain->head->next;
        free(tmp); return;
    }

    while (tmp->next && (*cmp)(val, tmp->next->val) != 0)
        tmp = tmp->next;

    if (tmp->next && (*cmp)(val, tmp->next->val) == 0) {
        c_node_t* to_free = tmp->next;
        tmp->next = to_free->next;
        free(to_free);
    }

    return;
}

void delete_table (hash_table_t* tab) {
    for (size_t i = 0; i < TABLE_SIZE; ++i) {
        free_chain(tab->table[i]);
    }
    free(tab->table);
    free(tab);
}

static void free_chain(chain_t* chain) {
    c_node_t* tmp = chain->head;
    while (tmp) {
        c_node_t* to_free = tmp;
        tmp = tmp->next;
        free(to_free->val);
        free(to_free);
    }
    free(chain);
}

