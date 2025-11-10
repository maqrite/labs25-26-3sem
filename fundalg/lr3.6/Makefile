CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g

SRCS = stack.c actions.c
OBJS = $(SRCS:.c=.o)

MAIN_PROG = programm

MAIN_SRCS = main.c $(SRCS)
MAIN_OBJS = main.o $(OBJS)

TEST_PROG = run_tests
TEST_SRCS = tests.c $(SRCS)
TEST_OBJS = tests.o $(OBJS)

.PHONY: all clean test_internal test_functional

all: $(MAIN_PROG)

$(MAIN_PROG): $(MAIN_OBJS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_OBJS)

$(TEST_PROG): $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

internal_tests: $(TEST_PROG)
	@echo "--- Running Internal Unit Tests ---"
	./$(TEST_PROG)
	@echo "-----------------------------------"


test: $(MAIN_PROG)
	@echo "--- Running External Functional Tests ---"
	
	@echo -n "Test 1 '()': "
	@echo "()" | ./$(MAIN_PROG) | grep "OK"
	
	@echo -n "Test 2 '()[]{}<>': "
	@echo "()[]{}<>" | ./$(MAIN_PROG) | grep "OK"
	
	@echo -n "Test 3 'int main() { }': "
	@echo "int main() { }" | ./$(MAIN_PROG) | grep "OK"
	
	@echo -n "Test 4 '(': "
	@echo "(" | ./$(MAIN_PROG) | grep "Error"
	
	@echo -n "Test 5 ')': "
	@echo ")" | ./$(MAIN_PROG) | grep "Error"
	
	@echo -n "Test 6 '([)]': "
	@echo "([)]" | ./$(MAIN_PROG) | grep "Error"
	
	@echo -n "Test 7 '(]': "
	@echo "(]" | ./$(MAIN_PROG) | grep "Error"

	@echo "---------------------------------------"

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(MAIN_PROG) $(TEST_PROG) *.o
