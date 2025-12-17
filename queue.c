#include "queue.h"
#include <stdlib.h>
#include <string.h>

void init_queue(TaskQueue* q) {
    q->front = q->rear = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
}

void enqueue(TaskQueue* q, task t) {
    pthread_mutex_lock(&q->lock);
    Node* temp = malloc(sizeof(Node));
    temp->t = t;
    temp->t.payload = strdup(t.payload);
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
    } else {
        q->rear->next = temp;
        q->rear = temp;
    }
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->lock);
}

task dequeue(TaskQueue* q) {
    pthread_mutex_lock(&q->lock);
    while (q->front == NULL)
        pthread_cond_wait(&q->cond, &q->lock);
    Node* temp = q->front;
    task t = temp->t;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(temp);
    pthread_mutex_unlock(&q->lock);
    return t;
}

void init_store(ResultStore* s) {
    pthread_mutex_init(&s->lock, NULL);
    for(int i=0; i<1000; i++) s->outputs[i] = NULL;
}

void store_result(ResultStore* s, int id, const char* res) {
    pthread_mutex_lock(&s->lock);
    s->outputs[id] = strdup(res);
    pthread_mutex_unlock(&s->lock);
}

char* get_from_store(ResultStore* s, int id) {
    pthread_mutex_lock(&s->lock);
    char* res = (id >= 0 && id < 1000) ? s->outputs[id] : NULL;
    pthread_mutex_unlock(&s->lock);
    return res;
}
