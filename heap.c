#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "heap.h"

#define CAP 1000000
#define DAS_THE_ROOT -1

/* ------------------------------------------------------ */

/*
	Update: The current implementation of heap
	is set default as max-heap; if min-heap is
	required, adjust the comparison funcion
*/

static int left_child(int root_ind);
static int parent(int child);
static void swap(data_t* n1, data_t* n2);

static void sift_up(data_t* heap, size_t size, int child, 
	int cmp(data_t, data_t));
static void sift_down(data_t* heap, size_t size, int parent, 
	int cmp(data_t, data_t));

/* ------------------------------------------------------ */

heap_t* new_heap(int func(data_t, data_t)) {
	heap_t* new = (heap_t*)malloc(sizeof(heap_t));
	assert(new);

	new->heap = (data_t*)malloc(sizeof(data_t) * CAP);
	new->capacity = CAP;
	new->size = 0;
	new->cmp = func;

	return new;
}

data_t peek(heap_t* heap) {
	assert(heap);
	if (heap->size <= 0) {
		perror("My guy the heap is empty. What are you peeking at?\n");
		exit(EXIT_FAILURE);
	}
	return heap->heap[0];
}

void heap_push(heap_t* h, data_t val) {
	assert(h);
	++h->size; 
	if (h->size > h->capacity) {
		perror("Heap reached maximum capacity.\n");
		exit(EXIT_FAILURE);
	}

	h->heap[h->size - 1] = val;
	
	sift_up(h->heap, h->size, (int)h->size - 1, h->cmp);

}

void heap_pop(heap_t* h, bool free_content) {
	assert(h);
	
	data_t last = h->heap[h->size - 1];
	
	if (free_content)
		free(h->heap[0]);

	--h->size;
	if (h->size == 0)
		return;

	h->heap[0] = last;
	sift_down(h->heap, h->size, 0, h->cmp);
}

heap_t* delete_heap(heap_t* h, bool free_content)  {
	while (!heap_is_empty(h)) {
		if (free_content)
			heap_pop(h, true);
		else 
			heap_pop(h, false);
	}
	free(h->heap);
	free(h);
	return NULL;
}

void build_heap(data_t* array, size_t size, int cmp(data_t, data_t)) {
	for (int i = size / 2 - 1; i > -1; --i) {
		sift_down(array, size, i, cmp);
	}
}

void heap_sort(data_t* array, size_t n, int cmpfunc(data_t, data_t),
	bool reversed) {
	build_heap(array, n, cmpfunc);
	for (int i = n-1; i > 0; --i) {
		swap(&array[0], &array[i]);
		sift_down(array, i, 0, cmpfunc);
	}
	if (reversed) {
		for (int j = 0; j < n/2; ++j) {
			swap(&array[j], &array[n-j-1]);
		}
	}
}

/* ------------------------------------------------------ */

bool heap_is_empty(heap_t* heap) {
	return heap->size == 0;
}

static int left_child(int root_ind) {
	return (root_ind * 2) + 1;
}

static int parent(int child) {
	if (child == 0) 
		return DAS_THE_ROOT;
	else 
		return (child - 1) / 2;
}

static void swap(data_t* n1, data_t* n2) {
	data_t tmp = *n1;
	*n1 = *n2;
	*n2 = tmp;
}

static void sift_up(data_t* heap, size_t size, int last, 
	int cmp(data_t, data_t)) {
	while (last > 0) {
		int pLast = parent(last);
		if (pLast < size && (*cmp)(heap[last], heap[pLast]) > 0) {
			swap(&heap[last], &heap[pLast]);
			last = pLast;
		} else	
			return;
	}
}

static void sift_down(data_t* heap, size_t size, int parent, 
	int cmp(data_t, data_t)) {
	while (parent < (int)size) {
		int child = left_child(parent);
		
		if (child >= size)
			return;
		
		if (child + 1 < (int)size && (*cmp)(heap[child], heap[child + 1]) < 0)
			++child;

		if ((*cmp)(heap[parent], heap[child]) < 0) {
			swap(&heap[parent], &heap[child]);
			parent = child;
		} else 
			return;
	}
}
