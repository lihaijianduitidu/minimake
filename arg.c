#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg.h"

static void print_usage(const char *program_name) {
    fprintf(stderr, "用法: %s [--help]\n", program_name);
}

static void print_help(const char *program_name) {
    printf("Usage: %s [--help]\n", program_name);
    printf("\n选项：\n");
    printf("  --help  显示帮助信息。\n");
}

void arguments(int argc, char *argv[]) {
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--help") == 0) {
            print_help(argv[0]);
            exit(EXIT_SUCCESS);
        }
    }


    if (argc > 1) {
        fprintf(stderr, "错误：无效参数 '%s'\n", argv[1]);
        print_usage(argv[0]);
        exit(EXIT_FAILURE);
    }
}