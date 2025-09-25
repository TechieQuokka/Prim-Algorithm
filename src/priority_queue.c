#include "priority_queue.h"

static void swap_nodes(PriorityQueue* pq, int i, int j) {
    int temp_vertex = pq->heap[i];
    pq->heap[i] = pq->heap[j];
    pq->heap[j] = temp_vertex;

    pq->pos[pq->heap[i]] = i;
    pq->pos[pq->heap[j]] = j;
}

static void heapify_up(PriorityQueue* pq, int idx) {
    while (idx > 0) {
        int parent = (idx - 1) / 2;
        if (pq->key[pq->heap[idx]] >= pq->key[pq->heap[parent]]) {
            break;
        }
        swap_nodes(pq, idx, parent);
        idx = parent;
    }
}

static void heapify_down(PriorityQueue* pq, int idx) {
    int smallest = idx;

    while (true) {
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < pq->size &&
            pq->key[pq->heap[left]] < pq->key[pq->heap[smallest]]) {
            smallest = left;
        }

        if (right < pq->size &&
            pq->key[pq->heap[right]] < pq->key[pq->heap[smallest]]) {
            smallest = right;
        }

        if (smallest == idx) {
            break;
        }

        swap_nodes(pq, idx, smallest);
        idx = smallest;
    }
}

PriorityQueue* create_pq(int max_size) {
    if (max_size <= 0) {
        error_exit("Priority queue size must be positive");
    }

    PriorityQueue* pq = (PriorityQueue*)safe_malloc(sizeof(PriorityQueue));

    pq->heap = (int*)safe_malloc(max_size * sizeof(int));
    pq->pos = (int*)safe_malloc(max_size * sizeof(int));
    pq->key = (int*)safe_malloc(max_size * sizeof(int));

    pq->size = 0;
    pq->capacity = max_size;

    for (int i = 0; i < max_size; i++) {
        pq->pos[i] = -1;
        pq->key[i] = INF;
    }

    debug_print("Created priority queue with capacity %d", max_size);
    return pq;
}

void insert_pq(PriorityQueue* pq, int vertex, int key) {
    if (!pq) {
        error_exit("Priority queue is NULL");
    }

    if (vertex < 0 || vertex >= pq->capacity) {
        error_exit("Invalid vertex index");
    }

    if (pq->size >= pq->capacity) {
        error_exit("Priority queue is full");
    }

    if (pq->pos[vertex] != -1) {
        error_exit("Vertex already in priority queue");
    }

    pq->key[vertex] = key;
    pq->heap[pq->size] = vertex;
    pq->pos[vertex] = pq->size;
    pq->size++;

    heapify_up(pq, pq->size - 1);

    debug_print("Inserted vertex %d with key %d", vertex, key);
}

int extract_min(PriorityQueue* pq) {
    if (!pq) {
        error_exit("Priority queue is NULL");
    }

    if (pq->size == 0) {
        error_exit("Priority queue is empty");
    }

    int min_vertex = pq->heap[0];
    int last_vertex = pq->heap[pq->size - 1];

    pq->heap[0] = last_vertex;
    pq->pos[last_vertex] = 0;
    pq->pos[min_vertex] = -1;
    pq->size--;

    if (pq->size > 0) {
        heapify_down(pq, 0);
    }

    debug_print("Extracted min vertex %d with key %d", min_vertex, pq->key[min_vertex]);
    return min_vertex;
}

void decrease_key(PriorityQueue* pq, int vertex, int new_key) {
    if (!pq) {
        error_exit("Priority queue is NULL");
    }

    if (vertex < 0 || vertex >= pq->capacity) {
        error_exit("Invalid vertex index");
    }

    if (pq->pos[vertex] == -1) {
        error_exit("Vertex not in priority queue");
    }

    if (new_key > pq->key[vertex]) {
        error_exit("New key is greater than current key");
    }

    int old_key = pq->key[vertex];
    pq->key[vertex] = new_key;

    heapify_up(pq, pq->pos[vertex]);

    debug_print("Decreased key of vertex %d from %d to %d", vertex, old_key, new_key);
}

bool is_empty_pq(PriorityQueue* pq) {
    return pq ? (pq->size == 0) : true;
}

bool is_in_pq(PriorityQueue* pq, int vertex) {
    if (!pq || vertex < 0 || vertex >= pq->capacity) {
        return false;
    }
    return pq->pos[vertex] != -1;
}

void destroy_pq(PriorityQueue* pq) {
    if (!pq) {
        return;
    }

    safe_free((void**)&pq->heap);
    safe_free((void**)&pq->pos);
    safe_free((void**)&pq->key);

    debug_print("Destroyed priority queue with capacity %d", pq->capacity);
    safe_free((void**)&pq);
}