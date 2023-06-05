#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#include "stack.h"

/*
    Update: now the pop function can give the user the choice to
    free the content within the stack or not
    
    The delete stack function will set free_content to true as 
    default, though. Use with caution.
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

void pop(stack_t* stack, bool free_content) {
    assert(stack);
    if (stack_is_empty(stack))
        return;

    s_node_t* plate = stack->top;
    stack->top = stack->top->next;
    if (free_content)
        free(plate->val);
    free(plate);
    plate = NULL;
}

void delete_stack(stack_t* stack) {
    assert(stack);
    while (!stack_is_empty(stack)) {
        pop(stack, true);
    }
    free(stack);
}
