#include "graph.h"

Graph* create_graph(int vertices) {
    if (vertices <= 0) {
        error_exit("Number of vertices must be positive");
    }

    Graph* graph = (Graph*)safe_malloc(sizeof(Graph));
    graph->vertices = vertices;

    graph->adj_matrix = (int**)safe_malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph->adj_matrix[i] = (int*)safe_malloc(vertices * sizeof(int));
        for (int j = 0; j < vertices; j++) {
            graph->adj_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    debug_print("Created graph with %d vertices", vertices);
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight) {
    if (!graph) {
        error_exit("Graph is NULL");
    }

    if (src < 0 || src >= graph->vertices || dest < 0 || dest >= graph->vertices) {
        error_exit("Invalid vertex indices");
    }

    if (weight < 0) {
        error_exit("Weight cannot be negative");
    }

    if (src == dest) {
        debug_print("Self-loop ignored: vertex %d", src);
        return;
    }

    graph->adj_matrix[src][dest] = weight;
    graph->adj_matrix[dest][src] = weight;

    debug_print("Added edge: %d -- %d (weight: %d)", src, dest, weight);
}

void print_graph(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL\n");
        return;
    }

    printf("\nGraph Adjacency Matrix (%d vertices):\n", graph->vertices);
    printf("     ");
    for (int i = 0; i < graph->vertices; i++) {
        printf("%4d", i);
    }
    printf("\n");

    for (int i = 0; i < graph->vertices; i++) {
        printf("%4d:", i);
        for (int j = 0; j < graph->vertices; j++) {
            if (graph->adj_matrix[i][j] == INF) {
                printf(" INF");
            } else {
                printf("%4d", graph->adj_matrix[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

bool is_connected(Graph* graph) {
    if (!graph || graph->vertices <= 0) {
        return false;
    }

    if (graph->vertices == 1) {
        return true;
    }

    bool* visited = (bool*)safe_malloc(graph->vertices * sizeof(bool));
    for (int i = 0; i < graph->vertices; i++) {
        visited[i] = false;
    }

    int* stack = (int*)safe_malloc(graph->vertices * sizeof(int));
    int top = 0;

    stack[top] = 0;
    visited[0] = true;
    int visited_count = 1;

    while (top >= 0) {
        int current = stack[top--];

        for (int i = 0; i < graph->vertices; i++) {
            if (!visited[i] && graph->adj_matrix[current][i] != INF) {
                visited[i] = true;
                stack[++top] = i;
                visited_count++;
            }
        }
    }

    bool connected = (visited_count == graph->vertices);

    safe_free((void**)&visited);
    safe_free((void**)&stack);

    return connected;
}

void destroy_graph(Graph* graph) {
    if (!graph) {
        return;
    }

    if (graph->adj_matrix) {
        for (int i = 0; i < graph->vertices; i++) {
            safe_free((void**)&graph->adj_matrix[i]);
        }
        safe_free((void**)&graph->adj_matrix);
    }

    debug_print("Destroyed graph with %d vertices", graph->vertices);
    safe_free((void**)&graph);
}