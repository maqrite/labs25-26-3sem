CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGET = app
SOURCES = main.c actions.c
TEST_RUNNER = run_tests
TEST_SOURCES = tests.c actions.c

all: $(TARGET)

$(TARGET): $(SOURCES) actions.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

internal_tests: $(TEST_RUNNER)
	@echo "--- Running Internal (assert) Tests ---"
	./$(TEST_RUNNER)
	@echo "---------------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) actions.h
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES)

clean:
	rm -f $(TARGET) $(TEST_RUNNER) input.txt output.txt expected.txt actual_stderr.txt expected_stderr.txt


test: all
	@echo "--- Running External (Makefile) Tests ---"
	@$(MAKE) test_errors
	@$(MAKE) test_functionality
	@$(MAKE) clean
	@echo "--- All external tests finished ---"

test_errors:
	@echo "\n--> Testing Error Handling..."
	-@./$(TARGET) > actual.tmp 2>/dev/null; if [ $$? -eq 3 ]; then echo "[PASS] Incorrect number of arguments (too few)"; else echo "[FAIL] Incorrect number of arguments (too few)"; fi
	-@./$(TARGET) 1 2 3 > actual.tmp 2>/dev/null; if [ $$? -eq 3 ]; then echo "[PASS] Incorrect number of arguments (too many)"; else echo "[FAIL] Incorrect number of arguments (too many)"; fi
	-@./$(TARGET) non_existent.txt out.txt > actual.tmp 2>/dev/null; if [ $$? -eq 1 ]; then echo "[PASS] Input file not found"; else echo "[FAIL] Input file not found"; fi

test_functionality:
	@echo "\n--> Testing Functionality..."

	@printf "101 Ff\n\n  007\tz" > input.txt
	@printf "101 2 5\nFf 16 255\n7 8 7\nz 36 35\n" > expected.txt
	@./$(TARGET) input.txt output.txt
	@diff -w output.txt expected.txt && echo "[PASS] Simple case with mixed separators/case" || echo "[FAIL] Simple case with mixed separators/case"

	@printf "good1 bad! good2" > input.txt
	@printf "good1 25 6640326\ngood2 25 6640327\n" > expected.txt
	@printf "Неудалось обработать строку /bad!/\n" > expected_stderr.txt
	@./$(TARGET) input.txt output.txt 2> actual_stderr.txt
	@diff -w output.txt expected.txt && diff -w actual_stderr.txt expected_stderr.txt && echo "[PASS] File with invalid strings" || echo "[FAIL] File with invalid strings"


.PHONY: all clean test internal_tests test_errors test_functionality
