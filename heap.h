#include <stdbool.h>
#include <stdlib.h>

#ifndef HEAP_H_
#define HEAP_H_

typedef void* data_t;

typedef struct {
    data_t* heap;
    size_t capacity;
    size_t size;
    int (*cmp)(data_t, data_t);
} heap_t;

heap_t* new_heap(int func(data_t, data_t));

bool heap_is_empty(heap_t* heap);

data_t peek(heap_t* heap);

void heap_push(heap_t* heap, data_t val);

void heap_pop(heap_t* heap, bool free_content);

heap_t* delete_heap(heap_t* heap, bool free_content);

void heap_sort(data_t* array, size_t n, int cmpfunc(data_t, data_t));

#endif