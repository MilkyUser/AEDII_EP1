all: get_dependencies
	make kosaraju

kosaraju: kosaraju.o node.o scanner.o map.o
	gcc -o ../kosaraju kosaraju.o node.o scanner.o map.o
	make clean
	
kosaraju.o:
	gcc -o kosaraju.o kosaraju.c -c

node.o:
	gcc -o node.o node.c -c
	
scanner.o:
	gcc -o scanner.o scanner.c -c

map.o: 
	gcc -o map.o map/src/map.c -c


get_dependencies:
	if [ ! -d './map' ] ; then git clone "https://github.com/rxi/map.git" ; fi

clean:
	rm -rf *.o *~

