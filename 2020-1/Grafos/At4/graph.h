#pragma once

#include "edge.h"
#include "list.h"

typedef struct graph_ Graph;
typedef struct node_ Node;

Graph *graph_create(int nodeQty);
void graph_delete(Graph **graph_ptr);
void graph_insert_edge(Graph *graph, int from, Edge *edge);
List *graph_get_edges(Graph *graph, int from);