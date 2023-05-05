#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
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

bool string_linked_list_push(string_linked_list * list, char * value)
{
	string_linked_list_node * new_node = calloc(1, sizeof(string_linked_list_node)); 
	new_node->value = calloc(1, NODE_ID_LEN);
	if (new_node == NULL || new_node->value == NULL)
	{
		return false;
	}
	strncpy(new_node->value, value, NODE_ID_LEN);
	new_node->next = list->head->next;
	list->head->next = new_node;
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

char * string_linked_list_pop(string_linked_list * list)
{
	if (list->count == 0)
	{
		return NULL;
	}
	char * value = calloc(1, NODE_ID_LEN);
	strncpy(value, list->head->next->value, NODE_ID_LEN);
	string_linked_list_node * popped = list->head->next;
	list->head->next = popped->next;
	free(popped->value);
	free(popped);
	return value;
}

char * string_linked_list_get(string_linked_list * list, int v)
{
	// This is a naive implementation of the get function
	// a better solution should keep track of each index at each loaded list
	if (v > list->count)
	{
		return NULL;
	} 
	string_linked_list_node * current_node = list->head;
	for (int i=0; i<v; i++)
	{
		current_node = current_node->next;
	}
	return current_node->value;	
}

void fprintf_string_linked_list(FILE * f, string_linked_list * list, char * sep)
{	
	if (list->count <= 0)
	{
		return;
	}
	string_linked_list_node * slln = malloc(sizeof(string_linked_list_node));
	slln = list->head->next;
	int i = 1;
	if (list->count > 0)
	{	
		fprintf(f, "%s", slln->value);
	}
	slln = slln->next;
	for (; i < list->count; i++)
	{
		fprintf(f, "%s%s", sep, slln->value);	
		slln = slln->next;
	}
	fprintf(f, "\n");
	free(slln);
}

