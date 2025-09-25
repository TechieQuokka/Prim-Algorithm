#ifndef PRIM_H
#define PRIM_H

#include "graph.h"
#include "priority_queue.h"

typedef struct MST_Result {
    int *parent;
    int *key;
    int total_weight;
    int vertex_count;
} MST_Result;

MST_Result* prim_mst(Graph* graph, int start_vertex);
MST_Result* prim_mst_simple(Graph* graph, int start_vertex);
void print_mst(MST_Result* result);
bool validate_mst(Graph* graph, MST_Result* result);
void destroy_mst_result(MST_Result* result);

#endif