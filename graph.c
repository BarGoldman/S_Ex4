#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
// struct Node {
//     int num_node;
//     int Tag;
//     int w_sum;
//     struct Node **neighbors; // for the node in graph
//     int *weights;
//     int num_of_neighbors// for the list of node in i node
// } typedef Node;


// struct Graph {
//     int N;
//     Node *nodes;
// } typedef Graph;

Graph *build_graph(int N) {
    Graph *my_graph = (Graph *) malloc(sizeof(Graph));
    my_graph->nodes = (Node *) malloc(N * sizeof(Node));
    my_graph->N = N;
    for (int i = 0; i < my_graph->N; ++i) {
        my_graph->nodes[i].num_node = i;
        my_graph->nodes[i].neighbors = NULL;
        my_graph->nodes[i].weights = NULL;
        my_graph->nodes[i].Tag = 0;
        my_graph->nodes[i].w_sum = 0;
        my_graph->nodes[i].num_of_neighbors = 0;
    }
    return my_graph;
}

void set_edge(int src, int dest, int w, Graph *gr) // add to node edge
{
    Node *my_src = NULL;
    Node *my_dest = NULL;
    for (int i = 0; i < gr->N; ++i) {
        if (gr->nodes[i].num_node == src) {
            my_src = &gr->nodes[i];
        }
        if (gr->nodes[i].num_node == dest) {
            my_dest = &gr->nodes[i];
        }
    }
    my_src->num_of_neighbors++;
    if (!my_src->neighbors) {
        my_src->neighbors = (Node **) malloc(my_src->num_of_neighbors * sizeof(Node *));
    } else {
        my_src->neighbors = (Node **) realloc(my_src->neighbors, my_src->num_of_neighbors * sizeof(Node *));
    }
    my_src->neighbors[my_src->num_of_neighbors - 1] = my_dest;
    if (!my_src->neighbors) {
        my_src->weights = (int *) malloc(my_src->num_of_neighbors * sizeof(int));
    } else {
        my_src->weights = (int *) realloc(my_src->weights, my_src->num_of_neighbors * sizeof(int));
    }
    my_src->weights[my_src->num_of_neighbors - 1] = w;
}

Node *add_node(int src, Graph *gr) {
    Node *my_src = NULL;
    for (int i = 0; i < gr->N; ++i) {
        if (gr->nodes[i].num_node == src) {
            my_src = &gr->nodes[i];
        }
    }
    if (my_src != NULL) {
        for (int i = 0; i < my_src->num_of_neighbors; ++i) {
            free(my_src->neighbors[i]);
        }
    } else {
        gr->N++;
        gr->nodes = (Node *) realloc(gr->nodes, gr->N * sizeof(Node));
        gr->nodes[gr->N - 1].num_node = src;
        gr->nodes[gr->N - 1].num_of_neighbors = 0;
        gr->nodes[gr->N - 1].weights = NULL;
        gr->nodes[gr->N - 1].Tag = 0;
        gr->nodes[gr->N - 1].neighbors = NULL;
        my_src = &gr->nodes[gr->N - 1];
    }
    return my_src;
}

void delete_helper(int num, Node *node, Graph *gr);

void reset_tag(const struct Graph *gr);

void delete_node(int num, Graph *gr) {
    Node *my_src = NULL;
    for (int i = 0; i < gr->N; ++i) {
        if (gr->nodes[i].num_node == num) {
            my_src = &gr->nodes[i];
        }
    }
    for (int i = 0; i < my_src->num_of_neighbors; ++i) {
        free(my_src->neighbors[i]);
    }
    for (int i = 0; i < my_src->num_of_neighbors; ++i) {
        free(my_src->weights);
    }
    for (int i = 0; i < gr->N; ++i) {
        delete_helper(num, &gr->nodes[i], gr);
    }
    free(my_src);
}

