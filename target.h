#ifndef TARGET_H
#define TARGET_H

#define MAX_TARGETS 100
#define MAX_DEPS 20
#define MAX_CMDS 50
#define MAX_ERRORS 100
#define MAX_LINE_LENGTH 256

typedef struct {
    char name[33];
    char dependencies[MAX_DEPS][33];
    int dep_count;
    char commands[MAX_CMDS][256];
    int cmd_count;
    int line_number;
} Target;

typedef struct {
    int line;
    char message[256];
} Error;

#endif