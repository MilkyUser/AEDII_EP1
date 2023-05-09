#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "string_linked_list.h"
#include "graph.h"
#include "strongly_connected_component.h"

bool scc_contains(string_linked_list * scc, char * node)
{
	if (scc->head->next == NULL)
	{
		return false;
	}
	string_linked_list_node * component = scc->head->next;
	for (int i=1; i<=scc->count; i++)
	{
		if (strcmp(node, component->value) == 0)
		{
			return true;
		}
		component = component->next; 
	}
	return false;
}

bool scc_equals(string_linked_list * scc1, string_linked_list * scc2)
{
	if (scc1->count != scc2->count)
	{
		return false;
	}
	if (scc1->count == 0)
	{
		return true;
	}
	map_str_t scc1_map;
	string_linked_list_node * slln = scc1->head->next;
	for (int i=0; i<scc1->count; i++)
	{
		map_set(&scc1_map, slln->value, "");
		slln = slln->next;
	}
	slln = scc2->head->next;
	for (int i=0; i<scc1->count; i++)
	{
		if (map_get(&scc1_map, slln->value)==NULL)
		{
			return false;
		}
		slln = slln->next;
	}
	map_init(&scc1_map);
	map_deinit(&scc1_map);
	return true;
}

void fprint_sccs(FILE * f, map_linked_list_t * list, char * sep)
{
	const char *key;
	map_iter_t iter = map_iter(list);
	key = map_next(list, &iter);
	printf("%s", key);
	while ((key = map_next(list, &iter)))
	{
	  printf("%s%s", sep, key);
	}
}

// snippet from https://stackoverflow.com/questions/23189630/how-to-use-qsort-for-an-array-of-strings
int __strcmp(const void * str1, const void * str2)
{
    char *const *pp1 = str1;
    char *const *pp2 = str2;
    return strcmp(*pp1, *pp2);
}

char ** scc_to_string_arr(string_linked_list * scc)
{
	if (scc->count == 0)
	{
		fprintf(stdout, "ERRO! Componente conectada vazia na lista de componentes fortemente conectadas\n");
	}
	char ** string_arr = calloc(scc->count, sizeof(char*));
	
	string_linked_list_node * slln = scc->head->next;
	
	for(int i=0; i<scc->count; i++)
	{
		string_arr[i] = slln->value;
		slln = slln->next;
	}
	
	qsort(string_arr, scc->count, sizeof(*string_arr), __strcmp);
	
	return string_arr;
}

