#ifndef GRAPH_H
#define GRAPH_H

#include "utils.h"

typedef struct Graph {
    int vertices;
    int **adj_matrix;
} Graph;

Graph* create_graph(int vertices);
void add_edge(Graph* graph, int src, int dest, int weight);
void print_graph(Graph* graph);
bool is_connected(Graph* graph);
void destroy_graph(Graph* graph);

#endif