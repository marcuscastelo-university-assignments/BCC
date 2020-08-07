#include "graph.h"
#include "list.h"

#include <stdio.h>
#include <stdlib.h>


struct graph_ {
    short n;
    List **adjacency_list;
};

Graph *graph_create(short n) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->adjacency_list = malloc(n * sizeof(List*));
    for (short i = 0; i < n; i++)
    {
        g->adjacency_list[i] = list_create();
    }
    return g;
}


void graph_delete(Graph **g_ptr) {
    if (g_ptr == NULL || *g_ptr == NULL) return;
    for (short i = 0; i < (*g_ptr)->n; i++)
        list_delete(&(*g_ptr)->adjacency_list[i]);
    free((*g_ptr)->adjacency_list);
    free(*g_ptr);
    *g_ptr = NULL;    
}

void graph_insert(Graph *g, short u, short v) {
    // printf("Adding (%d,%d)", u, v);
    list_add(g->adjacency_list[u],v);
    list_add(g->adjacency_list[v],u);
}

void graph_remove(Graph *g, short u, short v) {
    // printf("Removing (%d,%d)...\n", u, v);
    list_remove(g->adjacency_list[u],v);
    list_remove(g->adjacency_list[v],u);
}

void graph_print(Graph *g) {
    for (short i = 0; i < g->n; i++)
    {
        printf("%d: ", i);
        list_print(g->adjacency_list[i]);
    }
    printf("\n");
}