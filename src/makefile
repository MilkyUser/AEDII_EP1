all: get_dependencies
	make kosaraju

kosaraju: kosaraju.o scanner.o map.o graph.o string_linked_list.o
	gcc -o ../kosaraju kosaraju.o scanner.o map.o graph.o string_linked_list.o
	make clean
	
kosaraju.o:
	gcc -o kosaraju.o kosaraju.c -c
	
graph.o:
	gcc -o graph.o graph.c -c
	
string_linked_list.o:
	gcc -o string_linked_list.o string_linked_list.c -c
	
scanner.o:
	gcc -o scanner.o scanner.c -c

map.o: 
	gcc -o map.o map/src/map.c -c

get_dependencies:
	if [ ! -d './map' ] ; then git clone "https://github.com/rxi/map.git" ; fi

clean:
	rm -rf *.o *~

