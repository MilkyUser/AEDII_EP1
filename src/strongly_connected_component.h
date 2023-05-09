#ifndef SCC_H
#define SCC_H
#include "string_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include "./map/src/map.h"

bool scc_contains(string_linked_list * scc, char * node);
bool scc_equals(string_linked_list * scc1, string_linked_list * scc2); // compares two scc's, returns true if both have the same elements
char ** scc_to_string_arr(string_linked_list * scc);

#endif
