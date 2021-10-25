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

//NOTE: C does not have any object oriented programming. This is the closest we can
//get.

//Creates the path_create "object"
//Returns a pointer to the path created
//
//noi inputs are allowed
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

//Deletes the Path "object"
//Returns void
//
//**p: takes in a pointer to a point of a path "object"
void path_delete(Path **p) {
    if (*p) {
        stack_delete(&(*p)->vertices);
        free(*p);
        *p = NULL;
    }
    return;
}

//Handles pushing a vertex to the stack and updating the edge length
//Returns true if the push was successful
//Returns false if stack is full
//
//*p: takes in a path
//*G: takes in a Graph
bool path_push_vertex(Path *p, uint32_t v, Graph *G) {
    if (stack_size(p->vertices) > graph_vertices(G)) { //check if stack is full
        return false;
    }
    uint32_t u = 0;
    if (!stack_peek(p->vertices, &u)) { //check the top of the stack
        u = START_VERTEX; //we are at the start vertex if the stack is empty
    }
    stack_push(p->vertices, v);

    if (u != v) { //check to make sure the vertices are not the same
        p->length += graph_edge_weight(G, u, v);
    }
    return true;
}

//Handles popping the vertex from the stack and updating the edge length
//Returns true if the stack is empty
//
//*p: takes in a path
//*G: takes a graph
bool path_pop_vertex(Path *p, uint32_t *v, Graph *G) {
    if (stack_empty(p->vertices)) {
        return false;
    }
    uint32_t x = 0;
    if (!stack_peek(p->vertices, &x)) { //return the top vertex
        x = START_VERTEX; //if the stack is empty, then we are at the start
    }

    stack_pop(p->vertices, v);

    uint32_t y = 0;
    if (!stack_peek(p->vertices, &y)) { //find the top after the stack has been popped
        y = START_VERTEX;
    }
    p->length -= graph_edge_weight(G, y, x); //make sure you are finding the right edges
    return true;
}

//Returns the size of the path stack
//
//*p: takes in a path
uint32_t path_vertices(Path *p) {
    return stack_size(p->vertices);
}

//Returns the length of the path travelled
//
//*p: takes in a path
uint32_t path_length(Path *p) {
    return p->length;
}

//Copies the contents of one path to another path
//Returns void
//
//*dst: the path to be copied to
//*src: the path that is being copied
void path_copy(Path *dst, Path *src) {
    stack_copy(dst->vertices, src->vertices);
    dst->length = src->length; //remember to copy the path lengths
    return;
}

//prints the path length and the path traveled
//Returns void
//
//*p: takes in a path
//*outfile: where the output will be printed to
//*cities: takes in the array of cities
void path_print(Path *p, FILE *outfile, char *cities[]) {
    fprintf(outfile, "Path length: %" PRIu32 "\n", p->length);
    fprintf(outfile, "Path: ");
    stack_print(p->vertices, outfile, cities);
    return;
}
