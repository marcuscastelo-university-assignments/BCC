#include "graph.h"

#include <stdlib.h>
#include "debug.h"

struct graph_ {
    int nodeQty;
    List **edges_per_node;
};

struct node_ {

};

Graph *graph_create(int nodeQty) {
    Graph *graph = malloc(sizeof(Graph));

    graph->nodeQty = nodeQty;
    graph->edges_per_node = malloc(nodeQty * sizeof(List*));
    for (int i = 0; i < nodeQty; i++)
        graph->edges_per_node[i] = list_create();

    return graph;
}

void graph_delete(Graph **graph_ptr) {
    #define graph (*graph_ptr)
    if (graph_ptr == NULL || graph == NULL) {
        DP("Trying to delete null graph\n");
        return;
    }
    
    for (int i = 0; i < graph->nodeQty; i++)
        list_delete(&graph->edges_per_node[i]);

    graph->nodeQty=0;
    free(graph->edges_per_node);    
    free(graph);
    graph = NULL;

    #undef graph

}

void graph_insert_edge(Graph *graph, int from, Edge *edge) {
    list_insert(graph->edges_per_node[from], edge);
}

List *graph_get_edges(Graph *graph, int from) {
    return graph->edges_per_node[from];
}