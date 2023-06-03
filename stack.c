#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h"

/*
    NOTE: The pop function of the stack will not free the content within the 
    plate of the stack, please manually free the content of the plate before 
    using the pop function to prevent memory leaks
*/

stack_t* new_stack () {
    stack_t* new = (stack_t*)malloc(sizeof(stack_t));
    assert(new);
    new->top = NULL;
    return new;
}

bool stack_is_empty(stack_t* stack) {
    return (!stack->top);
}

void* top(stack_t* stack) {
    assert(stack && stack->top);
    return (stack->top->val);
}

void push(stack_t* stack, void* data) {
    assert(stack);
    s_node_t* plate = (s_node_t*)malloc(sizeof(s_node_t));
    assert(plate);
    plate->next = NULL;
    plate->val = data;

    if (stack_is_empty(stack)) {
        stack->top = plate;
        return;
    }

    plate->next = stack->top;
    stack->top = plate;
    return;
}

void pop(stack_t* stack) {
    assert(stack);
    if (stack_is_empty(stack))
        return;

    s_node_t* plate = stack->top;
    stack->top = stack->top->next;
    free(plate);
    plate = NULL;
}

void delete_stack(stack_t* stack) {
    assert(stack);
    while (!stack_is_empty(stack)) {
        free(top(stack));
        pop(stack);
    }
    free(stack);
}
