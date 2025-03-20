#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "checker.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    const char *filename = argc > 1 ? argv[1] : "Makefile";
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char *line = NULL;
    size_t len = 0;
    size_t read;
    int line_number = 0;
    bool in_rule = false;

    while ((read = getline(&line, &len, file)) != -1) {
        line_number++;
        line[strcspn(line, "\n")] = '\0'; // 去除换行符

        char processed_line[1024];
        strcpy(processed_line, line);
        remove_comment(processed_line); // 移除注释

        char trimmed_line[1024];
        strcpy(trimmed_line, processed_line);
        trim(trimmed_line); // 去除前后空白

        if (strlen(trimmed_line) == 0) {
            continue; // 跳过空行
        }

        check_line(processed_line, trimmed_line, line_number, &in_rule);
    }

    free(line);
    fclose(file);
    return EXIT_SUCCESS;
}