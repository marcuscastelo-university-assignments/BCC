#pragma once

typedef struct pq_ PriorityQueue;

typedef struct 
{
    int cityID, dist;
} PQPopPair;


PriorityQueue *pq_create(int cityQty);
void pq_delete(PriorityQueue **pq_ptr);
//Returns true if newDist < oldDist (if relaxed)
char pq_relax(PriorityQueue *pq, int cityID, int newDist);
char pq_is_empty(PriorityQueue *pq);
PQPopPair pq_pop(PriorityQueue *pq);