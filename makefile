# 编译器配置
CC = gcc
CFLAGS = -Wall -I.

# 定义两个独立程序
TARGET1 = main1_1    # 对应 1.1 arg 模块
TARGET2 = main1_2    # 对应 1.2 preprocess 模块

# 手动指定各模块的源文件
SRCS_MAIN1_1 = main1_1.c arg.c        # main1_1 依赖的源文件
SRCS_MAIN1_2 = main1_2.c preprocess.c # main1_2 依赖的源文件

# 自动生成对象文件列表
OBJS_MAIN1_1 = $(SRCS_MAIN1_1:.c=.o)
OBJS_MAIN1_2 = $(SRCS_MAIN1_2:.c=.o)

# 头文件列表
HEADERS = arg.h preprocess.h

# 默认编译全部目标
all: $(TARGET1) $(TARGET2)

# 编译 main1_1
$(TARGET1): $(OBJS_MAIN1_1)
	$(CC) $(CFLAGS) -o $@ $^

# 编译 main1_2
$(TARGET2): $(OBJS_MAIN1_2)
	$(CC) $(CFLAGS) -o $@ $^

# 模块依赖规则
main1_1.o: main1_1.c arg.h
arg.o: arg.c arg.h
main1_2.o: main1_2.c preprocess.h
preprocess.o: preprocess.c preprocess.h

# 通用编译规则
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# 清理所有生成文件
clean:
	rm -f $(TARGET1) $(TARGET2) *.o