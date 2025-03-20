#include "checker.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void check_line(const char* line, int line_number, bool* in_rule) {
    // 检查是否是命令（以\t开头）
    if (line[0] == '\t') {
        if (!(*in_rule)) {
            printf("Line%d: Command found before rule\n", line_number);
        }
        return;
    }

    // 检查目标行是否有冒号
    if (strchr(line, ':') != NULL) {
        *in_rule = true;
    } else {
        printf("Line%d: Missing colon in target definition\n", line_number);
        *in_rule = false;
    }
}