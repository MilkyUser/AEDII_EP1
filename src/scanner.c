#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanner.h"
#include "graph.h"


void id_too_large_error_throw(int buffer_size)
{
	printf("ERRO, PALAVRA MUITO GRANDE (MAX: %d CARACTERES)\n", buffer_size-1);
	exit(1);
} 

// This function reads a string from a file, considering {'\n', ':', ';'} as separators.
// It alsos trims leading and trailing whitespaces.
char scanner_fread_word(FILE * f, char * buffer, int buffer_size)
{
	char current_char = fgetc(f);
	int current_char_index;
	buffer_size--;
	
	// Next loop ignore leading whitespaces
	while(current_char == ' ')
	{
		current_char = fgetc(f);
	}
	
	for 
	(
		current_char_index = 0;
		!(current_char=='\n' || current_char==':' || current_char==';' || current_char==EOF) && current_char_index < buffer_size;
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
				if (no_of_whitespaces + current_char_index >= buffer_size)
				{
					if (ASSERT_BUFFER_SIZE)
					{
						id_too_large_error_throw(buffer_size);
					}
					else
					{
						sprintf(buffer, "%s%0*c", buffer, current_char_index - buffer_size, ' ');
					}
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
	
	// Ideally the buffer size assertion should be implemented with macros, as the flag is hardcoded in the scanner.h header file.
	if (ASSERT_BUFFER_SIZE)
	{
		if (current_char_index >= buffer_size)
		{
			id_too_large_error_throw(buffer_size);
		}
		buffer[current_char_index + 1] = '\0';
	}
	else
	{
		if (current_char_index >= buffer_size)
		{
			buffer[current_char_index] = '\0';
		}
		buffer[current_char_index + 1] = '\0';
		
		// Consumes any character after the buffer size is reached
		while (!(current_char=='\n' || current_char==':' || current_char==';' || current_char==EOF))
		{
			current_char = fgetc(f);
		}
		
	}	
	return current_char;
}


