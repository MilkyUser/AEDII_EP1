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
	char * sep = "|";
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
	
	char mode;
	scanf("%c", &mode);
	
	string_linked_list * topological_order = dfs1(&original_graph);	
	map_linked_list_t transposed_graph = *transpose_graph(&original_graph);
	printf("       SCCS\n");

	sccs_list * sccs = dfs2(&transposed_graph, topological_order);
	fprintf(stdout, "\n");
	fprint_sccs(stdout, sccs, " | ");
	map_linked_list_t sccs_graph;
	map_init(&sccs_graph);
	strongly_connected_component * scc = sccs->head;
	for (int i=0; i<sccs->count; i++)
	{
		char * key = calloc(1, NODE_ID_LEN * scc->nodes->count + (scc->nodes->count-1)*strlen(sep) + 1); 
		char ** scc_nodes = scc_to_string_arr(scc);
		strcpy(key, scc_nodes[0]);
		for (int i=1; i<scc->nodes->count; i++)
		{
			strcat(key, sep);
			strcat(key, scc_nodes[i]);
		}
		map_set(&sccs_graph, key, string_linked_list_init());
		scc = scc->next;
	}
	
	fprint_graph(stdout, &sccs_graph);
	
	printf("\nFINISH\n");
	return 0;
}

