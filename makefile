# 编译器配置
CC = gcc
CFLAGS = -Wall -I.

# 定义两个独立程序
TARGET1 = main1A    # 对应 1.1 arg 模块
TARGET2 = main1B    # 对应 1.2 preprocess 模块

# 手动指定各模块的源文件
SRCS_MAIN1A = main1A.c arg.c        # main1_1 依赖的源文件
SRCS_MAIN1B = main1B.c preprocess.c # main1_2 依赖的源文件

# 自动生成对象文件列表
OBJS_MAIN1A = $(SRCS_MAIN1A:.c=.o)
OBJS_MAIN1B = $(SRCS_MAIN1B:.c=.o)

# 头文件列表
HEADERS = arg.h preprocess.h

# 默认编译全部目标
all: $(TARGET1) $(TARGET2)

# 编译 main1A
$(TARGET1): $(OBJS_MAIN1A)
	$(CC) $(CFLAGS) -o $@ $^

# 编译 main1B
$(TARGET2): $(OBJS_MAIN1B)
	$(CC) $(CFLAGS) -o $@ $^

# 模块依赖规则
main1A.o: main1A.c arg.h
arg.o: arg.c arg.h
main1B.o: main1B.c preprocess.h
preprocess.o: preprocess.c preprocess.h

# 通用编译规则
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# 清理所有生成文件
clean:
	rm -f $(TARGET1) $(TARGET2) *.o