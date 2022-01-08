#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"


// Utility function to find minimum distance vertex in mdist
int minDistance(int mdist[], int vset[], int V)
{
    int min_val = INT_MAX;
    static int min_ind = -1;
    for (int i = 0; i < V; i++){
        if (vset[i] == 0 && mdist[i] < min_val)
        {
            min_val = mdist[i];
            min_ind = i;
        }
    }
    return min_ind;
}

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
    for (int j = 0; j < V - 1; j++)
    {
        int u = minDistance(mdist, vset, V);
        vset[u] = 1;

        for (int v = 0; v < V; v++)
        {
            if (!vset[v] && graph->edges[u][v] != INT_MAX && mdist[u] + graph->edges[u][v] < mdist[v])
                mdist[v] = mdist[u] + graph->edges[u][v];
        }
    }   
    //ternary operator
    return mdist[dest] != INT_MAX ? mdist[dest] : -1;
}