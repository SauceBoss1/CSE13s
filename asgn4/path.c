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
    if (stack_size(p->vertices) > graph_vertices(G)) {
        return false;
    }

    uint32_t u = 0;
    if (!stack_peek(p->vertices, &u)) {
        u = START_VERTEX;
    }

    p->length += graph_edge_weight(G, u, v);
    //printf("p->length: %"PRIu32"\n", p->length);
    stack_push(p->vertices, v);
    stack_peek(p->vertices, &u);
    //printf("*top: %"PRIu32" pushed: %" PRIu32 "\n", u, v);
    return true;
}

bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    }

    stack_pop(p->vertices, v);
    //printf("v: %"PRIu32"\n", *v);
    uint32_t x = 0;
    if (!stack_peek(p->vertices, &x)) {
        x = START_VERTEX;
    }
    p->length -= graph_edge_weight(G, x, *v);
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
