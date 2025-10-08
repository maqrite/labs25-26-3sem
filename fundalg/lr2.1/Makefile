CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address -lm
TARGET = app
SOURCES = main.c actions.c
TEST_RUNNER = run_tests
TEST_SOURCES = tests.c actions.c

all: $(TARGET)

$(TARGET): $(SOURCES) actions.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: $(TEST_RUNNER)
	@echo "--- Running Internal (assert) Tests ---"
	./$(TEST_RUNNER)
	@echo "---------------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) actions.h
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_RUNNER) actual.tmp expected.tmp


.PHONY: all clean test internal_tests
