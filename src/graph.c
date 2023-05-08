#include "string_linked_list.h"
#include "./map/src/map.h"
#include "graph.h"
#include "strongly_connected_component.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

map_linked_list_t * transpose_graph(map_linked_list_t * original_graph)
{
	map_linked_list_t * transposed_graph_pointer = malloc(sizeof(map_linked_list_t));
	map_init(transposed_graph_pointer);
	const char *key;
	map_iter_t iter = map_iter(&original_graph);
	while ((key = map_next(original_graph, &iter))) 
	{
		string_linked_list * vicinity = string_linked_list_init();
		map_set(transposed_graph_pointer, key, vicinity);
	}
	
	iter = map_iter(&original_graph);
	while ((key = map_next(original_graph, &iter))) 
	{
		string_linked_list * vicinity = (*map_get(original_graph, key));
		if (!(0 >= vicinity->count))
		{
			string_linked_list_node * neighbor = vicinity->head->next;
			for (int i=0; i<vicinity->count; i++)
			{	
				string_linked_list_append(*map_get(transposed_graph_pointer, neighbor->value), (char*) key); 
				neighbor = neighbor->next;
			}
		}
	}
	
	return transposed_graph_pointer;
}

void fprint_graph(FILE * f, map_linked_list_t * graph)
{
	const char *key;
	map_iter_t iter = map_iter(graph);

	while ((key = map_next(graph, &iter))) 
	{
		fprintf(f, "[%s] -> %d neighbors\n", key, (*map_get(graph, key))->count);
		if (!(0 >= (*map_get(graph, key))->count))
		{
			string_linked_list_node * neighbor = (*map_get(graph, key))->head->next;
			fprintf(f, "\t");
			for (int i=0; i<(*map_get(graph, key))->count-1; i++)
			{
				fprintf(f, "[%s], ", neighbor->value);
				neighbor = neighbor->next;
			}
			fprintf(f, "[%s]\n", neighbor->value);
		}
	}
}

void dfs_step(map_linked_list_t * graph, char * node, map_bool_t * discovered, string_linked_list * topological_sort)
{
	map_set(discovered, node, true);
	// iterates over neighbors
	string_linked_list * neighbors = *map_get(graph, node);  
	for (int i=1; i <= neighbors->count; i++)
	{
		char * neighbor = string_linked_list_get(neighbors, i);
		// Check if discovered
		if (*map_get(discovered, neighbor))
		{
			continue;
		}
		dfs_step(graph, neighbor, discovered, topological_sort);
	}
	
	// after iteration marks as visited
	string_linked_list_push(topological_sort, node);
	// TODO: free neighbors linked list
}

string_linked_list * dfs1(map_linked_list_t * graph)
{
	string_linked_list * topological_sort = string_linked_list_init();
	map_bool_t discovered;
	map_init(&discovered);
	
	// Populates discovered bool map
	const char * node;
	map_iter_t graph_iter = map_iter(graph);

	while ((node = map_next(graph, &graph_iter)))
	{
		map_set(&discovered, node, false);
	}
	
	printf("\n");
	graph_iter = map_iter(graph);
	while ((node = map_next(graph, &graph_iter)))
	{
		if (*map_get(&discovered, node))
		{
			continue;
		}
		dfs_step(graph, (char *) node, &discovered, topological_sort);
	}
	map_deinit(&discovered);
	
	return topological_sort;
}

sccs_list * dfs2(map_linked_list_t * graph, string_linked_list * topological_order)
{
	map_bool_t discovered;
	map_init(&discovered);
	sccs_list * sccs = sccs_list_init();
	if (sccs == NULL)
	{
		printf("ERRO! Alocação de lista de componentes fortememente conectadas falhou");
		exit(1);
	}

	// Populates discovered bool map
	const char * node;
	map_iter_t graph_iter = map_iter(graph);
	
	while ((node = map_next(graph, &graph_iter)))
	{
		map_set(&discovered, node, false);
	}

    for (int i=1; i <= topological_order->count; i++)
    {
        char * current_node = string_linked_list_pop(topological_order);
		if (*map_get(&discovered, current_node))
		{
			continue;
		}
		string_linked_list * scc_nodes = string_linked_list_init();
		dfs_step(graph, current_node, &discovered, scc_nodes);
		strongly_connected_component * scc = scc_init(scc_nodes);
		sccs_list_push(sccs, scc);
	}
	return sccs;
}

