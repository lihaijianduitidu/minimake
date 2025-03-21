#ifndef CHECKER_H
#define CHECKER_H
#include<stdbool.h>

//检查每行的语法规则
void check_line(const char *processed_line, const char *trimmed_line, int line_number, bool *in_rule);

#endif