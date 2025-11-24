CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c99 -g

SRCS = linkedList.c # actions.c
OBJS = $(SRCS:.c=.o)

MAIN_PROG = program
MAIN_SRCS = main.c $(SRCS)
MAIN_OBJS = main.o $(OBJS)

TEST_PROG = run_tests
TEST_SRCS = tests.c $(SRCS)
TEST_OBJS = tests.o $(OBJS)

.PHONY: all clean test $(MAIN_PROG) $(TEST_PROG)

all: $(MAIN_PROG)

internal_tests: $(TEST_PROG)
	@echo "--- Running Unit Tests ---"
	./$(TEST_PROG)


$(MAIN_PROG): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

$(TEST_PROG): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "--- Cleaning up build files ---"
	-rm -f $(MAIN_PROG) $(TEST_PROG) $(MAIN_OBJS) $(TEST_OBJS)
