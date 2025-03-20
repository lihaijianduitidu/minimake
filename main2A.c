// main.c
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "relychecker.h"

int main() {
    Target targets[MAX_TARGETS];
    Error errors[MAX_ERRORS];
    int target_count = 0, error_count = 0;

    FILE *file = fopen("Makefile", "r");
    if (!file) {
        perror("Error opening Makefile");
        return EXIT_FAILURE;
    }

    parse_makefile(file, targets, &target_count, errors, &error_count);
    fclose(file);

    check_dependencies(targets, target_count, errors, &error_count);

    for (int i = 0; i < error_count; i++) {
        printf("Line %d: %s\n", errors[i].line, errors[i].message);
    }

    return error_count ? EXIT_FAILURE : EXIT_SUCCESS;
}