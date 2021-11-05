#include "pq.h"
#include "node.h"

#include <stdbool.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdio.h>
#include <math.h>

struct PriorityQueue {
    uint32_t top;
    uint32_t capacity;
    Node **items;
};

PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));
    if (pq) {
        pq->top = 0;
        pq->capacity = capacity;
        pq->items = (Node **) calloc(capacity, sizeof(Node));

        if (!pq->items) {
            free(pq);
            pq = NULL;
        }
    } else {
        free(pq);
        pq = NULL;
    }
    return pq;
}

void pq_delete(PriorityQueue **q) {
    if (*q && (*q)->items) {
        //printf("cap: %"PRIu32"\n",(*q)->capacity);
        /* 
        for (uint32_t i = 0; i < (*q)->capacity; ++i) {
            //printf("i: %"PRIu32"\n", i);

            node_delete(&(*q)->items[i]);
            //free(&(*q)->items[i]);
        }
        */
        free((*q)->items);
        free(*q);
        *q = NULL;
    }
    return;
}

/////////////////////////////////////////////
//HEAP IMPLEMENTATION BELOW

static uint32_t min_child(PriorityQueue *q, uint32_t first, uint32_t last) {
    uint32_t left = 2 * first;
    uint32_t right = left + 1;

    if ((right <= last) && (q->items[left - 1]->frequency < q->items[right - 1]->frequency)) {
        return left;
    }
    return right;
}

void swap(Node *x, Node *y) {
    //puts("here");
    Node t = *x;
    *x = *y;
    *y = t;

    return;
}

static void fix_heap(PriorityQueue *q, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first, great = min_child(q, mother, last);

    while ((mother <= floor(last / 2)) && !found) {
        if (q->items[0]->frequency == 0) {
            swap(q->items[0], q->items[q->top - 1]);
        }
        if (q->items[mother - 1]->frequency > q->items[great - 1]->frequency) {
            swap(q->items[mother - 1], q->items[great - 1]);
            mother = great;
            great = min_child(q, mother, last);
        } else {
            found = true;
        }
    }
    return;
}

///////////////////////////////////////////

bool pq_empty(PriorityQueue *q) {
    if (q->top == 0) {
        return true;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    if (q->top == q->capacity) {
        return true;
    }
    return false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q->top;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (pq_full(q)) {
        return false;
    }

    q->items[q->top] = n;
    fix_heap(q, 1, q->top);
    q->top++;

    return true;
}

bool dequeue(PriorityQueue *q, Node **n) {
    if (pq_empty(q)) {
        return false;
    }

    swap(q->items[0], q->items[q->top - 1]);
    *n = q->items[q->top - 1];
    q->top--;
    fix_heap(q, 1, q->top);

    return true;
}

void pq_print(PriorityQueue *q) {
    printf("[");
    for (uint32_t i = 0; i < q->top; ++i) {
        printf(" %" PRIu64, q->items[i]->frequency); //tries to print NULL leading to segfault
    }
    printf(" ]\n");

    return;
}

/////////////////////////////////////////////////
//BELOW IS AN EXAMPLE OF HOW THE ADT WILL BE USED
/*
int main(void){
    PriorityQueue *q = pq_create(5);

    Node *a = node_create('a', 10);
    Node *b = node_create('b', 51);
    Node *c = node_create('c', 1);
    Node *d = node_create('d', 37);
    Node *e = node_create('e', 5);
    
    enqueue(q, a);
    enqueue(q, b);
    enqueue(q, c);
    enqueue(q, d);
    enqueue(q, e);
    pq_print(q);
    
    Node *n;
    
    dequeue(q, &n);
    node_print(n);
    pq_print(q);
    dequeue(q, &n);
    pq_print(q);
    
    pq_delete(&q);
 
    return 0;
}
*/
