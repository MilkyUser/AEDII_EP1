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

int main()
{
	uint16_t no_nodes;
	scanf("%" SCNu16, &no_nodes);
	fgetc(stdin); // This fgetc call consumes the new line character following the first read	
	map_linked_list_t original_graph;
	map_init(&original_graph);
	
	for (int line=0; line<no_nodes; line++)
	{
		char * current_node_id = calloc(1, NODE_ID_LEN);
		string_linked_list * vicinity = string_linked_list_init();
		char last_char = scanner_fread_word(stdin, current_node_id, NODE_ID_LEN);
		map_set(&original_graph, current_node_id, vicinity);
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
	fprint_graph(stdout, &original_graph);
	
	printf("-------------------\n");
	
	printf(" TOPOLOGICAL ORDER\n\n");
	string_linked_list * topological_order = dfs1(&original_graph);
	fprintf_string_linked_list(stdout, topological_order, " ");	
	
	printf("-------------------\n");
	
	map_linked_list_t transposed_graph = *transpose_graph(&original_graph);
	fprint_graph(stdout, &transposed_graph);
	
	printf("-------------------\n");
	printf("       SCCS\n\n");

	sccs_list * sccs = dfs2(&transposed_graph, topological_order);
	fprintf(stdout, "ENTRA\n");
	fprint_sccs(stdout, sccs, "| ");
	
	printf("\nFINISH\n");
	return 0;
}

