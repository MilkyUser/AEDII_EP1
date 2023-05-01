#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#define ASSERT_BUFFER_SIZE false

char scanner_fread_word(FILE * f, char * buffer, int buffer_size);

#endif

