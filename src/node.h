#ifndef NODE_H
#define NODE_H

#include <stdint.h>
#include <stdbool.h>

#define NODE_ID_LEN 64 

typedef struct node
{
	char id[NODE_ID_LEN];
	char ** adjacent_nodes;
	uint8_t no_adjacent_nodes;
} node;

node * node_init(char * id, char ** adjacent_nodes, uint8_t no_of_adjacent_nodes);

#endif
