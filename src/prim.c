#include "prim.h"

MST_Result* create_mst_result(int vertices) {
    MST_Result* result = (MST_Result*)safe_malloc(sizeof(MST_Result));

    result->parent = (int*)safe_malloc(vertices * sizeof(int));
    result->key = (int*)safe_malloc(vertices * sizeof(int));
    result->total_weight = 0;
    result->vertex_count = vertices;

    for (int i = 0; i < vertices; i++) {
        result->parent[i] = -1;
        result->key[i] = INF;
    }

    return result;
}

MST_Result* prim_mst(Graph* graph, int start_vertex) {
    if (!graph) {
        error_exit("Graph is NULL");
    }

    if (start_vertex < 0 || start_vertex >= graph->vertices) {
        error_exit("Invalid start vertex");
    }

    if (!is_connected(graph)) {
        error_exit("Graph is not connected");
    }

    int vertices = graph->vertices;
    MST_Result* result = create_mst_result(vertices);

    PriorityQueue* pq = create_pq(vertices);

    bool* in_mst = (bool*)safe_malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        in_mst[i] = false;
    }

    result->key[start_vertex] = 0;
    for (int i = 0; i < vertices; i++) {
        insert_pq(pq, i, result->key[i]);
    }

    debug_print("Starting Prim's algorithm from vertex %d", start_vertex);

    while (!is_empty_pq(pq)) {
        int u = extract_min(pq);
        in_mst[u] = true;

        debug_print("Added vertex %d to MST (key: %d)", u, result->key[u]);

        if (u != start_vertex) {
            result->total_weight += result->key[u];
        }

        for (int v = 0; v < vertices; v++) {
            if (graph->adj_matrix[u][v] != INF &&
                !in_mst[v] &&
                is_in_pq(pq, v) &&
                graph->adj_matrix[u][v] < result->key[v]) {

                result->parent[v] = u;
                result->key[v] = graph->adj_matrix[u][v];
                decrease_key(pq, v, result->key[v]);

                debug_print("Updated vertex %d: parent=%d, key=%d",
                           v, result->parent[v], result->key[v]);
            }
        }
    }

    safe_free((void**)&in_mst);
    destroy_pq(pq);

    debug_print("Prim's algorithm completed. Total weight: %d", result->total_weight);
    return result;
}

MST_Result* prim_mst_simple(Graph* graph, int start_vertex) {
    if (!graph) {
        error_exit("Graph is NULL");
    }

    if (start_vertex < 0 || start_vertex >= graph->vertices) {
        error_exit("Invalid start vertex");
    }

    if (!is_connected(graph)) {
        error_exit("Graph is not connected");
    }

    int vertices = graph->vertices;
    MST_Result* result = create_mst_result(vertices);

    bool* in_mst = (bool*)safe_malloc(vertices * sizeof(bool));
    for (int i = 0; i < vertices; i++) {
        in_mst[i] = false;
        result->key[i] = INF;
        result->parent[i] = -1;
    }

    result->key[start_vertex] = 0;

    debug_print("Starting simple Prim's algorithm from vertex %d", start_vertex);

    for (int count = 0; count < vertices; count++) {
        int min_key = INF;
        int u = -1;

        for (int v = 0; v < vertices; v++) {
            if (!in_mst[v] && result->key[v] < min_key) {
                min_key = result->key[v];
                u = v;
            }
        }

        if (u == -1) {
            error_exit("Graph is not connected");
        }

        in_mst[u] = true;
        if (u != start_vertex) {
            result->total_weight += result->key[u];
        }

        debug_print("Added vertex %d to MST (key: %d)", u, result->key[u]);

        for (int v = 0; v < vertices; v++) {
            if (graph->adj_matrix[u][v] != INF &&
                !in_mst[v] &&
                graph->adj_matrix[u][v] < result->key[v]) {

                result->parent[v] = u;
                result->key[v] = graph->adj_matrix[u][v];

                debug_print("Updated vertex %d: parent=%d, key=%d",
                           v, result->parent[v], result->key[v]);
            }
        }
    }

    safe_free((void**)&in_mst);

    debug_print("Simple Prim's algorithm completed. Total weight: %d", result->total_weight);
    return result;
}

void print_mst(MST_Result* result) {
    if (!result) {
        printf("MST Result is NULL\n");
        return;
    }

    printf("\nMinimum Spanning Tree:\n");
    printf("Edge\t\tWeight\n");
    printf("----\t\t------\n");

    for (int i = 0; i < result->vertex_count; i++) {
        if (result->parent[i] != -1) {
            printf("%d -- %d\t\t%d\n", result->parent[i], i, result->key[i]);
        }
    }

    printf("\nTotal weight of MST: %d\n", result->total_weight);
    printf("Number of edges: %d\n", result->vertex_count - 1);
}

bool validate_mst(Graph* graph, MST_Result* result) {
    if (!graph || !result) {
        return false;
    }

    if (graph->vertices != result->vertex_count) {
        return false;
    }

    int edge_count = 0;
    int calculated_weight = 0;

    for (int i = 0; i < result->vertex_count; i++) {
        if (result->parent[i] != -1) {
            edge_count++;

            if (result->parent[i] < 0 || result->parent[i] >= graph->vertices) {
                debug_print("Invalid parent index: %d", result->parent[i]);
                return false;
            }

            if (graph->adj_matrix[result->parent[i]][i] != result->key[i]) {
                debug_print("Edge weight mismatch: expected %d, got %d",
                           graph->adj_matrix[result->parent[i]][i], result->key[i]);
                return false;
            }

            calculated_weight += result->key[i];
        }
    }

    if (edge_count != result->vertex_count - 1) {
        debug_print("Wrong number of edges: expected %d, got %d",
                   result->vertex_count - 1, edge_count);
        return false;
    }

    if (calculated_weight != result->total_weight) {
        debug_print("Total weight mismatch: expected %d, got %d",
                   calculated_weight, result->total_weight);
        return false;
    }

    return true;
}

void destroy_mst_result(MST_Result* result) {
    if (!result) {
        return;
    }

    safe_free((void**)&result->parent);
    safe_free((void**)&result->key);

    debug_print("Destroyed MST result with %d vertices", result->vertex_count);
    safe_free((void**)&result);
}