#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include "node.h"
#include "scanner.h"
#include "./map/src/map.h"

int main()
{
	//char * a = calloc(1, NODE_ID_LEN);
	//char * b = calloc(1, NODE_ID_LEN);
	//char ac, bc;
	//ac = fread_word(stdin, a, NODE_ID_LEN);
	//bc = fread_word(stdin, b, NODE_ID_LEN);
	//printf("\"%s\" - 0x%x\n", a, ac);
	//printf("\"%s\" - 0x%x\n", b, bc);
	uint16_t no_nodes;
	scanf("%" SCNu16, &no_nodes);
	fgetc(stdin); // This fgetc call consumes the new line character following the first read
	char ** a = calloc(no_nodes, sizeof(char *)); 
	//char * current_string = calloc(1, NODE_ID_LEN);
	//char * current_string_b = calloc(1, NODE_ID_LEN);
	//char * current_string_c = calloc(1, NODE_ID_LEN);
	//char b = scanner_fread_word(stdin, current_string, NODE_ID_LEN);
	//char c = scanner_fread_word(stdin, current_string_b, NODE_ID_LEN);
	//char d = scanner_fread_word(stdin, current_string_c, NODE_ID_LEN);
	
	//printf("%d - \"%s\"\n", b, current_string);
	//printf("%d - \"%s\"\n", c, current_string_b);
	//printf("%d - \"%s\"\n", d, current_string_c);
	
	//exit(0);
	
	map_str_t original_graph;
	map_init(&original_graph);
	
	for (int line=0; line<no_nodes; line++)
	{
		char last_char = '\0';
		char * current_node;
		last_char = scanner_fread_word(stdin, current_node, NODE_ID_LEN);
		map_set(&original_graph, current_node, 1); \\ 1 should be replaced to a pointer to the head of a linked list
		a[line] = calloc(1, NODE_ID_LEN); // should be linked list
		while(last_char != '\n')
		{
			last_char = scanner_fread_word(stdin, a[line], NODE_ID_LEN);
		}
	}
	
	for (int line=0; line<no_nodes; line++)
	{
		printf("[%d] \"%s\"\n", line+1, a[line]);
	}
	
	exit(0);
	
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
