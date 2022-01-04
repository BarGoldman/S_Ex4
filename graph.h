// typedef struct Graph Graph;
// typedef struct Node Node;

struct Node{
    int num_node;
    int Tag;
    int w_sum;
    struct Node **neighbors; 
    int *weights;
    int num_of_neighbors;
} typedef Node;


typedef struct Graph {
    int N;
    Node *nodes;
} Graph;

Graph *build_graph(int);
void set_edge(int, int, int , Graph *gr);
Node *add_node(int, Graph *gr);
void delete_node(int, Graph *gr);
int shortsPath(int, int, struct Graph *gr);
void printGraph(struct Graph *gr);
void delete_gr(Graph*gr);
void TSP(int, struct Graph *gr);