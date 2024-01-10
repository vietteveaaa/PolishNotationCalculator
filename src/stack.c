#include "stack.h"

#include <stdio.h>
#include <stdlib.h>

void init(stack* stack) {
    stack->capacity = 16;
    stack->elements = (float*)malloc(stack->capacity * sizeof(float));
    stack->top = -1;
}

int is_empty(stack* stack) { return stack->top == -1; }

void push(stack* stack, float value) {
    if (stack->top == stack->capacity - 1) {
        stack->capacity *= 2;
        stack->elements = (float*)realloc(stack->elements, stack->capacity * sizeof(float));
    }
    stack->elements[++stack->top] = value;
}

float pop(stack* stack, int* flag) {
    float result = 1;
    if (is_empty(stack)) {
        *flag = -1;
        result = 0;
    }
    if (result != 0) {
        result = stack->elements[stack->top--];
    }
    return result;
}

float peek(stack* stack, int* flag) {
    float result = 1;
    if (is_empty(stack)) {
        *flag = -1;
        result = 0;
    }
    if (result != 0) {
        result = stack->elements[stack->top];
    }
    return result;
}

void clear(stack* stack) {
    free(stack->elements);
    stack->top = -1;
    stack->capacity = 0;
}
