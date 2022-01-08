#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"
#include "dijkstra.h"

static void add_edge_to_node(Edge *edge, Node *node);
static void remove_incoming_edges(int dest, Graph *gr);

void recieve_edges(int src_A, struct Graph *gr)
{
    int dest_A;
    int w_A;
    while (scanf("%d", &dest_A))
    {
        scanf("%d", &w_A); // get the destination node
        set_edge(src_A, dest_A, w_A, gr);
    }
    return;
}

Graph *build_graph(int N)
{
    Graph *my_graph = (Graph *)malloc(sizeof(Graph));
    my_graph->nodes_head = NULL; // initialize the head of the nodes list
    my_graph->N = N;
    return my_graph;
}

static void add_edge_to_node(Edge *edge, Node *node)
{
    edge->next = node->edges_head; // add the edge to the head of the list
    edge->prev = NULL; // the new edge is the head of the list

    // if the list is not empty
    if (node->edges_head != NULL)
    {
        node->edges_head->prev = edge; // update the previous pointer of the head of the list
    }
    node->edges_head = edge; // update the head of the list
    return;
}

void set_edge(int src, int dest, int w, Graph *gr) // add to node edge
{
    Node *my_src = NULL;
    // search the node in the graph with id = src
    for (Node *node = gr->nodes_head; node != NULL; node = node->next)
    {
        if (node->num_node == src)
        {
            my_src = node;
            break;
        }
    }

    // if the node is not found
    if (my_src == NULL)
    {
        printf("node %d is not found\n", src);
        exit(1);
    }

    // add edge to the node
    Edge *edge = (Edge *)malloc(sizeof(Edge));
    if (edge == NULL)
    {
        printf("malloc failed\n");
        exit(1);
    }

    edge->src = src;
    edge->dest = dest;
    edge->weight = w;

    // add edge to the node
    add_edge_to_node(edge, my_src);
    my_src->num_of_neighbors++;
}

static Node *search_node(int num_node, Graph *gr)
{
    Node *tmp = gr->nodes_head;
    while (tmp)
    {
        if (tmp->num_node == num_node)
        {
            break;
        }
        tmp = tmp->next;
    }
    return tmp; // return the node that we want to find or NULL if not found
}

static void remove_outgoing_edges(Node *node)
{
    // remove all the outgoing edges from the node
    Edge *edge = node->edges_head;
    while (edge)
    {
        Edge *next = edge->next;
        free(edge);
        edge = next;
        node->num_of_neighbors--;
    }
    node->edges_head = NULL; // set the head of the list to NULL
    return;
}

void connect_node_to_graph(Node *node, Graph *gr)
{
    // connect the node to the graph (doubly linked list)
    node->next = gr->nodes_head;
    node->prev = NULL;
    if (gr->nodes_head != NULL)
    {
        gr->nodes_head->prev = node;
    }
    gr->nodes_head = node;
    return;
}

// add node to the graph
Node *add_node(int src, Graph *gr)
{
    
    // search for the node with number src in the graph linked list
    Node *my_src = search_node(src, gr);

    if (my_src != NULL)
    {
        // remove all outgoing edges from the node
        remove_outgoing_edges(my_src);
    }
    else
    {
        // create a new node
        my_src = (Node *)malloc(sizeof(Node));
        my_src->num_node = src;
        my_src->edges_head = NULL;
        my_src->num_of_neighbors = 0;
        connect_node_to_graph(my_src, gr);
        gr->N++;
    }
    return my_src;
}

void delete_helper(int num, Node *node, Graph *gr);

void init_shortest_paths(const struct Graph *gr);

static void remove_node_from_graph(Node *node, Graph *gr)
{
    // remove the node from the graph
    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }
    else
    {
        gr->nodes_head = node->next;
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    free(node);
    return;
}

static void remove_edge(Edge *edge, Node *node)
{
    // if i'm the head of the list
    if (edge->prev == NULL)
    {
        node->edges_head = edge->next;
    }
    else
    {
        edge->prev->next = edge->next; // update the previous pointer of the next edge
    }
    if (edge->next != NULL)
    {
        //if i'm not at the end of the list
        edge->next->prev = edge->prev; // update the next pointer of the previous edge
    }
    free(edge); // free the edge memory
    node->num_of_neighbors--;
    return;
}

static void remove_incoming_edges(int dest, Graph *gr)
{
    // remove all the incoming edges to the node
    // iterate over all the nodes in the graph
    for (Node *node = gr->nodes_head; node != NULL; node = node->next)
    {
        // iterate over all the edges of the node
        for (Edge *edge = node->edges_head; edge != NULL; edge = edge->next)
        {
            // if the edge is incoming to the node
            if (edge->dest == dest)
            {
               remove_edge(edge, node); // remove the edge from the node
               break; // move to the next node. no need to check the rest of the edges
            }
        }
    }
    return;
}


