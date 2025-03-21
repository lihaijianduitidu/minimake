#include <unistd.h>
#include <string.h>
#include "relychecker.h"

void check_dependencies(Target targets[], int target_count, Error errors[], int *error_count) {
    for (int i = 0; i < target_count; i++) {  //遍历目标
        Target *t = &targets[i];
        for (int j = 0; j < t->dep_count; j++) {  //遍历依赖项
            char *dep = t->dependencies[j];
            if (access(dep, F_OK) == 0) continue;  //检查依赖项是否存在

            int valid = 0;
            for (int k = 0; k < target_count; k++) {  //检查依赖项是否为已定义的目标
                if (strcmp(targets[k].name, dep) == 0) {
                    valid = 1;
                    break;  //找到匹配项后提前跳出循环
                }
            }

            if (!valid && *error_count < MAX_ERRORS) {  //如果依赖项既不是文件也不是目标，则报错
                snprintf(errors[*error_count].message, sizeof(errors[*error_count].message),
                    "Invalid dependency '%s'", dep);
                errors[(*error_count)++].line = t->line_number;
            }
        }
    }
}