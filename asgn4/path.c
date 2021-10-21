#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>
#include <stdio.h>

#include "path.h"
#include "stack.h"
#include "vertices.h"

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void){
    Path *p = (Path *)malloc(sizeof(Path));
    p->vertices = *stack_create(VERTICES);
    p->length = 0;
    return p;
}

void path_delete(Path **p){
    free(*p);
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G){
    if (stack_size(p->vertices) > graph_vertices(G)){
        return false;
    }

    if (!stack_empty(p->vertices)){
        uint32_t *i;
        stack_peek(p->vertices, i);
        p->length += graph_edge_weight(G, i, v);
    }
    
    stack_push(p->vertices, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G){
    if(stack_empty(p->vertices)){
        return false;
    }
    
    stack_pop(p->vertices, v);
    uint32_t *i;
    stack_peek(p->vertices, i);
    p->length -= graph_edge_weight(G, i, v);
    return true;
}

uint32_t path_vertices(Path *p){
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p){
    return p->length;
}

void path_copy(Path *dst, Path *src){
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]){
    fprintf(outfile, "Path length: &" PRIu32 "\n", p->length);
    stack_print(p->vertices, outfile, cities[]);
    return;
}
