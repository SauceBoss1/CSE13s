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

void stack_delete(Stack **s) {
    if (*s && (*s)->items) {
        for (uint32_t i = 0; i < (*s)->capacity; ++i) {
            node_delete(&(*s)->items[i]);
        }

        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

bool stack_empty(Stack *s) {
    if (s->top == 0) {
        return true;
    }
    return false;
}

bool stack_full(Stack *s) {
    if (s->top == s->capacity) {
        return true;
    }
    return false;
}

uint32_t stack_size(Stack *s) {
    return s->top;
}

bool stack_push(Stack *s, Node *n) {
    if (stack_full(s)) {
        return false;
    }

    s->items[s->top]->symbol = n->symbol;
    s->items[s->top]->frequency = n->frequency;
    s->top++;
    return true;
}

bool stack_pop(Stack *s, Node **n) {
    if (stack_empty(s)) {
        return false;
    }

    *n = s->items[s->top];
    //(*n)->frequency = s->items[s->top]->frequency;
    //(*n)->symbol = s->items[s->top]->symbol;
    s->top--;
    return true;
}

void stack_print(Stack *s) {
    printf("[ ");
    for (uint32_t i = 0; i < s->top; ++i) {
        printf("%" PRIu64 " ", s->items[i]->frequency);
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
    node_delete(&x);
    stack_print(s);
    //node_print(x);
    stack_delete(&s);
    return 0;
}*/
