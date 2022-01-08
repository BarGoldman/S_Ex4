// typedef struct Graph Graph;
// typedef struct Node Node;

struct Edge{
    int src;
    int dest;
    int weight;
    struct Edge *next;
    struct Edge *prev;
} typedef Edge;

struct Node{
    struct Node *next;
    struct Node *prev;
    int num_node;
    // list of neighbors is a linked list of outgoing edges
    Edge *edges_head;
    int num_of_neighbors;
} typedef Node;

typedef struct Graph {
    int N;
    Node *nodes_head;
} Graph;

int shortestPath(int src,int dest, Graph *gr);

int shortestPathDijkstra(int src,int dest, Graph *gr);
void recieve_edges(int src_A, struct Graph *gr);
Graph *build_graph(int);
void set_edge(int, int, int , Graph *gr);
Node *add_node(int, Graph *gr);
void delete_node(int, Graph *gr);
int shortsPath(int, int, struct Graph *gr);
void printGraph(struct Graph *gr);
void delete_gr(Graph*gr);
void TSP(int, struct Graph *gr);