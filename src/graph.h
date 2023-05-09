#ifndef GRAPH_H
#define GRAPH_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include "string_linked_list.h"
#include "strongly_connected_component.h"
#include "./map/src/map.h"

#define NODE_ID_LEN 64 

typedef map_t(string_linked_list*) map_linked_list_t;
typedef map_t(bool) map_bool_t; 
map_linked_list_t * transpose_graph(map_linked_list_t * original_graph);
void fprint_graph(FILE * f, map_linked_list_t * graph, char * vicinity_sep1, char * vicinity_sep2, char * node_sep);
string_linked_list * dfs1(map_linked_list_t * graph);
map_linked_list_t * dfs2(map_linked_list_t * graph, string_linked_list * topological_order, char * sep);

#endif
