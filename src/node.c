#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "node.h"

node * node_init(char * id, char ** adjacent_nodes, uint8_t no_adjacent_nodes)
{
	node * new_node_pointer = malloc(sizeof(node));
	if (new_node_pointer == NULL)
	{
		fprintf(stderr, "Unable to allocate memory to node %s.\n", id);
		exit(1);
	}
	strncpy(new_node_pointer->id, id, NODE_ID_LEN);
	new_node_pointer->adjacent_nodes = adjacent_nodes;
	new_node_pointer->no_adjacent_nodes = no_adjacent_nodes;
	return new_node_pointer;
}

