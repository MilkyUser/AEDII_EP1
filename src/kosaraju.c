#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include "graph.h"
#include "scanner.h"
#include "./map/src/map.h"
#include "string_linked_list.h"

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
	
	printf("------------------\n");
	printf("       DFS\n");
	printf("");
	string_linked_list * my_list = dfs1(&original_graph);
	printf("%d ", my_list->count);
	fprintf_string_linked_list(stdout, my_list);	
	printf("------------------\n");
	
	map_linked_list_t transposed_graph = *transpose_graph(&original_graph);
	fprint_graph(stdout, &transposed_graph);
	
	printf("FINISH\n");
	return 0;
}

