#include <stdlib.h>
#include <assert.h>

#include "queue.h"

/*
    Update: The function dequeue now give the user the decision
    to whether free the content inside the queue
    
    The function delete_queue still set free_content as default, 
    freeing all the content inside the queue. Use with caution
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

void dequeue(queue_t* queue, bool free_content) {
    assert(queue);
    if (queue_is_empty(queue))
        return;
    
    q_node_t* mem = queue->front;
    queue->front = queue->front->next;
    if (free_content)
        free(mem->val);
    free(mem); mem = NULL;

    if (!queue->front)
        queue->back = NULL;

    return;
}

void delete_queue(queue_t* queue) {
    assert(queue);
    while (!queue_is_empty(queue)) {
        dequeue(queue, true);
    }
    free(queue); queue = NULL;
}
