#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "graph.h"

int main()
{
    struct Graph *gr = NULL;
    char ch;
    int input_num;
    //	printf("enter First letter A/B/D/S: \n");
    while (scanf("%c", &ch))
    {
        if (ch == 'W')
        {
            break;
        }
        while (ch == 'A')
        {
            if (gr != NULL)
            {
                delete_gr(gr);
            }
            //			printf("enter how mach node: \n");
            scanf("%d", &input_num);
            gr = build_graph(input_num);
            //			char l_n;
            int src_A;
            int dest_A;
            int w_A;
            //			printf("one: %c\n",ch);
            //			printf("enter n: \n");
            //			scanf("%c", &ch);
            //			scanf("%c", &ch);
            //			scanf("%d",&dest_A);
            //			printf("3: %c\n",ch);
            while (scanf("%c", &ch))
            {
                if (ch == 'n')
                {
                    //				printf("enter node: \n");
                    scanf("%d", &src_A);
                    // if(ch == EOF){
                    // 	break;
                    // }
                    //				printf("enter dest: \n");
                    while (scanf("%d", &dest_A))
                    {
                        //					printf("enter wight: \n");
                        scanf("%d", &w_A);
                        set_edge(src_A, dest_A, w_A, gr);
                    }
                }
                if (ch == 'A' || ch == 'B' || ch == 'D' || ch == 'S' || ch == 'T' || ch == 'W')
                {
                    break;
                }
            }
            //			printf("two: %c\n",ch);
            printf("after A: \n");
            printGraph(gr);
        }
        if (ch == 'B')
        {
            int num_B;
            int dest;
            int weight;
            //			printf("enter num node add: \n");
            scanf("%d", &num_B);
            Node *my_src = add_node(num_B, gr);
            //			printf("enter dest node add: \n");
            while (scanf("%d", &dest))
            {
                //				printf("enter weight node add: \n");
                scanf("%d", &weight);
                set_edge(my_src->num_node, dest, weight, gr);
                //				printf("enter dest node add: OR CHANGE LETTER:\n");
            }
            printGraph(gr);
        }
        if (ch == 'D')
        {
            int dest;
            //			printf("enter node delete: \n");
            scanf("%d", &dest);
            delete_node(dest, gr);
            printGraph(gr);
            //			printf("enter next letter : \n");
        }
        if (ch == 'S')
        {
            int src;
            int dest;
            scanf("%d", &src);
            //			printf("enter node dest: \n");
            scanf("%d", &dest);
            printf("Dijsktra shortest path: %d\n", shortsPath(src, dest, gr));
            printGraph(gr);
            //			printf("enter next letter : \n");
        }
        if (ch == 'W')
        {
            printf("i here:\n");
            printGraph(gr);
            break;
        }
        if (ch == 'T')
        {
            int k;
            scanf("%d", &k);
            TSP(k, gr);
        }
    }
    delete_gr(gr);
    return 0;
}