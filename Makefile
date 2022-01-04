all: graph

graph: main2.o graph.o
	gcc -Wall -o graph main2.o graph.o 

main2.o: main2.c graph.h
	gcc -Wall -c main2.c

graph.o: graph.c graph.h
	gcc -Wall -c graph.c

.PHONY: clean all

clean:
	rm -f *.o graph main2 *.txt