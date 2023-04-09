#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "node.h"

node * get_node_from_line()
{

	

}

void id_too_large_error_throw()
{
	printf("ERRO, PALAVRA MUITO GRANDE (MAX: 63 CARACTERES)\n");
	exit(1);
}

char fread_word(FILE * f, char * buffer)
{
	char current_char = fgetc(f);
	char current_char_index;
	
	// Next loop ignore leading whitespaces
	while(current_char == ' ')
	{
		current_char = fgetc(f);
	}
	
	for 
	(
		current_char_index = 0;
		!(current_char=='\n' || current_char==':' || current_char==';' || current_char==EOF) && current_char_index < NODE_ID_LEN;
		current_char_index++
	)
	{
		buffer[current_char_index] = current_char;
		current_char = fgetc(f);
		int no_of_whitespaces = 0;
		
		// Next loop ignore trailing whitespaces
		while(current_char == ' ')
		{
			no_of_whitespaces++;
			current_char = fgetc(f);
			if (current_char=='\n' || current_char==':' || current_char==';')
			{
				return current_char;
			}
			else if (current_char != ' ')
			{
				if (no_of_whitespaces + current_char_index >= NODE_ID_LEN)
				{
					id_too_large_error_throw();
				}
				// Appends any whitespaces in the middle of the string
				else
				{
					sprintf(buffer, "%s%0*c", buffer, no_of_whitespaces, ' ');
					current_char_index += no_of_whitespaces; 
				} 
			}
		}
	}
	if (current_char_index >= NODE_ID_LEN)
	{
		id_too_large_error_throw();
	}
	return current_char;
}


