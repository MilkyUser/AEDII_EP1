#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "graph.h"
#include "string_linked_list.h"

string_linked_list * string_linked_list_init()
{
	string_linked_list * list_pointer = malloc(sizeof(string_linked_list));
	string_linked_list_node * head = malloc(sizeof(string_linked_list_node));
	if (list_pointer == NULL || head == NULL)
	{
		return NULL;
	}
	head->value = calloc(1, 5); 
	head->value = strcpy(head->value, "HEAD");
	head->next = NULL;
	list_pointer->head = head;
	list_pointer->tail = head;
	list_pointer->count = 0; 
	return list_pointer;
}

bool string_linked_list_append(string_linked_list * list, char * value)
{
	string_linked_list_node * node = malloc(sizeof(string_linked_list_node));
	if (node == NULL)
	{
		return false;
	}
	node->next = NULL;
	node->value = calloc(1, NODE_ID_LEN);
	if (node->value == NULL) 
	{
		return false;
	}
	strncpy(node->value, value, NODE_ID_LEN);
	list->tail->next = node;
	list->tail = node;
	list->count++;
	return true;
}

char * string_linked_list_pull(string_linked_list * list)
{
	char * value = calloc(1, NODE_ID_LEN);
	strncpy(value, list->tail->value, NODE_ID_LEN);
	free(list->tail->value);
	free(list->tail);
	list->count--;
	string_linked_list_node * current_node = list->head;
	for (int i=0; i<list->count; i++)
	{
		current_node = current_node->next;
	}
	list->tail = current_node;
	return value;
}

