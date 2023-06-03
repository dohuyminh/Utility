#include <stdbool.h>

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct node q_node_t;

struct node {
    void* val;
    q_node_t* next;
};

typedef struct {
    q_node_t* front;
    q_node_t* back;
} queue_t;

queue_t* new_queue();

bool queue_is_empty(queue_t* queue);

void* front(queue_t* queue);

void* back(queue_t* queue);

void enqueue(queue_t* queue, void* data);

void dequeue(queue_t* queue);

void delete_queue(queue_t* queue);

#endif
