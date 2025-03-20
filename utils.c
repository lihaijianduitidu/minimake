#include "utils.h"
#include <string.h>
#include <ctype.h>

// 移除行中的注释部分（以#开头）
void remove_comment(char *line) {
    char *comment_start = strchr(line, '#');
    if (comment_start != NULL) {
        *comment_start = '\0';
    }
}

// 去除字符串前后的空白字符
void trim(char *line) {
    if (line == NULL) return;

    // 去除前导空白
    char *start = line;
    while (isspace((unsigned char)*start)) start++;
    memmove(line, start, strlen(start) + 1);

    // 去除尾部空白
    char *end = line + strlen(line) - 1;
    while (end >= line && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
}