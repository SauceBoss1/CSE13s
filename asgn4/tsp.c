#include "graph.h"
#include "path.h"
#include "stack.h"
#include "vertices.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "hvui:o:"

static int recursive_calls = 0; //this keeps track of the number of times dfs has been called
void matrix_parser(Graph *G, FILE *infile);
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    uint32_t vertices);

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int opt = 0;
    bool undirected = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'u': undirected = true; break;
        }
    }

    char buf[1024];
    fgets(buf, 1024, infile);
    buf[strlen(buf) - 1] = '\0';
    int vertices = strtol(buf, NULL, 10); //number of cities in file

    char **cities = malloc(vertices * sizeof(char *));
    for (int i = 0; i < vertices; ++i) {
        char buf[1024];
        fgets(buf, 1024, infile);
        buf[strlen(buf) - 1] = '\0';
        cities[i] = strdup(buf); //add the city to the array
            //NOTE: strdup uses malloc already
    }

    Graph *G = graph_create((uint32_t) vertices, undirected);
    matrix_parser(G, infile);
    //graph_print(G);

    Path *curr = path_create();
    Path *shortest = path_create();

    recursive_calls = 0; //make sure we start our recursion at 0
    dfs(G, START_VERTEX, curr, shortest, cities, outfile, vertices);
    path_print(shortest, outfile, cities);
    printf("Recursive Calls: %d\n", recursive_calls);
    ////////////////////////////////////////////////////////////////////////////////////
    //USE THE SECTION BELOW TO FREE MEMORY

    for (int i = 0; i < vertices; ++i) { //free each item in array
        //printf("%s\n", cities[i]);
        free(cities[i]);
        cities[i] = NULL;
    }

    free(cities); //delete the cities array
    cities = NULL;

    graph_delete(&G);

    path_delete(&curr);
    path_delete(&shortest);

    fclose(infile);
    fclose(outfile);
    return 0;
}

//Updates the Graph G
//Returns void
//
//*G: a pointer to the graph G
//infile: the input file we are reading from
void matrix_parser(Graph *G, FILE *infile) {
    uint32_t i, j, k;
    i = j = k = 0;
    while (fscanf(infile, "%" PRIu32 " %" PRIu32 " %" PRIu32, &i, &j, &k) != EOF) {
        graph_add_edge(G, i, j, k);
        //printf("<%"PRIu32", %"PRIu32", %"PRIu32">\n", i, j ,k);
    }
    return;
}

//figure out how to deal with the shortest length
void dfs(Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile,
    uint32_t vertices) {
    recursive_calls++;
    uint32_t z = 0;

    //printf("path_vertices: %" PRIu32 " vertices: %" PRIu32 "\n", path_vertices(curr), vertices);
    if (path_vertices(curr) >= vertices - 1) {
        if (z == 0) {
            puts("z is 0");
        }
        if (path_length(shortest) == 0) {
            path_copy(shortest, curr); //if there's not shortest length so far
        } else if (path_length(curr) < path_length(shortest)) {
            path_copy(shortest, curr);
        }
    }

    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);
    //printf("pushed: %"PRIu32"\n", v);
    for (uint32_t w = 0; w <= graph_vertices(G); ++w) {
        //printf("v: %"PRIu32" w: %"PRIu32" weight: %" PRIu32"\n", v, w, graph_edge_weight(G, v, w));
        if (!graph_visited(G, w) && graph_has_edge(G, v, w)) {
            //printf("v: %"PRIu32" w: %"PRIu32" weight: %" PRIu32"\n", v, w, graph_edge_weight(G, v, w));
            dfs(G, w, curr, shortest, cities, outfile, vertices);
            path_pop_vertex(curr, &z, G);
            //printf("z: %" PRIu32 "\n", z);
        }
    }

    graph_mark_unvisited(G, v);
    return;
}
