#include "path.h"

#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Path {
    Stack *vertices;
    uint32_t length;
};

Path *path_create(void) {
    Path *p = (Path *) malloc(sizeof(Path));
    if (p) {
        p->vertices = stack_create(VERTICES);
        p->length = 0;
    } else {
        free(p);
        p = NULL;
    }
    return p;
}

void path_delete(Path **p) {
    stack_delete(&(*p)->vertices);
    free(*p);
    *p = NULL;
    return;
}

bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    printf("first line\n");
    if (stack_size(p->vertices) > graph_vertices(G)) {
        return false;
    }
    printf("second line\n");

    //if (!stack_empty(p->vertices)) {
    uint32_t x = 0;
    uint32_t *i = &x;
    //printf("i: %"PRIu32"\n",i);

    printf("third line\n");
    stack_peek(p->vertices, i);

    printf("fourth line\n");
    p->length += graph_edge_weight(G, v, *i);
    //}

    printf("fifth line\n");
    stack_size(p->vertices);
    puts("sixth line");
    stack_push(p->vertices, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    }

    stack_pop(p->vertices, v);
    uint32_t *i = 0;
    stack_peek(p->vertices, i);
    p->length -= graph_edge_weight(G, *v, *i);
    return true;
}

uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

uint32_t path_length(Path *p) {
    return p->length;
}

void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length;
    return;
}

void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
    stack_print(p->vertices, outfile, cities);
    return;
}
