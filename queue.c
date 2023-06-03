#include <stdlib.h>
#include <assert.h>

#include "queue.h"

/*
    NOTE: The function dequeue will not free the content inside the data of
    the member of the queue, please manually free the content before using the 
    dequeue function
*/

queue_t* new_queue() {
    queue_t* new = (queue_t*)malloc(sizeof(queue_t));
    assert(new);
    new->front = new->back = NULL;
    return new;
}

bool queue_is_empty(queue_t* queue) {
    return (!queue->front && !queue->back);
}

void* front(queue_t* queue) {
    assert(queue && queue->front);
    return queue->front->val;
}

void* back(queue_t* queue) {
    assert(queue && queue->back);
    return queue->back->val;
}

void enqueue(queue_t* queue, void* data) {
    assert(queue);
    q_node_t* mem = (q_node_t*)malloc(sizeof(q_node_t));
    assert(mem);
    mem->next = NULL;
    mem->val = data;

    if (queue_is_empty(queue)) {
        queue->front = queue->back = mem;
        return;
    }

    queue->back->next = mem;
    queue->back = mem;
    return;
}

void dequeue(queue_t* queue) {
    assert(queue);
    if (queue_is_empty(queue))
        return;
    
    q_node_t* mem = queue->front;
    queue->front = queue->front->next;
    free(mem); mem = NULL;

    if (!queue->front)
        queue->back = NULL;

    return;
}

void delete_queue(queue_t* queue) {
    assert(queue);
    while (!queue_is_empty(queue)) {
        free(front(queue));
        dequeue(queue);
    }
    free(queue); queue = NULL;
}
