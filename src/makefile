CC = gcc
CFLAGS = -Wall

all: get_dependencies
	make kosaraju

kosaraju: kosaraju.o scanner.o map.o graph.o string_linked_list.o strongly_connected_component.o gen.o
	gcc -o ../kosaraju kosaraju.o scanner.o map.o string_linked_list.o graph.o strongly_connected_component.o gen.o
	make clean

map.o: 
	gcc -o map.o map/src/map.c -c

get_dependencies:
	if [ ! -d './map' ] ; then git clone "https://github.com/rxi/map.git" ; fi

clean:
	rm -rf *.o *~

