#include "preprocess.h"
#include"checker.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char* argv[]) {
    bool verbose = false;

    // 解析命令行参数
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        }
    }

    // 检查Makefile是否存在
    if (access("Makefile", F_OK) == -1) {
        fprintf(stderr, "Error: Makefile not found in current directory\n");
        return 1;
    }

    int line_count = 0;
    ProcessedLine* processed = preprocess_makefile("Makefile", verbose, &line_count);

    if (!processed) {
        return 1;
    }

    // 打印处理结果（调试用）
    /*
    if (verbose) {
        printf("Cleaned Makefile:\n");
        for (int i = 0; i < line_count; i++) {
            printf("%s\n", processed[i]);
        }
    }
        */
    // 语法检查核心逻辑
    bool in_rule = false;
    for (int i = 0; i < line_count; i++) {
        const char* line_content = processed[i].content; // 处理后的内容
        const int original_line_num = processed[i].original_line; // 原始行号

    // 跳过空行
        if (strlen(line_content) == 0) continue;

    // 检查语法规则
        check_line(line_content, original_line_num, &in_rule);
    }

    // 释放预处理结果内存
    for (int i = 0; i < line_count; i++) {
        free(processed[i].content);
    }
    free(processed);

    return 0;
}
