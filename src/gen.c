#include "gen.h"
#include "./map/src/map.h"
#include "string_linked_list.h"
#include <stdlib.h>

char * gen_get_ascii(char n)
{
	char * ascii_value = malloc(2);
	ascii_value[1] = '\0';
	char char_value;
	if (n < 26)
	{
		char_value = n + 97;
	}
	else
	{
		if (n < 26*2)
		{
			char_value = n + 65-26;
		}
		else
		{
			if (n < 10 + 26*2)
			{
				char_value = n + 48-26*2;
			}
		}
	}
	ascii_value[0] = char_value;
	return ascii_value;
}

map_linked_list_t * generate_graph(int no_vertices, int no_edges)
{
	if (no_edges >= no_vertices*no_vertices)
	{
		printf("ERRO! Número de arestas deve ser menor que quadrado de vértices");
		exit(1);
	}
	if (no_vertices > 62)
	{
		printf("ERRO! A função geradora de grafos só aceita até 62 vértices");
		exit(1);
	}
	double prob = (double) no_edges / (no_vertices*(no_vertices-1));
	map_linked_list_t * graph = malloc(sizeof(map_linked_list_t));
	map_init(graph);
	
	for (int v = 0; v < no_vertices; v++)
	{
		map_set(graph, gen_get_ascii((char) v), string_linked_list_init());
    	for (int w = 0; w < no_vertices; ++w)
    	{
        	if (ALLOW_SELF_LOOPS || v != w) // Won't allow self loops
        	{
           		if (rand() < prob*(RAND_MAX+1.0))
           		{
           			string_linked_list_push(*map_get(graph, gen_get_ascii((char) v)), gen_get_ascii((char) w)); 
				}
			}
		}
	}
	return graph;
}

