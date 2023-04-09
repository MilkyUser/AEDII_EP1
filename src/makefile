all: kosaraju

kosaraju: kosaraju.o node.o scanner.o
	gcc -o ../kosaraju kosaraju.o node.o scanner.o
	make clean
	
kosaraju.o: kosaraju.c
	gcc -o kosaraju.o kosaraju.c -c

node.o: node.c
	gcc -o node.o node.c -c
	
scanner.o: scanner.c
	gcc -o scanner.o scanner.c -c

clean:
	rm -rf *.o *~

