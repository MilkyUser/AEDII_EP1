#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include "node.h"

node * get_node_from_line();
char fread_word(FILE * f, char * buffer);

#endif

