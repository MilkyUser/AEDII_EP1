#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "string_linked_list.h"
#include "strongly_connected_component.h"

sccs_list * sccs_list_init()
{
	sccs_list * list_pointer = malloc(sizeof(sccs_list));
	if (list_pointer == NULL)
	{
		return NULL;
	}
	list_pointer->count = 0;
	list_pointer->head = NULL;
	return list_pointer;
}

void sccs_list_push(sccs_list * list, strongly_connected_component * new_scc)
{
	if (list->head == NULL)
	{
		list->head = new_scc;
		new_scc->next = NULL;
	}
	else
	{
		strongly_connected_component * previous = list->head; 
		list->head = new_scc;
		new_scc->next = previous;
	}
	list->count++;
}

strongly_connected_component * scc_init(string_linked_list * node_list)
{
	strongly_connected_component * scc = malloc(sizeof(strongly_connected_component));
	if (scc == NULL)
	{
		return NULL;
	}
	scc->nodes = node_list;
	scc->next = NULL;
	return scc;
}

bool scc_contains(strongly_connected_component * scc, char * node)
{
	if (scc->nodes->head->next == NULL)
	{
		return false;
	}
	string_linked_list_node * component = scc->nodes->head->next;
	for (int i=1; i<scc->nodes->count; i++)
	{
		if (strcmp(node, component->value) == 0)
		{
			return true;
		}
		component = component->next; 
	}
	return false;
}

bool scc_equals(strongly_connected_component * scc1, strongly_connected_component * scc2)
{
	if (scc1->nodes->count != scc2->nodes->count)
	{
		return false;
	}
	// TODO: for each node in scc1, compare to each node in scc2, if no match is found return false, finally return true
}

void fprint_sccs(FILE * f, sccs_list * list, char * sep)
{
	strongly_connected_component * scc = list->head;
	for(int i=0; i<list->count; i++)
	{
		if (scc->nodes->count == 0)
		{
			fprintf(f, "ERRO! Componente conectada vazia na lista de componentes fortemente conectadas\n");
		}
		fprintf_string_linked_list(f, scc->nodes, " | ");
		scc = scc->next;
	}
}

