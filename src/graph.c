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

void print_graph(FILE * f, map_linked_list_t * graph)
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

