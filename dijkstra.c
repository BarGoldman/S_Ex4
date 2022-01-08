#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dijkstra.h"


// Utility function to find minimum distance vertex in mdist
int minDistance(int mdist[], int vset[], int V)
{
    int minVal = INT_MAX;
    static int minInd = -1;
    for (int i = 0; i < V; i++)
        if (vset[i] == 0 && mdist[i] < minVal)
        {
            minVal = mdist[i];
            minInd = i;
        }
    //print minInd
    // printf("flag is %d, minIndx=%d \n",flag, minInd);
    return minInd;
}

// Utility function to print distances
void print(int dist[], int V)
{
    printf("\nVertex  Distance\n");
    for (int i = 0; i < V; i++)
    {
        if (dist[i] != INT_MAX)
            printf("%d\t%d\n", i, dist[i]);
        else
            printf("%d\tINF", i);
    }
}

// The main function that finds the shortest path from given source
// to all other vertices using Dijkstra's Algorithm.It doesn't work on negative
// weights
int Dijkstra(struct GraphDijkstra *graph, int src,int dest)
{
    int V = graph->vertexNum;
    int mdist[V];  // Stores updated distances to vertex
    int vset[V];   // vset[i] is true if the vertex i included
                   // in the shortest path tree

    // Initialise mdist and vset. Set distance of source as zero
    for (int i = 0; i < V; i++) 
    {
        mdist[i] = INT_MAX;
        vset[i] = 0;
    }

    mdist[src] = 0;

    // iterate to find shortest path
    for (int count = 0; count < V - 1; count++)
    {
        int u = minDistance(mdist, vset, V);
        vset[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!vset[v] && graph->edges[u][v] != INT_MAX &&
                mdist[u] + graph->edges[u][v] < mdist[v])
                mdist[v] = mdist[u] + graph->edges[u][v];
        }
    }

    // print(mdist, V);
    
    //ternary operator
    return mdist[dest] != INT_MAX ? mdist[dest] : -1;
}