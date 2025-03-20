#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <stdbool.h>

#define MAX_LINE_LEN 1024

// 处理Makefile并返回清理后的内容
typedef struct {
    char* content;          // 处理后的内容
    int original_line;     // 原始行号
} ProcessedLine;

ProcessedLine* preprocess_makefile(const char* filename, bool verbose, int* line_count);

#endif