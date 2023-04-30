#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include "node.h"
#define ASSERT_BUFFER_SIZE false

node * get_node_from_line();
char scanner_fread_word(FILE * f, char * buffer, int buffer_size);

#endif

