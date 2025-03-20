CC = gcc
CFLAGS = -Wall -I.
TARGET1 = main1A
TARGET2 = main1B
SRCS_MAIN1A = main1A.c arg.c
SRCS_MAIN1B = main1B.c preprocess.c
OBJS_MAIN1A = $(SRCS_MAIN1A:.c=.o)
OBJS_MAIN1B = $(SRCS_MAIN1B:.c=.o)
HEADERS = arg.h preprocess.h
all $(TARGET1) $(TARGET2)
$(TARGET1): $(OBJS_MAIN1A)
	$(CC) $(CFLAGS) -o $@ $^
$(TARGET2): $(OBJS_MAIN1B)
	$(CC) $(CFLAGS) -o $@ $^
main1A.o: main1A.c arg.h
arg.o: arg.c arg.h
main1B.o: main1B.c preprocess.h
preprocess.o: preprocess.c preprocess.h
%.o: %.c
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f $(TARGET1) $(TARGET2) *.o
