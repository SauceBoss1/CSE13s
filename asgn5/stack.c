#include "stack.h"
#include "node.h"

#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

//Allocates memory for a stack of nodes
//Returns a stack pointer
//capacity: number of elements in stack
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (Node **) calloc(capacity, sizeof(Stack));

        if (!s->items) {
            free(s);
            s = NULL;
        }
    } else {
        free(s);
        s = NULL;
    }

    return s;
}

//Deletes a stack
//**s: takes in a stack to delete
void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

//Check if stack is empty
bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

//check if the stack is full
bool stack_full(Stack *s) {
    if (s->top >= s->capacity) {
        return true;
    }
    return false;
}

//returns the size of the stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//push a node onto the stack
//returns false if the stack is false
//returns true if it has been pushed successfully
bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }

    s->items[s->top] = n;
    s->top++;
    return true;
}

//Pops a node from the stack
//Uses pass by reference to "return" the node
//Returns false if the stack is empty
//
//returns true if the stack has been popped successfully
bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }

    *n = s->items[s->top - 1];
    s->top--;
    return true;
}

//Debug function to print the stack
void stack_print(Stack *s) {
    printf("[ ");
    for (uint32_t i = 0; i < s->top; ++i) {
        printf("%c ", s->items[i]->symbol);
    }
    printf("]\n");
}
///////////////////////////////////////////////////////////
//EXAMPLE USAGE OF STACK BELOW

/*
int main(void) {
    Node *a = node_create('a', 10);
    Node *b = node_create('b', 25);
    Node *c = node_create('c', 110);

    Stack *s = stack_create(3);

    stack_push(s, a);
    stack_push(s, b);
    stack_push(s, c);
    stack_print(s);

    Node *x;

    stack_pop(s, &x);
    stack_print(s);
    //node_print(x);
    stack_delete(&s);
    return 0;
}*/
