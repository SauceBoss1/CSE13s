#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#include "graph.h"
#include "vertices.h"

struct Graph {
    uint32_t vertices;
    bool undirected;
    bool visited[VERTICES];
    uint32_t matrix[VERTICES][VERTICES];
}

Graph *graph_create(uint32_t vertices, bool undirected){
    Graph *G = (Graph *)calloc(1, sizeof(Graph));
    G->vertices = vertices;
    G->undirected = undirected;
    return G;
}

void graph_delete(Graph **G){
    free(*G);
    *G = NULL;
    return;
}

uint32_t graph_vertices(Graph *G){
    G->vertices;
}

bool graph_add_edge(Graph *G, uint32_t i, uint32_t j, uint32_t k){
    if ((i > G->vertices) || (j > G->vertices)){
        return false;
    }
    G->matrix[i][j] = k;
    return true;
}

uint32_t graph_edge_weight(Graph *G, uint32_t i, uint32_t j){
    if ((i > G->vertices) || (j > G->vertices)){
        return 0;
    }
    return G->matrix[i][j];
}

bool graph_visited(Graph *G, uint32_t v){
    return G->visited[v];
}

void graph_mark_visited(Graph *G, uint32_t v){
    if (v > G->vertices){
        fprintf(stderr, "vertex is out of bounds");
        return;
    }

    G->visited[v] = true;
    return;
}

void graph_mark_unvisited(Graph *G, uint32_t v){
    if ( v > G->vertices){
        fprintf(stderr, "vertex is out of bounds");
        return;
    }

    G->visited[v] = false;
    return;
}

void graph_print(Graph *G){
    for (uint32_t i = 0; i < G->vertices; ++i){
        for (uint32_t j = 0; j < G->vertices; ++i){
            printf("% "PRIu32,G->matrix[i][j]);
        }
        printf("\n");
    }
    return;
}
