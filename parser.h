#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "target.h"

void parse_makefile(FILE *file, Target targets[], int *target_count, Error errors[], int *error_count);

#endif