#include "graph.h"

#include <stdio.h>
#include <stdlib.h>

struct graph_ {
    short n;
    char **adjacency_matrix;
};

Graph *graph_create(short n) {
    Graph *g = malloc(sizeof(Graph));
    g->n = n;
    g->adjacency_matrix = malloc(n * sizeof(char *));
    for (short i = 0; i < n; i++)
        g->adjacency_matrix[i] = calloc(n, sizeof(char));    
    return g;
}


void graph_delete(Graph **g_ptr) {
    if (g_ptr == NULL || *g_ptr == NULL) return;
    for (short i = 0; i < (*g_ptr)->n; i++)
        free((*g_ptr)->adjacency_matrix[i]);
    free((*g_ptr)->adjacency_matrix);
    free(*g_ptr);
    *g_ptr = NULL;    
}

void graph_insert(Graph *g, short u, short v) {
    g->adjacency_matrix[u][v] = 1;
    g->adjacency_matrix[v][u] = 1;
}

void graph_remove(Graph *g, short u, short v) {
    g->adjacency_matrix[u][v] = 0;
    g->adjacency_matrix[v][u] = 0;
}

void graph_print(Graph *g) {
    for (short i = 0; i < g->n; i++)
    {
        for (short j = 0; j < g->n; j++)
        {
            printf("%d ", g->adjacency_matrix[i][j]);
        }
        printf("\n");        
    }
    printf("\n");        
}