#include <stdbool.h>

#ifndef STACK_H_
#define STACK_H_

typedef struct node s_node_t;

struct node {
    void* val;
    s_node_t* next;
};

typedef struct {
    s_node_t* top;
} stack_t;

stack_t* new_stack();

bool stack_is_empty(stack_t* stack);

void* top(stack_t* stack);

void push(stack_t* stack, void* val);

void pop(stack_t* stack);

void delete_stack(stack_t* stack);

#endif
