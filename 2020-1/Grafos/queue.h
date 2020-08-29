#pragma once

typedef struct queue_ Queue;

Queue *queue_create();

void queue_insert(Queue*, int value);
int queue_pop(Queue*);
int queue_is_empty(Queue*);

void queue_delete(Queue**);