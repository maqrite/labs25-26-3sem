# Компилятор C
CC = gcc

CFLAGS = -std=c99 -Wall -Wextra -g -O2
LDFLAGS = -lm


SRCS = main.c actions.c student.c studentVector.c fileIo.c validation.c

OBJS = $(SRCS:.c=.o)


TARGET = lab


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