void delete_helper(int num, Node *node, Graph *gr) {
    Node **new_neighbors = (Node **) realloc(node->neighbors, gr->N - 1);
    int *new_weights = (int *) realloc(node->weights, gr->N - 1);
    int location_of_neighbor = -1;
    for (int j = 0; j < node->num_of_neighbors; ++j) {
        if (node->neighbors[j]->num_node == num) {
            location_of_neighbor = j;
            break;
        }
    }
    if (location_of_neighbor == -1) {
        return;
    }
    if (location_of_neighbor == 0) {
        memcpy(new_neighbors, node->neighbors[1],
               (node->num_of_neighbors - 1) * sizeof(Node *));
        memcpy(new_weights, &node->weights[1],
               (node->num_of_neighbors - 1) * sizeof(int));
    } else if (location_of_neighbor == node->num_of_neighbors - 1) {
        memcpy(new_neighbors, node->neighbors[0],
               (node->num_of_neighbors - 1) * sizeof(Node *));
        memcpy(new_weights, &node->weights[0],
               (node->num_of_neighbors - 1) * sizeof(int));
    } else {
        memcpy(new_neighbors, node->neighbors[0],
               (location_of_neighbor) * sizeof(Node *));
        memcpy(new_neighbors[location_of_neighbor],
               node->neighbors[location_of_neighbor + 1],
               (node->num_of_neighbors - location_of_neighbor - 1) * sizeof(Node *));
        memcpy(new_weights, &node->weights[0],
               (location_of_neighbor) * sizeof(Node *));
        memcpy(&new_weights[location_of_neighbor],
               &node->weights[location_of_neighbor + 1],
               (node->num_of_neighbors - location_of_neighbor - 1) * sizeof(Node *));
    }
    for (int j = 0; j < node->num_of_neighbors; ++j) {
        free(node->neighbors[j]);
    }
    node->neighbors = new_neighbors;
    node->weights = new_weights;
    node->num_of_neighbors--;
}

int min_Val(struct Graph *gr) {
    int sum = INT_MAX;
    int j = 0;
    Node *ptr = NULL;
    for (int i = 0; i < gr->N; i++) {
        if (gr->nodes[i].w_sum < sum) {
            if (gr->nodes[i].Tag == 0) {
                sum = gr->nodes[i].w_sum;
                j = i;
            }
        }
    }
    return j;
}

int shortsPath(int src, int dest, struct Graph *gr) // you get the shorts path
{
    int ans = -1;
    Node *ptr = NULL;
    for (int i = 0; i < gr->N; i++) {
        if (gr->nodes[i].num_node == src) {
            ptr = &gr->nodes[i];
            continue;
        }
        gr->nodes[i].w_sum = INT_MAX;
    }
    int l = 0;
    while (l < gr->N) {
        if (ptr->Tag == 1) {
            l++;
            continue;
        }
        ptr->Tag = 1;
        for (int j = 0; j < ptr->num_of_neighbors; ++j) {
            Node *temp = ptr->neighbors[j];
            temp->w_sum = MIN(temp->w_sum, temp->weights[j] + ptr->w_sum);
        }
        int num = min_Val(gr);
        ptr = &gr->nodes[num];
        l++;
    }
    reset_tag(gr);
    ptr = &gr->nodes[dest];
    if (ptr->w_sum == INT_MAX) {
        return ans;
    } else {
        return ptr->w_sum;
    }
}

void reset_tag(const struct Graph *gr) {
    for (int i = 0; i < gr->N; ++i) {
        gr->nodes[i].Tag = 0;
    }
}

void printGraph(struct Graph *gr) // Print your graph
{
    Node *ptr = NULL;
    printf("Your graph have %d Node\n", gr->N);
    printf("Look Your graph: \n");
    for (int i = 0; i < gr->N; ++i) {
        ptr = &gr->nodes[i];
        printf("Node: %d\n", ptr->num_node);
        for (int j = 0; j < ptr->num_of_neighbors; j++) {
            printf("(%d -> %d), w:(%d)", ptr->num_node, ptr->neighbors[j]->num_node, ptr->weights[j]);
        }
        printf("NULL\n");
    }
}

// 2 0 5 -> 9
// 2 5 0 -> 8
// 5 2 0 -> -1
// 5 0 2
// 0 2 5
// 0 5 2
// int *get_sum(int sum, Graph *gr) {
//     if () {

//     }
//     for (int i = 0; i < gr->N; ++i) {
//         if (gr->nodes[i].Tag != 0) {

//         }
//     }
// }

void delete_gr(Graph*gr){
    for (int i = 0; i < gr->N; ++i) {
        free(gr->nodes[i].weights);
        free(gr->nodes[i].neighbors);
        free(gr->nodes+i);
    }
    free(gr->nodes);
    free(gr);
};

int TSP(int *values, int num_of_values, struct Graph *gr) {

    for (int i = 0; i < gr->N; ++i) {

    }
    int ans = -1;
    int i = 0;
}

void delete_gr(Graph*gr){
    for (int i = 0; i < gr->N; ++i) {
        free(gr->nodes[i].weights);
        free(gr->nodes[i].neighbors);
    }
    free(gr->nodes);
    free(gr);
}

