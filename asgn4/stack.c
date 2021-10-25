#include "stack.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

//Handles the creation of the stack
//Returns a stack pointer
//
//capacity: takes in the size of the stack you desire
//
//NOTE: this code was given to us from the assignment pdf
Stack *stack_create(uint32_t capacity) {
    Stack *s = (Stack *) malloc(sizeof(Stack)); //allocate memory for the stack
    if (s) { //check if the stack was created successfully
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(
            capacity, sizeof(uint32_t)); //allocate memomry for each item in stack
        if (!s->items) { //check if the array couldnt be created
            free(s);
            s = NULL;
        }
    }
    return s;
}

//Deletes and frees the entire stack
//Returns void
//
//**s: takes in a pointer of a pointer of a stack
//
//NOTE: this code was given to us from the assignment pdf
void stack_delete(Stack **s) {
    if (*s && (*s)->items) { //check if the stack even exists
        free((*s)->items);
        free(*s);
        *s = NULL;
    }
    return;
}

//Checks if the stack is empty
//Returns true if the stack is empty
//Returns false if not
//
//*s: takes in a stack
bool stack_empty(Stack *s) {
    if (s->top == 0) { //check if the stack is empty
        return true;
    }
    return false;
}

//Checks if the stack is full
//Returns true if the stack is full
//Returns false if not
//
//*s takes in a stack
bool stack_full(Stack *s) {
    if (s->top == s->capacity) { //check to see if stack is full
        return true;
    }
    return false;
}

//Returns the stack size
//
//*s: takes in a stack
uint32_t stack_size(Stack *s) {
    return s->top;
}

//Pushes items into the stack
//Returns true if the item was pushed succesfull
//Returns false if it wasn't pushed correctly
//
//*s: takes in a stack
//x: the item that you are going to push to the stack
bool stack_push(Stack *s, uint32_t x) {
    if (stack_full(s)) {
        return false;
    }
    s->items[s->top] = x;
    s->top += 1; //remember to increment top after each push
    return true;
}

//Pops an item to the stack and passes the item to a pointer
//Returns true if the item was sucessfully pused otherwise false
//
//*s: takes in a stack
//*x: pass the value of the popped item to the pointer
bool stack_pop(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top]; //pass the value of the popped item to the pointer
    s->top--;
    return true;
}

//Passes the value of the item at the top of the stack
//Returns true if the item was peeked successfully otherwise false
//
//*s: takes in a stack
//*x: passes the value of the peeked item into a pointer
bool stack_peek(Stack *s, uint32_t *x) {
    if (stack_empty(s)) {
        return false;
    }
    *x = s->items[s->top - 1]; //we need to decrement the value of top in order to
        //get the top of the stack
    return true;
}

//Copies the contents of one stack to another stack
//Returns void
//
//*dst: the stack your copying to
//*src: the stack your copying from
void stack_copy(Stack *dst, Stack *src) {
    for (uint32_t i = 0; i < src->top; ++i) { //copy the array from one stack to the other stack
        dst->items[i] = src->items[i];
    }
    dst->top = src->top; //copy the top from *src to *dst
    return;
}

//Prints the stack that is passed
//Returns void
//
//*s: takes in a stack
//*outfile: where the stack will be printed to
//*cities[]: the array of cities
//
//NOTE: this code is given to us int he assignment pdf
void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; ++i) {
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
    return;
}
