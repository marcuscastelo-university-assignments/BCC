#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

typedef enum {
    OK, ERROR_CYCLE
} OPERATION_RESULT;

typedef char bool;

bool **create_graph(int nodeQty) {
    bool **graph = malloc(nodeQty * sizeof(bool*));
    for (int i = 0; i < nodeQty; i++)
        graph[i] = calloc(nodeQty, sizeof(bool));
    return graph;
}

void free_graph(bool ***graph_ptr, int nodeQty){
    #define graph (*graph_ptr)
    for (int i = 0; i < nodeQty; i++) free(graph[i]);
    free(graph);
    graph = NULL;    
    #undef graph
}

OPERATION_RESULT make_graph_connection(bool **graph, int u, int v, int nodeQty) {
    if (u >= nodeQty || v >= nodeQty) return OK;
    if (u == v) return ERROR_CYCLE;
    graph[u][v] = 1;
    return OK;
}

void add_independents_to_queue(Queue *queue, int *dependencyList, int size) {
    for (int i = 0; i < size; i++)
        if (dependencyList[i] == 0)
            queue_insert(queue, i);   
}

OPERATION_RESULT check_remaining_cycles(int *dependencyList, int size) {
    for (int i = 0; i < size; i++)
        if (dependencyList[i] > 0)
            return ERROR_CYCLE;
    return OK;
}

void subtract_dependents_of(int dependencyNode, bool **graph, int *dependencyList, int nodeQty) {
    for (int i = 0; i < nodeQty; i++)
    {
        if (graph[dependencyNode][i] == 1)
            dependencyList[i]--;
    }
    
}

//Calcula o tempo mínimo para executar as tarefas do grafo e salva na referencia passada por parametro result_var_ptr
//O retorno indica a existencia de ciclos ou não
OPERATION_RESULT calculate_required_time_to_complete_all_tasks(bool **graph, int *dependencyQtyList, int nodeQty, int *result_var_ptr) {
    //Cria a fila para a execução do bfs
    Queue *to_explore_q = queue_create();
    *result_var_ptr = 0;

    //Adiciona ao bfs todos os nós que não dependem de nenhum outro
    add_independents_to_queue(to_explore_q, dependencyQtyList, nodeQty);

    //Se todos os nós forem dependentes, o grafo possui ciclos
    if (queue_is_empty(to_explore_q)) {
        queue_delete(&to_explore_q);
        return ERROR_CYCLE;
    } 

    //Enquanto houverem nós indepententes para explorar:
    do
    {  
        //Avança o contador de tempo
        (*result_var_ptr)++;
        do { //Para todos os nós a serem explorados nesse tempo:
            //Pega o valor do nó
            int node = queue_pop(to_explore_q); 

            //Marca o nó como visitado (<0)
            dependencyQtyList[node] = -1;

            //Diminui o contador de dependencia dos nós que dependem deste
            subtract_dependents_of(node, graph, dependencyQtyList, nodeQty);
        } while (!queue_is_empty(to_explore_q));

        //Adiciona os nós cujas dependencias já foram executadas
        add_independents_to_queue(to_explore_q, dependencyQtyList, nodeQty);
    } while (!queue_is_empty(to_explore_q));

    //Se houverem nós que não foram executados após o loop anterior, existe ciclo
    if (check_remaining_cycles(dependencyQtyList, nodeQty) == ERROR_CYCLE) {
        queue_delete(&to_explore_q);
        return ERROR_CYCLE;
    }

    queue_delete(&to_explore_q);
    return OK;
}

int main(int argc, char const *argv[])
{   
    //Numero de nós no grafo
    int nodeQty;
    scanf("%d", &nodeQty);

    int *dependencyQtyList = calloc(nodeQty, sizeof(int));

    bool **graph = create_graph(nodeQty);
    
    //Número de arestas
    int connectionsQty;
    scanf("%d", &connectionsQty);
    
    //Cria as arestas e faz a primeira verificação se existe loop fechado no próprio nó u == v
    bool hasCycle = 0;
    int u, v;
    for (int i = 0; i < connectionsQty; i++)
    {
        scanf("%d %d", &u, &v);
        dependencyQtyList[v]++;
        if (make_graph_connection(graph, u, v, nodeQty) == ERROR_CYCLE) {
            hasCycle = 1;
            break;
        }
    }
    
    //Se houver ciclo na primeira verificação, exibe -1
    if (hasCycle) {
        printf("-1\n");
        free_graph(&graph, nodeQty);    
        free(dependencyQtyList);
        return 0;
    }


    //Calcula o menor tempo para executar as tarefas por meio de BFS
    int requiredTimeToCompleteAllTasks = 0;
    OPERATION_RESULT res = calculate_required_time_to_complete_all_tasks(graph, dependencyQtyList, nodeQty, &requiredTimeToCompleteAllTasks);

    //Se for identificado um ciclo durante o processo, exibe -1
    if (res == ERROR_CYCLE) {
        printf("-1\n");
        free_graph(&graph, nodeQty); 
        free(dependencyQtyList);
        return 0;
    }

    printf("%d\n", requiredTimeToCompleteAllTasks);

    free_graph(&graph, nodeQty);    
    free(dependencyQtyList);
    return 0;
}
