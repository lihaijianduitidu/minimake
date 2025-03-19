CC = gcc
CFLAGS = -Wall
TARGET = main
SRCS = main.c arg.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^  

clean:
	rm -f $(TARGET)           