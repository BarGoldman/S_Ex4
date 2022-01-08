// Structure for storing a graph
struct GraphDijkstra
{
    int vertexNum;
    int **edges;
};

int Dijkstra(struct GraphDijkstra *graph, int src,int dest);


