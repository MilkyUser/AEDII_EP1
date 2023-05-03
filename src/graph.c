#include "string_linked_list.h"
#include "./map/src/map.h"
#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

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

void dfs1_step(map_linked_list_t * graph, char * node, map_bool_t * discovered, string_linked_list * topological_sort)
{
	printf("Discovering %s\n", node);
	map_set(discovered, node, true);
	// iterates over neighbors
	for (int i=1; i < (*map_get(graph, node))->count; i++)
	{
		char * neighbor = string_linked_list_get(*map_get(graph, node), i);
		// Check if discovered
		if (*map_get(discovered, neighbor))
		{
			continue;
		}
		dfs1_step(graph, neighbor, discovered, topological_sort);
	}
	
	// after iteration marks as visited
	printf("ENTRA %s\n", node);
	string_linked_list_push(topological_sort, node);
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
	graph_iter = map_iter(&discovered);
	while ((node = map_next(&discovered, &graph_iter)))
	{
		if (*map_get(&discovered, node))
		{
			continue;
		}
		printf("\tAttempting begin at %s -> %s\n", node, *map_get(&discovered, node) ? "true": "false"); 
		dfs1_step(graph, (char *) node, &discovered, topological_sort);
	}
	map_deinit(&discovered);
	
	return topological_sort;
}

