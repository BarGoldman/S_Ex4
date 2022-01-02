#include <stdio.h>
#include <string.h>
#include "graph.h"

int main(int argc, char const *argv[]) {
    struct Graph *gr;
    char *ch;
    int input_num;
    scanf("%c", ch);
    while (1) {
        if (*ch == EOF) {
            break;
        }
        if (*ch == 'A') {
            scanf("%d", &input_num);
            gr = build_graph(input_num);
			int node_A;
			int dest_A;
			int w_A;
			char n_letter;
			while (scanf("%s", &n_letter))
			{
                if (n_letter == 'A' || n_letter == 'B' || n_letter == 'D') {
                    ch = n_letter;
                    break;
                }
				scanf("%d",node_A);
				while (scanf("%d", dest_A))
				{
					scanf("%d", w_A);
					set_edge(node_A,dest_A,w_A,gr);
					
				}
			}
			
        }
        if (*ch == 'B') {
            int num_B;
            int dest;
            int weight;
            scanf("%d", &num_B);
            Node *my_src = add_node(num_B,gr);
            while (scanf("%d", &dest)) {
                // if (dest == 'A' || dest == 'B' || dest == 'D') {
                //     ch = dest;
                //     break;
                // }
                scanf("%d", &weight);
                set_edge(my_src->num_node, dest, weight, gr);
            }
			scanf("%c", ch);
        } else if (*ch == 'D') {
            int dest;
            scanf("%d", &dest);
            delete_node(dest,gr);
            scanf("%c", ch);
        }else if (*ch == 'S') {
            int src;
            int dest;
            scanf("%d", &src);
            scanf("%d", &dest);
            shortsPath(src,dest,gr);
            scanf("%c", ch);
        }else if (*ch == 'T') {
            int k;
            int val;
            scanf("%d", &k);
            int values[k];
            for (int i = 0; i < k; ++i) {
                scanf("%d", &val);
                values[i] = val;
            }
            TSP(values,k,gr);
            scanf("%c", ch);
        }


    }
    delete_gr(gr);
    return 0;
}
