#include "checker.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 检查每行的语法规则
void check_line(const char *processed_line, const char *trimmed_line, int line_number, bool *in_rule) {
    if (processed_line[0] == '\t') {
        // 检查命令是否在规则之后
        if (!(*in_rule)) {
            printf("Line%d: Command found before rule\n", line_number);
        }
    } else {
        // 检查目标是否有冒号
        if (strchr(trimmed_line, ':') != NULL) {
            *in_rule = true;
        } else {
            printf("Line%d: Missing colon in target definition\n", line_number);
            *in_rule = false;
        }
    }
}