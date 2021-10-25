#include "graph.h"

#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
};

//Creates an instance of the graph
//Returns a pointer of the graph
//
//vertices: takes in the number of vertices in the graph
//undirected: tells us whether or not we want a undirected graph
Graph *graph_create(uint32_t vertices, bool undirected) {
    Graph *G = (Graph *) calloc(1, sizeof(Graph)); //initilize all fields of the struct to 0
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

//Destructor for the graph
//Returns void
//
//**G: take in a point of a pointer to the graph
void graph_delete(Graph **G) {
    free(*G);
    *G = NULL;
    return;
}

//Returns the number of vertices in the graph
//
//*G: takes in a graph
uint32_t graph_vertices(Graph *G) {
    return G->vertices;
}

//Adds the edges to the graph
//Returns false if the vertices are out of bounds
//Return true if the vertex was successfully pushed
//
//*G: takes in a graph
//i, j: these are the vertices of the graph
//k: the weight you want to set to the graph
bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k) {
    if ((i > G->vertices) || (j > G->vertices)) { //check if the the vertcies are in bounds
        return false;
    }

    if (G->undirected) {
        G->matrix[i][j] = k;
        G->matrix[j][i] = k;
    } else {
        G->matrix[i][j] = k;
    }
    return true;
}

//Checks if the given vertices has an edge
//Returns false if there is not edge
//Returns true if there is an edge
//
//*G: takes in a graph
//i,j: takes in vertices
bool graph_has_edge(Graph *G, uint32_t i, uint32_t j) {
    if ((i > G->vertices) || (j > G->vertices) || (G->matrix[i][j] < 1)) {
        //check if i,j are in bounds and if the the weight is a positive non-zero
        return false;
    }
    return true;
}

//Returns the edge weight of given vertices
//
//*G: takes in a graoh
//i,j: takes in 2 vertices on a point
uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j) {
    if ((i > G->vertices) || (j > G->vertices)) {
        return 0;
    }
    return G->matrix[i][j];
}

//Checks whether or not a vertex has been visited
//Returns true if the vertex has been visted else false
//
//*G: takes in a graph
//v: takes in a vertex
bool graph_visited(Graph *G, uint32_t v) {
    return G->visited[v];
}

//Marks the vertex v as visited
//Returns void
//
//*G: takes in a graph
//v: takes in a vertex
void graph_mark_visited(Graph *G, uint32_t v) {
    if (v > G->vertices) { //checks to make sure that the vertex is in bounds
        fprintf(stderr, "vertex is out of bounds");
        return;
    }

    G->visited[v] = true;
    return;
}

//Marks the vertex v as unvisted
//Returns void
//
//*G: takes in a graph
//v: takes in a vertex
void graph_mark_unvisited(Graph *G, uint32_t v) {
    if (v > G->vertices) { //check if the vertex is in bounds
        fprintf(stderr, "vertex is out of bounds");
        return;
    }

    G->visited[v] = false;
    return;
}

//Prints a graph of the matrix
//Returns void
//
//*G: takes in a graph
void graph_print(Graph *G) {
    for (uint32_t x = 0; x < G->vertices; ++x) {
        printf("%" PRIu32 " ", x);
    }
    printf("\n");
    for (uint32_t i = 0; i < G->vertices; ++i) {
        printf("%" PRIu32 " ", i);
        for (uint32_t j = 0; j < G->vertices; ++j) {
            printf(" %" PRIu32, G->matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
