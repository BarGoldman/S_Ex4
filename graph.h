struct Node {
    int num_node;
    int Tag;
    int w_sum;
    struct Node **neighbors; // for the node in graph
    int *weights;
    int num_of_neighbors// for the list of node in i node
} typedef Node;


struct Graph {
    int N;
    Node *nodes;
} typedef Graph;

Graph *build_graph(int);
void set_edge(int, int, int , Graph *gr);
Node *add_node(int, Graph *gr);
void delete_node(int, Graph *gr);
int shortsPath(int, int, struct Graph *gr);
void printGraph(struct Graph *gr);
void delete_gr(Graph*gr);
int TSP(int *v, int, struct Graph *gr);