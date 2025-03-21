// main.c
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "relychecker.h"

int main() {
    Target targets[MAX_TARGETS];
    Error errors[MAX_ERRORS];
    int target_count = 0, error_count = 0;

    FILE *file = fopen("Makefile", "r");  //打开Makefile文件
    if (!file) {  //检查文件是否打开成功
        perror("Error opening Makefile");   //输出系统错误信息
        return EXIT_FAILURE;
    }

    parse_makefile(file, targets, &target_count, errors, &error_count);
    fclose(file);  //解析makefile文件并关闭

    check_dependencies(targets, target_count, errors, &error_count);  //检查依赖项

    for (int i = 0; i < error_count; i++) {
        printf("Line %d: %s\n", errors[i].line, errors[i].message);
    }

    return error_count ? EXIT_FAILURE : EXIT_SUCCESS;
}