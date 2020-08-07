#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct node_ {
    int value;
    struct node_ *next;
} Node;

struct queue_
{
    Node *start, *end;
};

Node* create_node(int value) {
    Node *n = malloc(sizeof(Node));
    n -> value = value;
    n -> next = NULL;
    return n;
}

Queue *queue_create() {
    Queue *queue = malloc(sizeof(Queue));
    queue -> start = queue -> end = NULL;
    return queue;
}

void queue_insert(Queue* q, int value) {
    if (q->end == NULL) q->start = q->end = create_node(value);
    else if (q->end == q->start) q->start->next = q->end = create_node(value);
    else { q->end->next = create_node(value); q->end = q->end->next; }
}

int queue_pop(Queue* q) {
    if (q -> start == NULL) {
        fprintf(stderr, "ERROR: trying to pop empty list!!!\n");
        return -1;
    }
    int value = q->start->value;
    Node *n = q->start;
    q->start = q->start->next;
    if (q->start == NULL) q->end = NULL;
    free(n);
    return value;
}

int queue_is_empty(Queue* q) {
    return q->start == NULL;
}

void queue_delete(Queue** q_p) {
    #define q (*q_p)
    Node *to_delete = NULL;
    while (q->start != NULL) {
        to_delete = q->start;
        q->start = q->start->next;
        free(to_delete);
    }
    q->end = NULL;
    free(q);
    q = NULL;
    #undef q
}