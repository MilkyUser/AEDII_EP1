#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "node.h"
#include "scanner.h"

int main()
{
	char * a = calloc(1, NODE_ID_LEN);
	char * b = calloc(1, NODE_ID_LEN);
	char ac, bc;
	ac = fread_word(stdin, a);
	bc = fread_word(stdin, b);
	printf("\"%s\" - %c\n", a, ac);
	printf("\"%s\" - %c\n", b, bc);
	exit(0);
	uint16_t no_nodes;
	scanf("%hu", &no_nodes); //This assumes that the system interprets that a uint16_t is a short integer and can cause errors in non-trivial systems
	fgetc(stdin);
	//node ** graph = malloc(sizeof(node*) * no_nodes); // Ideally should be a hash list of some sort (or at least have utils functions) 
	char ** values = malloc(no_nodes);
	for (int i=0; i<no_nodes; i++)
	{
		//values[i] = read_word(stdin);
	}
	
	printf("\n");
	
	for (int i=0; i<no_nodes; i++)
	{
		printf("word [%d]: %s\n", i, values[i]);
	}	
	
	//printf("no_nodes %d at [%p]\n", no_nodes, &no_nodes);
	//for (int i=0; i<no_nodes; i++)
	//{
	//	printf("Node object at [%p] %s - %d\n", graph[i], graph[i]->id, graph[i]->no_adjacent_nodes);
	//}
	printf("FINISH\n");
	return 0;
}
