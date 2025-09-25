#include "../include/prim.h"
#include <assert.h>

void test_utils() {
    printf("Testing utility functions...\n");

    void* ptr = safe_malloc(100);
    assert(ptr != NULL);
    safe_free(&ptr);
    assert(ptr == NULL);

    printf("✓ Utility functions test passed\n");
}

void test_graph_creation() {
    printf("Testing graph creation...\n");

    Graph* graph = create_graph(5);
    assert(graph != NULL);
    assert(graph->vertices == 5);
    assert(graph->adj_matrix != NULL);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (i == j) {
                assert(graph->adj_matrix[i][j] == 0);
            } else {
                assert(graph->adj_matrix[i][j] == INF);
            }
        }
    }

    destroy_graph(graph);
    printf("✓ Graph creation test passed\n");
}

void test_graph_edges() {
    printf("Testing graph edge operations...\n");

    Graph* graph = create_graph(4);

    add_edge(graph, 0, 1, 10);
    assert(graph->adj_matrix[0][1] == 10);
    assert(graph->adj_matrix[1][0] == 10);

    add_edge(graph, 1, 2, 20);
    assert(graph->adj_matrix[1][2] == 20);
    assert(graph->adj_matrix[2][1] == 20);

    assert(is_connected(graph) == false);

    add_edge(graph, 2, 3, 30);
    assert(graph->adj_matrix[2][3] == 30);
    assert(graph->adj_matrix[3][2] == 30);

    add_edge(graph, 0, 2, 5);
    assert(is_connected(graph) == true);

    destroy_graph(graph);
    printf("✓ Graph edge operations test passed\n");
}

void test_priority_queue() {
    printf("Testing priority queue...\n");

    PriorityQueue* pq = create_pq(5);
    assert(pq != NULL);
    assert(is_empty_pq(pq) == true);

    insert_pq(pq, 0, 10);
    insert_pq(pq, 1, 5);
    insert_pq(pq, 2, 15);
    insert_pq(pq, 3, 3);
    insert_pq(pq, 4, 8);

    assert(is_empty_pq(pq) == false);

    assert(extract_min(pq) == 3);
    assert(extract_min(pq) == 1);

    decrease_key(pq, 2, 7);

    assert(extract_min(pq) == 2);
    assert(extract_min(pq) == 4);
    assert(extract_min(pq) == 0);

    assert(is_empty_pq(pq) == true);

    destroy_pq(pq);
    printf("✓ Priority queue test passed\n");
}

void test_simple_mst() {
    printf("Testing simple MST case...\n");

    Graph* graph = create_graph(4);
    add_edge(graph, 0, 1, 10);
    add_edge(graph, 0, 2, 6);
    add_edge(graph, 0, 3, 5);
    add_edge(graph, 1, 3, 15);
    add_edge(graph, 2, 3, 4);

    MST_Result* result = prim_mst(graph, 0);
    assert(result != NULL);
    assert(result->total_weight == 19);
    assert(validate_mst(graph, result) == true);

    printf("Expected total weight: 19, Actual: %d\n", result->total_weight);

    destroy_mst_result(result);
    destroy_graph(graph);
    printf("✓ Simple MST test passed\n");
}

void test_algorithm_comparison() {
    printf("Testing algorithm comparison...\n");

    Graph* graph = create_graph(5);
    add_edge(graph, 0, 1, 2);
    add_edge(graph, 0, 3, 6);
    add_edge(graph, 1, 2, 3);
    add_edge(graph, 1, 3, 8);
    add_edge(graph, 1, 4, 5);
    add_edge(graph, 2, 4, 7);
    add_edge(graph, 3, 4, 9);

    MST_Result* heap_result = prim_mst(graph, 0);
    MST_Result* simple_result = prim_mst_simple(graph, 0);

    assert(heap_result != NULL);
    assert(simple_result != NULL);
    assert(heap_result->total_weight == simple_result->total_weight);
    assert(validate_mst(graph, heap_result) == true);
    assert(validate_mst(graph, simple_result) == true);

    printf("Both algorithms found MST with weight: %d\n", heap_result->total_weight);

    destroy_mst_result(heap_result);
    destroy_mst_result(simple_result);
    destroy_graph(graph);
    printf("✓ Algorithm comparison test passed\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");

    Graph* single_vertex = create_graph(1);
    assert(is_connected(single_vertex) == true);

    MST_Result* single_result = prim_mst(single_vertex, 0);
    assert(single_result->total_weight == 0);
    assert(validate_mst(single_vertex, single_result) == true);

    destroy_mst_result(single_result);
    destroy_graph(single_vertex);

    Graph* two_vertex = create_graph(2);
    add_edge(two_vertex, 0, 1, 5);

    MST_Result* two_result = prim_mst(two_vertex, 0);
    assert(two_result->total_weight == 5);
    assert(validate_mst(two_vertex, two_result) == true);

    destroy_mst_result(two_result);
    destroy_graph(two_vertex);

    printf("✓ Edge cases test passed\n");
}

void test_performance() {
    printf("Testing performance with larger graph...\n");

    const int vertices = 20;
    Graph* graph = create_graph(vertices);

    srand(42);
    for (int i = 0; i < vertices; i++) {
        for (int j = i + 1; j < vertices; j++) {
            if (rand() % 3 == 0) {
                int weight = (rand() % 50) + 1;
                add_edge(graph, i, j, weight);
            }
        }
    }

    if (is_connected(graph)) {
        MST_Result* result = prim_mst(graph, 0);
        assert(result != NULL);
        assert(validate_mst(graph, result) == true);
        printf("Large graph MST weight: %d\n", result->total_weight);
        destroy_mst_result(result);
    } else {
        printf("Generated graph is not connected, skipping MST test\n");
    }

    destroy_graph(graph);
    printf("✓ Performance test completed\n");
}

int main() {
    printf("Running Prim's Algorithm Test Suite\n");
    printf("===================================\n\n");

    test_utils();
    test_graph_creation();
    test_graph_edges();
    test_priority_queue();
    test_simple_mst();
    test_algorithm_comparison();
    test_edge_cases();
    test_performance();

    printf("\n===================================\n");
    printf("All tests passed successfully! ✓\n");
    printf("===================================\n");

    return 0;
}