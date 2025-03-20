#include <string.h>
#include <ctype.h>
#include "parser.h"

static void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    
    while (isspace(str[start])) start++;
    while (end >= start && isspace(str[end])) end--;
    
    int len = end - start + 1;
    if (start > 0) memmove(str, str + start, len);
    str[len] = '\0';
}

static void parse_dependencies(char *str, Target *target) {
    char *dep = strtok(str, " \t");
    while (dep != NULL) {
        trim(dep);
        if (*dep) {
            strncpy(target->dependencies[target->dep_count], dep, 32);
            target->dependencies[target->dep_count][32] = '\0';
            target->dep_count++;
        }
        dep = strtok(NULL, " \t");
    }
}

void parse_makefile(FILE *file, Target targets[], int *target_count, Error errors[], int *error_count) {
    char line[MAX_LINE_LENGTH];
    Target *current = NULL;
    int line_num = 0;

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '#' || strlen(line) == 0) continue;

        if (line[0] == '\t') {
            if (!current) {
                snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                    "Command without target");
                errors[(*error_count)++].line = line_num;
                continue;
            }
            strncpy(current->commands[current->cmd_count], line + 1, 255);
            current->cmd_count++;
        } else {
            char *colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char *target_part = line;
                char *deps_part = colon + 1;
                trim(target_part);

                for (int i = 0; i < *target_count; i++) {
                    if (strcmp(targets[i].name, target_part) == 0) {
                        snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                            "Duplicate target definition '%s'", target_part);
                        errors[(*error_count)++].line = line_num;
                        goto NEXT_LINE;
                    }
                }

                if (*target_count >= MAX_TARGETS) {
                    snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                        "Too many targets");
                    errors[(*error_count)++].line = line_num;
                    continue;
                }

                current = &targets[(*target_count)++];
                strncpy(current->name, target_part, 32);
                current->name[32] = '\0';
                current->dep_count = current->cmd_count = 0;
                current->line_number = line_num;

                trim(deps_part);
                parse_dependencies(deps_part, current);
            } else {
                snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                    "Invalid syntax");
                errors[(*error_count)++].line = line_num;
            }
        }
        NEXT_LINE:;
    }
}