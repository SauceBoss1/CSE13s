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
void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose);

//handles with printing the help msg
void help_msg(void) {
    puts("SYNOPSIS");
    puts("    Traveling Salesman Problem using DFS.\n");
    puts("USAGE");
    puts("    ./tsp [-u] [-v] [-h] [-i infile] [-o outfile]\n");
    puts("OPTIONS");
    puts("  -u             Use undirected graph.");
    puts("  -v             Enable verbose printing.");
    puts("  -h             Program usage and help.");
    puts("  -i infile      Input containing graph (default: stdin");
    puts("  -o outfile     Output of computed path (default: stdout)");
}

int main(int argc, char **argv) {
    FILE *infile = stdin;
    FILE *outfile = stdout;

    int opt = 0;
    bool undirected = false;
    bool verbose = false;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) { //handles command line options
        switch (opt) {
        case 'i': infile = fopen(optarg, "r"); break;
        case 'o': outfile = fopen(optarg, "w"); break;
        case 'u': undirected = true; break;
        case 'v': verbose = true; break;
        case 'h':
            help_msg();
            return 1;
            break;
        }
    }
    ////////////////////////////////////////////////////////////////

    //The below code handles with the cities
    char buf[1024];
    if (fgets(buf, 1024, infile) == NULL) {
        fprintf(stderr, "Bad Read!\n");
        return 1;
    }

    buf[strlen(buf) - 1] = '\0';
    int vertices = strtol(buf, NULL, 10); //number of cities in file
    if (vertices <= 1) {
        fprintf(stderr, "There is no where to go.\n");
        return 1;
    }

    char **cities = malloc(vertices * sizeof(char *)); //dynamicall create an array of strings
    for (int i = 0; i < vertices; ++i) {
        char buf[1024];

        if (fgets(buf, 1024, infile) == NULL) { //checks to see if fgets() is a success
            fprintf(stderr, "Bad Read!\n");
            return 1;
        }

        buf[strlen(buf) - 1] = '\0';
        cities[i] = strdup(buf); //add the city to the array
            //NOTE: strdup uses malloc already
    }

    /////////////////////////////////////////////////////////////

    //The code below handles the meat of the program
    Graph *G = graph_create((uint32_t) vertices, undirected);
    matrix_parser(G, infile);
    //graph_print(G);

    Path *curr = path_create();
    Path *shortest = path_create();

    recursive_calls = 0; //make sure we start our recursion at 0
    dfs(G, START_VERTEX, curr, shortest, cities, outfile, verbose);
    path_print(shortest, outfile, cities);
    fprintf(outfile, "Recursive Calls: %d\n", recursive_calls);

    ////////////////////////////////////////////////////////////////////////////////////
    //USE THE SECTION BELOW TO FREE MEMORY

    for (int i = 0; i < vertices; ++i) { //free each item in array
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
    }
    return;
}

//finds the shortest hamiltonian path for a given graph
//Returns nothing
//
//G: input graph
//v: starting vertex
//curr: current path
//shortest: shortest path
//cities[]: an array of cities
//outfile: how you want the program to be outputted
//vertices: number of vertices in the graph
//verbos: enables verbose printing
//
//NOTE: DFS algorithm was based from the assignment pdf pseudocode
void dfs(
    Graph *G, uint32_t v, Path *curr, Path *shortest, char *cities[], FILE *outfile, bool verbose) {

    recursive_calls++;
    uint32_t z = 0; //keeps track of the popped vertices

    graph_mark_visited(G, v);
    path_push_vertex(curr, v, G);

    if (path_vertices(curr) >= graph_vertices(G) && graph_has_edge(G, v, START_VERTEX)) {
        //check if we reached a full hamiltonian path
        path_push_vertex(curr, START_VERTEX, G);
        if (verbose) { //print all hamiltonian paths if this is called
            path_print(curr, outfile, cities);
        }

        if (path_length(shortest) == 0) {
            path_copy(shortest, curr);
        } else if (path_length(curr) < path_length(shortest)) {
            path_copy(shortest, curr);
        }

        path_pop_vertex(curr, &z, G);
    }

    for (uint32_t w = 0; w <= graph_vertices(G); ++w) {
        if (!graph_visited(G, w) && graph_has_edge(G, v, w)) {
            dfs(G, w, curr, shortest, cities, outfile, verbose);
        }
    }
    path_pop_vertex(curr, &z, G);
    graph_mark_unvisited(G, v);
    return;
}
