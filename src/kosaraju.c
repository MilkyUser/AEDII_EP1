#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "graph.h"
#include "scanner.h"
#include "./map/src/map.h"
#include "string_linked_list.h"
#include "strongly_connected_component.h"

int main(int argc, char ** argv)
{
	if (argc > 2)
	{
		// TODO: Call generator
		return 0;
	}

	char * sep = "";
	if (argc > 1)
	{
		sep = argv[1];
	}
	uint16_t no_nodes;
	scanf("%" SCNu16, &no_nodes);
	fgetc(stdin); // This fgetc call consumes the new line character following the first read	
	map_linked_list_t * original_graph = malloc(sizeof(map_linked_list_t));
	map_init(original_graph);
	
	for (int line=0; line<no_nodes; line++)
	{
		char * current_node_id = calloc(1, NODE_ID_LEN);
		string_linked_list * vicinity = string_linked_list_init();
		char last_char = scanner_fread_word(stdin, current_node_id, NODE_ID_LEN);
		map_set(original_graph, current_node_id, vicinity);
		while(last_char != '\n')
		{
			char * value = calloc(1, NODE_ID_LEN); 
			last_char = scanner_fread_word(stdin, value, NODE_ID_LEN);
			if (strcmp(value, "") == 0)
			{
				break;
			}
			string_linked_list_append(vicinity, value);
		}
	}
	
	int mode;
	scanf("%d", &mode);
	
	map_linked_list_t * transposed_graph = transpose_graph(original_graph);
	string_linked_list * topological_order;
	map_linked_list_t * sccs;
	if (mode == 2)
	{
		topological_order = dfs1(transposed_graph);
		sccs = dfs2(original_graph, topological_order, sep);
	} else
	{
		if (mode != 1)
		{
			fprintf(stdout, "ERRO! MODO INVÁLIDO1\n");
			return 1;
		}
		topological_order = dfs1(original_graph);
		sccs = dfs2(transposed_graph, topological_order, sep);
	}

	map_linked_list_t sccs_graph;
	map_init(&sccs_graph);
	const char * node;
	map_iter_t graph_iter = map_iter(sccs);
	int scc_count = 0;
	while ((node = map_next(sccs, &graph_iter)))
	{
		scc_count++;
		string_linked_list * scc_vicinity = string_linked_list_init();
		string_linked_list * components = *map_get(sccs, node);
		string_linked_list_node * component = components->head->next;
		for (int component_index=1; component_index<=components->count; component_index++)
		{
			string_linked_list * component_vicinity = *map_get(original_graph, component->value);
			string_linked_list_node * component_neighbor = component_vicinity->head->next;
			for 
			(
				int component_neighbor_index=1;
			 	component_neighbor_index<=component_vicinity->count;
			 	component_neighbor_index++
			 )
			{
				const char * node2;
				map_iter_t graph_iter2 = map_iter(sccs);
				while ((node2 = map_next(sccs, &graph_iter2)))
				{
					if
					(
						scc_contains(*map_get(sccs, node2), component_neighbor->value) && 
						strcmp(node, (char *)node2)!=0 &&
						!string_linked_list_contains(scc_vicinity, (char *)node2)
					)
					{
						string_linked_list_push(scc_vicinity, (char *)node2);
					}
				}
				component_neighbor = component_neighbor->next;
			} 
			component = component->next;
		} 
		map_set(&sccs_graph, node, scc_vicinity);
	}
	scc_count == 1 ? fprintf(stdout, "Sim\n"): fprintf(stdout, "Não\n");
	fprintf(stdout, "%d\n", scc_count);
	topological_order = dfs1(&sccs_graph);
	fprintf_string_linked_list(stdout, topological_order, " ");
	fprint_graph(stdout, &sccs_graph, ": ", "; ", "\n");
	return 0;
}

