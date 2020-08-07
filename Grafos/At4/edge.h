#pragma once

typedef struct edge_ Edge;

struct edge_ {
    int to, time, cost;
};

Edge *create_edge(int to, int time, int cost);
void delete_edge(Edge **edge_ptr);