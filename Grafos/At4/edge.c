#include "edge.h"
#include <stdlib.h>

Edge *create_edge(int to, int time, int cost) {
    Edge *edge = malloc(sizeof(Edge));
    edge->to = to;
    edge->time = time;
    edge->cost = cost;
    return edge;
}

void delete_edge(Edge **edge_ptr) {
    
}