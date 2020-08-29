#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

#define INF 0x6FFFFFFF
typedef struct node_ Node;

struct node_ {
    char visited;
    int cityID, dist;
};

struct pq_ {
    Node **node_arr;
    int nodeQty;
};

Node *node_create(int cityID, int dist) {
    Node *node = malloc(sizeof(Node));
    node->cityID = cityID;
    node->dist = dist;
    node->visited = 0;
    return node;
}

void node_delete(Node **node_ptr) {
    #define node (*node_ptr)
    if (node_ptr == NULL || node == NULL) {
        DP("Trying to delete null node pq@node_del\n");
        return;
    }

    node->cityID = 0;
    node->dist = 0;
    free(node);

    node = NULL;
    #undef node
}

Node *pq_find(PriorityQueue *pq, int cityID) {
    for (int  i = 0; i < pq->nodeQty; i++) 
        if (pq->node_arr[i]->cityID == cityID) 
            return pq->node_arr[i];
    return NULL;
}

PriorityQueue *pq_create(int cityQty) {
    PriorityQueue *pq = malloc(sizeof(PriorityQueue));
    pq->node_arr = malloc(cityQty * sizeof(Node*));
    pq->nodeQty = cityQty;

    for (int i = 0; i < cityQty; i++) pq->node_arr[i] = node_create(i, INF);    

    return pq;
}

void pq_delete(PriorityQueue **pq_ptr) {
    #define pq (*pq_ptr)
    if (pq_ptr == NULL || pq == NULL) {
        DP("Trying to delete null pq\n");
        return;
    }

    for (int i = 0; i < pq->nodeQty; i++)
        node_delete(&pq->node_arr[i]);
    
    pq->nodeQty = 0;
    free(pq->node_arr);
    free(pq);
    pq = NULL;

    #undef pq
}

char pq_is_empty(PriorityQueue *pq) {
    for (int i = 0; i < pq->nodeQty; i++)
    {
        if (pq->node_arr[i]->visited == 0)
            return 0;
    }
    return 1;    
}

char pq_relax(PriorityQueue *pq, int cityID, int newDist) {
    Node *nodeToRelax = pq_find(pq, cityID);
    if (nodeToRelax == NULL) {
        DP("Trying to relax inexistent city: %d\n", cityID);
        return -1;
    }

    if (newDist < nodeToRelax->dist){
        nodeToRelax->dist = newDist;
        return 1;
    }

    return 0;
}

Node *pq_get_min_dist_node(PriorityQueue *pq) {
    int minDist = INF+1;
    Node *minNode = NULL;
    for (int i = 0; i < pq->nodeQty; i++)
    {
        if (pq->node_arr[i]->visited == 1) continue;
        if (pq->node_arr[i]->dist < minDist) {
            minDist = pq->node_arr[i]->dist;
            minNode = pq->node_arr[i];
        }   
    }
    
    return minNode;
}

PQPopPair pq_pop(PriorityQueue *pq) {
    Node *node = pq_get_min_dist_node(pq);
    if (node == NULL) {
        return (PQPopPair) {-1,-1};
    }
    int dist = node->dist;
    node->visited = 1;
    return (PQPopPair) { node->cityID, dist };
}