#include <stdbool.h>

#ifndef HASH_TABLE_H_
#define HASH_TABLE_H_

typedef struct c_node c_node_t;

/* 
    The current implementation of hash table takes
    seperate chaining as the method to deal with collision
*/

struct c_node {
    void* val;
    c_node_t* next;
};

typedef struct {
    c_node_t* head;
} chain_t;

typedef struct {
    chain_t** table;
    size_t size;
    int (*func)(void*);
    int (*cmp)(void*, void*);
} hash_table_t;

hash_table_t* new_hash_table(int hash_f(void*), int cmpfunc(void*, void*));

bool ht_is_empty(hash_table_t* tab);

bool ht_find(hash_table_t* tab, void* val);

void ht_insert(hash_table_t* tab, void* val);

void ht_remove(hash_table_t* tab, void* val);

void delete_table(hash_table_t* table);

#endif
