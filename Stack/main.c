#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

struct Stack {
    int items[MAX_STACK_SIZE];
    int top;
};

typedef struct Stack Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(Stack* stack) {
    return (stack->top == -1);
}

int isFull(Stack* stack) {
    return (stack->top == MAX_STACK_SIZE - 1);
}

void push(Stack* stack, int item) {
    if (isFull(stack)) {
        printf("Stack is full. Cannot push more elements.\n");
        return;
    }
    stack->items[++stack->top] = item;
}

int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop from an empty stack.\n");
        return -1;
    }
    return stack->items[stack->top--];
}

int peek(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot peek at an empty stack.\n");
        return -1;
    }
    return stack->items[stack->top];
}

int main() {
    Stack* stack = createStack();

    push(stack, 10);
    push(stack, 20);
    push(stack, 30);

    printf("Stack elements: ");
    while (!isEmpty(stack)) {
        printf("%d ", pop(stack));
    }

    return 0;
}
