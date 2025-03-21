#include <string.h>
#include <ctype.h>
#include "parser.h"

/*
处理逻辑：
 1. 找到第一个非空白字符的位置
 2. 找到最后一个非空白字符的位置
 3. 将有效内容移动到字符串起始位置
 4. 添加字符串终止符 */
static void trim(char *str) {
    int start = 0, end = strlen(str) - 1;
    
    while (isspace(str[start])) start++;
    while (end >= start && isspace(str[end])) end--; //空白处理
    
    int len = end - start + 1;
    if (start > 0) memmove(str, str + start, len); //计算有效内容长度并移动
    str[len] = '\0'; //追加终止符
}

/*
处理逻辑：
 * 1. 使用strtok按空格/tab分割依赖项
 * 2. 对每个依赖项进行trim处理
 * 3. 将有效依赖项存入目标结构体
 * 4. 维护依赖项计数器
 */
static void parse_dependencies(char *str, Target *target) {
    char *dep = strtok(str, " \t");
    while (dep != NULL) {
        trim(dep);
        if (*dep) {
            strncpy(target->dependencies[target->dep_count], dep, 32);
            target->dependencies[target->dep_count][32] = '\0';
            target->dep_count++;
        }
        dep = strtok(NULL, " \t");
    }
}

void parse_makefile(FILE *file, Target targets[], int *target_count, Error errors[], int *error_count) {
    char line[MAX_LINE_LENGTH];
    Target *current = NULL;
    int line_num = 0;    //当前处理的目标与行号

    while (fgets(line, sizeof(line), file)) {
        line_num++;
        line[strcspn(line, "\n")] = '\0';
        if (line[0] == '#' || strlen(line) == 0) continue;
        //命令行处理
        if (line[0] == '\t') {
            if (!current) {
                snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                    "Command without target");
                errors[(*error_count)++].line = line_num;
                continue;
            }
            strncpy(current->commands[current->cmd_count], line + 1, 255);
            current->cmd_count++;
        } 
        //目标行处理
        else {
            char *colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char *target_part = line;
                char *deps_part = colon + 1;
                trim(target_part);
                //检查重复目标定义
                for (int i = 0; i < *target_count; i++) {
                    if (strcmp(targets[i].name, target_part) == 0) {
                        snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                            "Duplicate target definition '%s'", target_part);
                        errors[(*error_count)++].line = line_num;
                        goto NEXT_LINE;
                    }
                }

                if (*target_count >= MAX_TARGETS) {
                    snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                        "Too many targets");
                    errors[(*error_count)++].line = line_num;
                    continue;
                }

                current = &targets[(*target_count)++];
                strncpy(current->name, target_part, 32);
                current->name[32] = '\0';
                current->dep_count = current->cmd_count = 0;
                current->line_number = line_num;
                //解析依赖项
                trim(deps_part);
                parse_dependencies(deps_part, current);
            } 
            else {
                snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                    "Invalid syntax");
                errors[(*error_count)++].line = line_num;
            } //无效语法处理
        }
        NEXT_LINE:;
    }
}