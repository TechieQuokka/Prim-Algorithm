#include "prim.h"
#include <time.h>

void print_menu() {
    printf("\n====== Prim's Algorithm Demo ======\n");
    printf("1. Run Example 1 (Simple 4-vertex graph)\n");
    printf("2. Run Example 2 (Complete 5-vertex graph)\n");
    printf("3. Run Example 3 (Linear graph)\n");
    printf("4. Run Custom Graph\n");
    printf("5. Compare Algorithms (Heap vs Simple)\n");
    printf("0. Exit\n");
    printf("===================================\n");
    printf("Choose an option: ");
}

Graph* create_example_graph_1() {
    Graph* graph = create_graph(4);

    add_edge(graph, 0, 1, 10);
    add_edge(graph, 0, 2, 6);
    add_edge(graph, 0, 3, 5);
    add_edge(graph, 1, 3, 15);
    add_edge(graph, 2, 3, 4);

    return graph;
}

Graph* create_example_graph_2() {
    Graph* graph = create_graph(5);

    add_edge(graph, 0, 1, 2);
    add_edge(graph, 0, 3, 6);
    add_edge(graph, 1, 2, 3);
    add_edge(graph, 1, 3, 8);
    add_edge(graph, 1, 4, 5);
    add_edge(graph, 2, 4, 7);
    add_edge(graph, 3, 4, 9);

    return graph;
}

Graph* create_example_graph_3() {
    Graph* graph = create_graph(6);

    add_edge(graph, 0, 1, 4);
    add_edge(graph, 1, 2, 8);
    add_edge(graph, 2, 3, 7);
    add_edge(graph, 3, 4, 9);
    add_edge(graph, 4, 5, 10);
    add_edge(graph, 2, 5, 4);
    add_edge(graph, 3, 5, 14);

    return graph;
}

Graph* create_custom_graph() {
    int vertices, edges;

    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    if (vertices <= 0 || vertices > 100) {
        printf("Invalid number of vertices. Using default (4).\n");
        vertices = 4;
    }

    Graph* graph = create_graph(vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    if (edges < 0) {
        edges = 0;
    }

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < edges; i++) {
        int src, dest, weight;
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &src, &dest, &weight);

        if (src >= 0 && src < vertices &&
            dest >= 0 && dest < vertices &&
            weight >= 0) {
            add_edge(graph, src, dest, weight);
        } else {
            printf("Invalid edge parameters. Skipping.\n");
            i--;
        }
    }

    return graph;
}

void run_example(int example_num) {
    Graph* graph = NULL;
    const char* description = NULL;

    switch (example_num) {
        case 1:
            graph = create_example_graph_1();
            description = "Simple 4-vertex graph";
            break;
        case 2:
            graph = create_example_graph_2();
            description = "Complete 5-vertex graph";
            break;
        case 3:
            graph = create_example_graph_3();
            description = "Linear graph with cycles";
            break;
        case 4:
            graph = create_custom_graph();
            description = "Custom graph";
            break;
        default:
            printf("Invalid example number.\n");
            return;
    }

    if (!graph) {
        printf("Failed to create graph.\n");
        return;
    }

    printf("\n=== %s ===\n", description);
    print_graph(graph);

    if (!is_connected(graph)) {
        printf("Warning: Graph is not connected. MST may not be complete.\n");
        destroy_graph(graph);
        return;
    }

    printf("Running Prim's Algorithm (starting from vertex 0):\n");

    MST_Result* result = prim_mst(graph, 0);

    if (result) {
        print_mst(result);

        if (validate_mst(graph, result)) {
            printf("\n✓ MST validation successful!\n");
        } else {
            printf("\n✗ MST validation failed!\n");
        }

        destroy_mst_result(result);
    }

    destroy_graph(graph);
}

void compare_algorithms() {
    printf("\n=== Algorithm Comparison ===\n");

    Graph* graph = create_example_graph_2();
    print_graph(graph);

    clock_t start, end;
    double heap_time, simple_time;

    printf("Running Heap-based Prim's Algorithm:\n");
    start = clock();
    MST_Result* heap_result = prim_mst(graph, 0);
    end = clock();
    heap_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nRunning Simple Prim's Algorithm:\n");
    start = clock();
    MST_Result* simple_result = prim_mst_simple(graph, 0);
    end = clock();
    simple_time = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n=== Results Comparison ===\n");

    printf("\nHeap-based Algorithm:\n");
    print_mst(heap_result);
    printf("Execution time: %.6f seconds\n", heap_time);

    printf("\nSimple Algorithm:\n");
    print_mst(simple_result);
    printf("Execution time: %.6f seconds\n", simple_time);

    printf("\n=== Performance Analysis ===\n");
    printf("Heap-based algorithm: O(E log V) - Better for dense graphs\n");
    printf("Simple algorithm: O(V²) - Better for sparse graphs\n");

    if (heap_result->total_weight == simple_result->total_weight) {
        printf("✓ Both algorithms found MST with same total weight: %d\n",
               heap_result->total_weight);
    } else {
        printf("✗ Algorithms found different MST weights!\n");
    }

    destroy_mst_result(heap_result);
    destroy_mst_result(simple_result);
    destroy_graph(graph);
}

int main() {
    printf("Prim's Minimum Spanning Tree Algorithm Implementation\n");
    printf("===================================================\n");

    int choice;

    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2:
            case 3:
            case 4:
                run_example(choice);
                break;
            case 5:
                compare_algorithms();
                break;
            case 0:
                printf("Thank you for using Prim's Algorithm Demo!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }

        if (choice != 0) {
            printf("\nPress Enter to continue...");
            getchar();
            getchar();
        }

    } while (choice != 0);

    return 0;
}