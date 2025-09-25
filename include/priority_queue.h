#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "utils.h"

typedef struct PriorityQueue {
    int *heap;
    int *pos;
    int *key;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* create_pq(int max_size);
void insert_pq(PriorityQueue* pq, int vertex, int key);
int extract_min(PriorityQueue* pq);
void decrease_key(PriorityQueue* pq, int vertex, int new_key);
bool is_empty_pq(PriorityQueue* pq);
bool is_in_pq(PriorityQueue* pq, int vertex);
void destroy_pq(PriorityQueue* pq);

#endif