void delete_node(int num, Graph *gr)
{
    // search for the node with number src in the graph linked list
    Node *my_src = search_node(num, gr);
    if (my_src == NULL)
    {
        printf("node %d is not found\n", num);
        exit(1);
    }

    // remove all outgoing edges from the node
    remove_outgoing_edges(my_src);

    // remove all incoming edges to this node
    remove_incoming_edges(my_src->num_node, gr);

    // remove the node from the graph
    remove_node_from_graph(my_src, gr);
    // update num of nodes
    gr->N--;
    return;
}



int shortestPath(int src,int dest, Graph *gr)
{
    //build adjacency matrix
    int **adj_matrix = (int **)malloc(gr->N * sizeof(int *));
    for (int i = 0; i < gr->N; i++)
    {
        adj_matrix[i] = (int *)malloc(gr->N * sizeof(int));
    }
    for (int i = 0; i < gr->N; i++)
    {
        for (int j = 0; j < gr->N; j++)
        {
            adj_matrix[i][j] = INT_MAX;
            if (i == j)
            {
                adj_matrix[i][j] = 0;
            }
        }
    }
    for (Node *node = gr->nodes_head; node != NULL; node = node->next)
    {
        for (Edge *edge = node->edges_head; edge != NULL; edge = edge->next)
        {
            adj_matrix[node->num_node][edge->dest] = edge->weight;
        }
    }

    struct GraphDijkstra *graph = (struct GraphDijkstra *)malloc(sizeof(*graph));
    graph->edges = adj_matrix;
    graph->vertexNum = gr->N;
    int retval = Dijkstra(graph, src, dest);
    //free memory
    for (int i = 0; i < gr->N; i++)
    {
        free(adj_matrix[i]);
    }
    free(adj_matrix);
    free(graph);

    return retval;
}


void printGraph(struct Graph *gr) // Print your graph
{
    // iterate over all the nodes in the graph
    for (Node *node = gr->nodes_head; node != NULL; node = node->next)
    {
        printf("Node %d: ", node->num_node);
        // iterate over all the edges of the node
        for (Edge *edge = node->edges_head; edge != NULL; edge = edge->next)
        {
            printf("%d(%d) ", edge->dest, edge->weight);
        }
        printf("\n");
    }
    //print long line of '-'
    printf("-----------------------------------------------------\n");

    return;   
}

void swap(int x, int y, int *a)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

void TSP(int num_of_values, struct Graph *gr)
{
    int *ptr, *c;
    int val;
    c = (int *)malloc(num_of_values * sizeof(int));
    ptr = (int *)malloc(num_of_values * sizeof(int));
    for (int i = 0; i < num_of_values; ++i)
    {
        scanf("%d", &val);
        ptr[i] = val;
        c[i] = 0;
    }
    int ans = INT_MAX;
    int temp_sum = 0;
    for (int j = 0; j < num_of_values - 1; j++)
    {
        int temp = shortestPath(ptr[j], ptr[j + 1], gr);
        if (temp == -1)
        {
            temp_sum = 0;
            break;
        }
        temp_sum = temp_sum + temp;
    }
    if (temp_sum < ans && temp_sum != 0)
    {
        ans = temp_sum;
    }
    temp_sum = 0;
    int i = 0;
    while (i < num_of_values)
    {
        if (c[i] < i)
        {
            if (i % 2 == 0)
            {
                swap(0, i, ptr);
            }
            else
            {
                swap(c[i], i, ptr);
            }
            for (int j = 0; j < num_of_values - 1; j++)
            {
                int temp = shortestPath(ptr[j], ptr[j + 1], gr);
                if (temp == -1)
                {
                    temp_sum = 0;
                    break;
                }
                temp_sum = temp_sum + temp;
            }
            if (temp_sum < ans && temp_sum != 0)
            {
                ans = temp_sum;
            }
            temp_sum = 0;
            c[i]++;
            i = 0;
        }
        else
        {
            c[i] = 0;
            i++;
        }
    }
    if (ans == INT_MAX || ans == 0)
    {
        ans = -1;
        printf("TSP shortest path: %d \n", ans);
    }
    else
    {
        printf("TSP shortest path: %d \n", ans);
    }
    free(ptr);
    free(c);
}

void delete_gr(Graph *gr)
{
    Node *node = gr->nodes_head;
    Node *next = NULL;
    while (node != NULL)
    {
        next = node->next;
        //remove all edges
        remove_outgoing_edges(node);
        remove_node_from_graph(node, gr);
        node = next;
        gr->N--;
    }
    free(gr);
}

