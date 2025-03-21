#ifndef PREPROCESS_H
#define PREPROCESS_H

#include <stdbool.h>

#define MAX_LINE_LEN 1024

// 处理makefile并返回清理后的内容
char** preprocess_makefile(const char* filename, bool verbose, int* line_count);

#endif