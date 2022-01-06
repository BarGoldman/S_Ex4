#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "graph.h"

// struct Node {
//     int num_node;
//     int Tag;
//     int w_sum;
//     struct Node **neighbors;
//     int *weights;
//     int num_of_neighbors;
// } typedef Node;

// struct Graph {
//     int N;
//     Node *nodes;
// } typedef Graph;

Graph *build_graph(int N)
{
    Graph *my_graph = (Graph *)malloc(sizeof(Graph));
    my_graph->nodes = (Node *)malloc(N * sizeof(Node));
    my_graph->N = N;
    for (int i = 0; i < my_graph->N; ++i)
    {
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
    printf("i am here:\n");
    Node *my_src = NULL;
    Node *my_dest = NULL;
    for (int i = 0; i < gr->N; ++i)
    {
        if (gr->nodes[i].num_node == src)
        {
            my_src = &gr->nodes[i];
        }
        if (gr->nodes[i].num_node == dest)
        {
            my_dest = &gr->nodes[i];
        }
    }
    my_src->num_of_neighbors++;
    if (!my_src->neighbors)
    {
        my_src->neighbors = (Node **)malloc(my_src->num_of_neighbors * sizeof(Node *));
    }
    else
    {
        my_src->neighbors = (Node **)realloc(my_src->neighbors, my_src->num_of_neighbors * sizeof(Node *));
    }
    my_src->neighbors[my_src->num_of_neighbors - 1] = my_dest;
    if (!my_src->neighbors)
    {
        my_src->weights = (int *)malloc(my_src->num_of_neighbors * sizeof(int));
    }
    else
    {
        my_src->weights = (int *)realloc(my_src->weights, my_src->num_of_neighbors * sizeof(int));
    }
    my_src->weights[my_src->num_of_neighbors - 1] = w;
}

Node *add_node(int src, Graph *gr)
{
    printf("1\n");
    Node *my_src = NULL;
    for (int i = 0; i < gr->N; ++i)
    {
        if (gr->nodes[i].num_node == src)
        {
            my_src = &gr->nodes[i];
        }
    }
    if (my_src != NULL)
    {
        free(my_src->neighbors);
        my_src->neighbors = NULL;
        my_src->num_of_neighbors = 0;
        free(my_src->weights);
        my_src->weights = NULL;
    }
    else
    {
        gr->N++;
        gr->nodes = (Node *)realloc(gr->nodes, gr->N * sizeof(Node));
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

void delete_node(int num, Graph *gr)
{
    Node *my_src = NULL;
    for (int i = 0; i < gr->N; ++i)
    {
        if (gr->nodes[i].num_node == num)
        {
            my_src = &gr->nodes[i];
        }
    }
    free(my_src->neighbors);
    my_src->neighbors = NULL;
    free(my_src->weights);
    my_src->weights = NULL;
    my_src->num_of_neighbors = 0;
    for (int i = 0; i < gr->N; ++i)
    {
        delete_helper(num, &gr->nodes[i], gr);
    }
    Node *new_nodes = (Node *)malloc((gr->N-1) * sizeof(Node));
    int counter = 0 ;
    for(int i = 0 ; i< gr->N ; ++i){
        if(gr->nodes[i].num_node != num){
            new_nodes[counter] = gr->nodes[i];
            counter++;
        }
    }
    free(gr->nodes);
    gr->nodes = new_nodes;
    gr->N--;
}

void delete_helper(int num, Node *node, Graph *gr)
{
    printf(" 1 .i am here\n");
    Node **new_neighbors = (Node **)realloc(node->neighbors, gr->N - 1);
    int *new_weights = (int *)realloc(node->weights, gr->N - 1);
    int location_of_neighbor = -1;
    for (int j = 0; j < node->num_of_neighbors; ++j)
    {
        if (node->neighbors[j]->num_node == num)
        {
            location_of_neighbor = j;
            break;
        }
    }
    if (location_of_neighbor == -1)
    {
        return;
    }
    if (location_of_neighbor == 0)
    {
        printf(" 1. node: %d, num_ of neigh: %d \n" ,node->num_node, node->num_of_neighbors);
        memcpy(new_neighbors, node->neighbors[1],
               (node->num_of_neighbors - 1 ) * sizeof(Node *));
        memcpy(new_weights, &node->weights[1],
               (node->num_of_neighbors - 1 ) * sizeof(int));
    }
    else if (location_of_neighbor == node->num_of_neighbors - 1) // 5
    {
        printf("2. node: %d, num_ of neigh: %d \n" ,node->num_node, node->num_of_neighbors);
        memcpy(new_neighbors, node->neighbors[0],
               (node->num_of_neighbors - 1) * sizeof(Node *));
        memcpy(new_weights, &node->weights[0],
               (node->num_of_neighbors - 1) * sizeof(int));
    }
    else
    {
        printf("node: %d, num_ of neigh: %d \n" ,node->num_node, node->num_of_neighbors);
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
    printf("4 . i am here\n");
//    free(node->neighbors);
    node->neighbors = new_neighbors;
    node->weights = new_weights;
    node->num_of_neighbors--;
//    free(node->neighbors);
}

int min_Val(struct Graph *gr)
{
    int sum = INT_MAX;
    int j = 0;
    for (int i = 0; i < gr->N; i++)
    {
        if (gr->nodes[i].w_sum < sum)
        {
            if (gr->nodes[i].Tag == 0)
            {
                sum = gr->nodes[i].w_sum;
                j = i;
            }
        }
    }
    return j;
}

int MIN(int x, int y)
{
    if (x < y)
    {
        return x;
    }
    else
    {
        return y;
    }
}

void reset_tag(const struct Graph *gr)
{
    for (int i = 0; i < gr->N; ++i)
    {
        gr->nodes[i].Tag = 0;
    }
}

void reset_num_w(const struct Graph *gr)
{
    for (int i = 0; i < gr->N; ++i)
    {
        gr->nodes[i].w_sum = 0;
    }
}

int shortsPath(int src, int dest, struct Graph *gr) // you get the shorts path
{
    reset_num_w(gr);
    int ans = -1;
    Node *ptr = NULL;
    for (int i = 0; i < gr->N; i++)
    {
        if (gr->nodes[i].num_node == src)
        {
            ptr = &gr->nodes[i];
            continue;
        }
        gr->nodes[i].w_sum = INT_MAX;
    }
    if (ptr->num_of_neighbors == 0)
    {
        return -1;
    }
    // printf("Node %d: %d\n", gr->nodes[0].num_node, gr->nodes[0].w_sum);
    // printf("Node %d: %d\n", gr->nodes[1].num_node, gr->nodes[1].w_sum);
    // printf("Node %d: %d\n", gr->nodes[2].num_node, gr->nodes[2].w_sum);
    // printf("Node %d: %d\n", gr->nodes[3].num_node, gr->nodes[3].w_sum);
    // printf("Node %d: %d\n", gr->nodes[4].num_node, gr->nodes[4].w_sum);
    int l = 0;
    while (l < gr->N)
    {
        if (ptr->Tag == 1)
        {
            l++;
            continue;
        }
        ptr->Tag = 1;
        for (int j = 0; j < ptr->num_of_neighbors; ++j)
        {
            Node *temp = ptr->neighbors[j];
            // printf("ptr->neighbors[j] NOde : %d\n", ptr->neighbors[j]->num_node);
            // printf("Node temp is : %d temp->w_sun: %d\n", temp->num_node, temp->w_sum);
            // printf("the w: %d to neighbors %d is: (ptr->wights[j]) %d\n", ptr->num_node, ptr->neighbors[j]->num_node, ptr->weights[j]);
            // printf("gr->nodes[temp->num_node].w_sum: %d ptr->weights[j] %d  ptr->w_sum %d\n", gr->nodes[temp->num_node].w_sum, ptr->weights[j], ptr->w_sum);
            // printf(" MIN %d\n", MIN(gr->nodes[temp->num_node].w_sum, ptr->weights[j] + ptr->w_sum));
            gr->nodes[temp->num_node].w_sum = MIN(gr->nodes[temp->num_node].w_sum, ptr->weights[j] + ptr->w_sum);
            // printf("Node %d w_sum now: %d\n", temp->num_node, temp->w_sum);
            // printf("Node %d: %d\n", gr->nodes[0].num_node, gr->nodes[0].w_sum);
            // printf("Node %d: %d\n", gr->nodes[1].num_node, gr->nodes[1].w_sum);
            // printf("Node %d: %d\n", gr->nodes[2].num_node, gr->nodes[2].w_sum);
            // printf("Node %d: %d\n", gr->nodes[3].num_node, gr->nodes[3].w_sum);
            // printf("Node %d: %d\n", gr->nodes[4].num_node, gr->nodes[4].w_sum);
        }
        int num = min_Val(gr);
        ptr = &gr->nodes[num];
        l++;
    }
    reset_tag(gr);
    ptr = &gr->nodes[dest];
    if (ptr->w_sum == INT_MAX)
    {
        return ans;
    }
    else
    {
        return ptr->w_sum;
    }
}

void printGraph(struct Graph *gr) // Print your graph
{
    Node *ptr = NULL;
    printf("Your graph have %d Node\n", gr->N);
    printf("Look Your graph: \n");
    for (int i = 0; i < gr->N; ++i)
    {
        ptr = &gr->nodes[i];
        printf("Node: %d\n", ptr->num_node);
        for (int j = 0; j < ptr->num_of_neighbors; j++)
        {
            printf("(%d -> %d), w:(%d)", ptr->num_node, ptr->neighbors[j]->num_node, ptr->weights[j]);
        }
        printf("NULL\n");
    }
}

void swap(int x, int y, int *a)
{
    int temp = a[x];
    a[x] = a[y];
    a[y] = temp;
}

void TSP(int num_of_values, struct Graph *gr)
{
    reset_num_w(gr);
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
        int temp = shortsPath(ptr[j], ptr[j + 1], gr);
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
                int temp = shortsPath(ptr[j], ptr[j + 1], gr);
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
    if (ans == MAX_INPUT || ans == 0)
    {
        ans = -1;
        printf("TSP shortest path: %d\n", ans);
    }
    else
    {
        printf("TSP shortest path: %d\n", ans);
    }
    reset_num_w(gr);
    free(ptr);
    free(c);
}

void delete_gr(Graph *gr)
{
    for (int i = 0; i < gr->N; ++i)
    {
        free(gr->nodes[i].weights);
        free(gr->nodes[i].neighbors);
    }
    free(gr->nodes);
    free(gr);
}
