#ifndef RELYCHECKER_H
#define RELYCHECKER_H

#include "target.h"

void check_dependencies(Target targets[], int target_count, Error errors[], int *error_count);

#endif