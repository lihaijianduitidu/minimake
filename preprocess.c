/* preprocess.c */
#include "preprocess.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

// 检查是否空白行
static bool is_whitespace_only(const char* line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) {
            return false;
        }
        line++;
    }
    return true;
}

// 去除行尾空格
static void trim_trailing_spaces(char* line) {
    char* end = line + strlen(line) - 1;
    while (end >= line && isspace((unsigned char)*end)) {
        end--;
    }
    *(end + 1) = '\0';
}

// 处理单行
static void process_line(char* line) {
    // 去除注释
    char* comment_pos = strchr(line, '#');
    if (comment_pos) {
        *comment_pos = '\0';
    }

    // 去除行尾空格
    trim_trailing_spaces(line);
}

char** preprocess_makefile(const char* filename, bool verbose, int* line_count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    char buffer[MAX_LINE_LEN];
    char** lines = NULL;
    int capacity = 0;
    *line_count = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        process_line(buffer);

        // 跳过空行
        if (is_whitespace_only(buffer)) {
            continue;
        }

        // 动态数组扩容
        if (*line_count >= capacity) {
            capacity = (capacity == 0) ? 16 : capacity * 2;
            lines = realloc(lines, capacity * sizeof(char*));
        }

        lines[*line_count] = strdup(buffer);
        (*line_count)++;
    }

    fclose(file);

    // 调试模式输出
    if (verbose) {
        FILE* output = fopen("Minimake_cleared.mk", "w");
        if (output) {
            for (int i = 0; i < *line_count; i++) {
                fprintf(output, "%s\n", lines[i]);
            }
            fclose(output);
        }
    }

    return lines;
}