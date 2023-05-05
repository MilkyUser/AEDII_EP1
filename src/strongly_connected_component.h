#ifndef SCC_H
#define SCC_H
#include "string_linked_list.h"
#include <stdbool.h>
#include <stdio.h>

typedef struct strongly_connected_component
{
	string_linked_list * nodes;
	struct strongly_connected_component * next;
} strongly_connected_component;

typedef struct sccs_list
{
	struct strongly_connected_component * head;
	uint16_t count;
} sccs_list;

sccs_list * sccs_list_init();
strongly_connected_component * scc_init(string_linked_list * node_list);
void sccs_list_push(sccs_list * list, strongly_connected_component * new_scc);
bool scc_contains(strongly_connected_component * scc, char * node);
bool scc_equals(strongly_connected_component * scc1, strongly_connected_component * scc2); // compares two scc's, returns true if both have the same elements
void fprint_sccs(FILE * f, sccs_list * list, char * sep);

#endif
