#ifndef QUEUE_H
#define QUEUE_H
#include "task.h"
#include <pthread.h>

typedef struct Node {
    task t;
    struct Node* next;
} Node;

typedef struct {
    Node *front, *rear;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} TaskQueue;

typedef struct {
    char* outputs[1000]; // Stores results by ID
    pthread_mutex_t lock;
} ResultStore;

void init_queue(TaskQueue* q);
void enqueue(TaskQueue* q, task t);
task dequeue(TaskQueue* q);
void init_store(ResultStore* s);
void store_result(ResultStore* s, int id, const char* res);
char* get_from_store(ResultStore* s, int id);

#endif
