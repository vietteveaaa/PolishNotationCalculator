#ifndef STACK_H
#define STACK_H

typedef struct {
    float* elements;
    int top;
    int capacity;
} stack;

void init(stack* stack);
int is_empty(stack* stack);
void push(stack* stack, float value);
float pop(stack* stack, int* flag);
float peek(stack* stack, int* flag);
void clear(stack* stack);

#endif /* STACK_H */
