// checker.c
#include <unistd.h>
#include <string.h>
#include "relychecker.h"

void check_dependencies(Target targets[], int target_count, Error errors[], int *error_count) {
    for (int i = 0; i < target_count; i++) {
        Target *t = &targets[i];
        for (int j = 0; j < t->dep_count; j++) {
            char *dep = t->dependencies[j];
            if (access(dep, F_OK) == 0) continue;

            int valid = 0;
            for (int k = 0; k < target_count; k++) {
                if (strcmp(targets[k].name, dep) == 0) {
                    valid = 1;
                    break;
                }
            }

            if (!valid && *error_count < MAX_ERRORS) {
                snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                    "Invalid dependency '%s'", dep);
                errors[(*error_count)++].line = t->line_number;
            }
        }
    }
}