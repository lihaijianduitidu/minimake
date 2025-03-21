#include "preprocess.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

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
    char** processed = preprocess_makefile("Makefile", verbose, &line_count);

    if (!processed) {
        return 1;
    }

    // 打印处理结果（供调试）
    if (verbose) {
        printf("Cleaned Makefile:\n");
        for (int i = 0; i < line_count; i++) {
            printf("%s\n", processed[i]);
        }
    }

    // 释放内存
    for (int i = 0; i < line_count; i++) {
        free(processed[i]);
    }
    free(processed);

    return 0;
}