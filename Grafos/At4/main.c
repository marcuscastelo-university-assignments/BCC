#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "graph.h"
#include "list.h"
#include "priority_queue.h"
#include "debug.h"

typedef struct {
    int minCost, minTime;
    char *pathStr, *baseStr;
} DijkstraResult;

//Returns the cost of minimal time trip
DijkstraResult dijkstra(Graph *g, int startID, int endID, int nodeQty) {
    PriorityQueue *pq = pq_create(nodeQty);
    pq_relax(pq, startID, 0);

    int *finalLocalCosts = calloc(nodeQty, sizeof(int));
    int *finalLocalTimes = calloc(nodeQty, sizeof(int));
    int *antecessorIDs = malloc(nodeQty * sizeof(int));

    while (!pq_is_empty(pq)) {
        PQPopPair pair = pq_pop(pq);
        int cityID = pair.cityID;
        int dist = pair.dist;

        if (cityID < 0) break;

        List *edges = graph_get_edges(g, cityID);
        int size = list_get_size(edges);

        for (int i = 0; i < size; i++)
        {
            Edge *edge = list_get(edges, i);
            int destID = edge->to;
            int destTime = edge->time;

            //Dist is measured by time
            int newDist = dist + destTime;

            if (pq_relax(pq, destID, newDist) == 1) {
                antecessorIDs[destID] = cityID;
                finalLocalCosts[destID] = edge->cost;
                finalLocalTimes[destID] = edge->time;
            }
        }
        
    }

    int costSum = 0, timeSum = 0;

    //Allocate a worst scenario string size
    int n = nodeQty;

    int charsCount = 0;

    while (n > 10) {
        int termQty = n - (int) pow(10, (int) log10(n)) + 1;
        int digitCount = (log10(n-1) + 1) * (n / 10 * 10);
        n /= 10;

        charsCount = termQty * (digitCount + 1);
    }
    // \n e \0
    charsCount += 2;

    char *pathStrBase = calloc(charsCount, sizeof(char));

    char *pathStrEnd = pathStrBase;

    int *citiesInPath = malloc(nodeQty * sizeof(int));
    int revI = nodeQty-1;

    int currID = endID;
    while (1) {
        costSum += finalLocalCosts[currID];
        timeSum += finalLocalTimes[currID];

        citiesInPath[revI--] = currID;

        if (currID == startID) break;
        currID = antecessorIDs[currID];
    }

    for (int i = revI+1; i < nodeQty; i++)
        pathStrEnd += sprintf(pathStrEnd, "%d ", citiesInPath[i]);
    sprintf(pathStrEnd, "\n");
    
    free(antecessorIDs);
    free(finalLocalCosts);
    free(finalLocalTimes);
    pq_delete(&pq);

    return (DijkstraResult){costSum, timeSum, pathStrBase};
}

Graph *feed_graph(int nodeQty, int edgeQty) {
    Graph *g = graph_create(nodeQty);

    int from, to, time, cost;
    for (int i = 0; i < edgeQty; i++) {
        scanf("%d %d %d %d", &from, &to, &time, &cost);
        graph_insert_edge(g, from, create_edge(to, time, cost));
    }
    return g;    
}

int main(int argc, char const *argv[])
{   
    //Inputs iniciais
    int nodeQty, edgeQty;
    scanf("%d %d", &nodeQty, &edgeQty);

    //Alimenta o grafo
    Graph *graph = feed_graph(nodeQty, edgeQty);
    if (graph == NULL) {
        DP("CRITICAL FAILURE main.c@main() -> ask_for_edges()\n");
        return 0;
    }

    int startCity, endCity;
    scanf("%d %d", &startCity, &endCity);

    DijkstraResult res = dijkstra(graph, startCity, endCity, nodeQty);
    printf("%s", res.pathStr);
    printf("%d %d\n", res.minTime, res.minCost);

    //Free res.pathStr (it's a pointer to the middle of baseStr)
    free(res.baseStr);
    graph_delete(&graph);

    return 0;
}
