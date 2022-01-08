all: graph

graph: main.o graph.o dijkstra.o
	gcc -Wall -g -o graph dijkstra.o main.o graph.o 

main.o: main.c graph.h
	gcc -Wall -g -c main.c

graph.o: graph.c graph.h
	gcc -Wall -g -c graph.c

dijkstra.o: dijkstra.c dijkstra.h
	gcc -Wall -g -c dijkstra.c

.PHONY: clean all

clean:
	rm -f *.o graph