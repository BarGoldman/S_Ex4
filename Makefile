all: .graph

graph: main.o graph.o
	gcc -Wall -o graph main.o graph.o

main.o: main.c graph.h
	gcc -Wall -c main.c

graph.o: graph.c graph.h
	gcc -Wall -c graph.c

.PHONY: clean all

clean:
	rm -f *.o graph *.txt