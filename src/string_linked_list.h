#ifndef STRING_LINKED_LIST
#define STRING_LINKED_LIST
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct string_linked_list_node
{
	char * value;
	struct string_linked_list_node * next;
} string_linked_list_node;

typedef struct string_linked_list
{
	struct string_linked_list_node * head;
	struct string_linked_list_node * tail;
	uint16_t count;
} string_linked_list;

string_linked_list * string_linked_list_init();
bool string_linked_list_append(string_linked_list * list, char * value); //inserts value at the end of the list O(n)
bool string_linked_list_push(string_linked_list * list, char * value); //inserts value at the begining of the list O(1)
char * string_linked_list_pull(string_linked_list * list); //removes last item of the list - O(n)
char * string_linked_list_pop(string_linked_list * list); //removes first item of the list - O(1)
char * string_linked_list_get(string_linked_list * list, int n); // gets nth item of list, returns null if n > count
void fprintf_string_linked_list(FILE * f, string_linked_list * list, char * sep);
#endif 

