#include <stdio.h>

#include "graph.h"

typedef enum {
    INSERT = 1, REMOVE, PRINT
} OPERATION;

typedef char bool;

void executeStdinOperation(Graph *g) {
    short operation;
    scanf("%hd", &operation);

    short u, v;
    
    if (operation != PRINT)
        scanf("%hd %hd", &u, &v);    

    if (operation == INSERT) {
        graph_insert(g, u, v);        
    } else if (operation == REMOVE) {
        graph_remove(g, u, v);
    } else if (operation == PRINT) {
        graph_print(g);
    } else {
        printf("ERRO: entrada com operação inválida: %d", operation);
        return;
    }
}

int main(int argc, char const *argv[])
{
    short n, m, q;
    scanf("%hd", &n); //Número de nós
    scanf("%hd", &m); //Número de arestas

    Graph *g = graph_create(n);

    short u, v;
    for (short i = 0; i < m; i++) {
        scanf("%hd %hd", &u, &v);
        graph_insert(g, u, v);
    }


    scanf("%hd", &q);
    for (short i = 0; i < q; i++)
        executeStdinOperation(g);
    
    
    graph_delete(&g);
    return 0;
}
