CC = gcc

CFLAGS = -std=c99 -Wall -Wextra -Werror

TARGET = program
SOURCES = main.c actions.c
TEST_RUNNER = test_runner
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
	rm -f $(TARGET) $(TEST_RUNNER) output.txt expected.txt

test: all
	@echo "--- Running External (Makefile) Tests ---"
	@$(MAKE) test_errors
	@$(MAKE) test_functionality
	@$(MAKE) clean
	@echo "--- All external tests finished ---"

test_errors:
	@echo "\n--> Testing Error Handling..."
	-@printf "hello\n2\n" | ./$(TARGET) >/dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] Bad number input (hello)"; else echo "[FAIL] Bad number input (hello)"; fi
	-@printf "10\nhello\n" | ./$(TARGET) >/dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] Bad 'r' input"; else echo "[FAIL] Bad 'r' input"; fi

test_functionality:
	@echo "\n--> Testing Functionality..."
	
	@printf "10\n4\n" | ./$(TARGET) > output.txt
	@printf "Введите десятичное число: Введите степень r (1-5) для 2^r: число 10 (основание 10)\nчисло A (основание 2^4 = 16)\n" > expected.txt
	@diff -w output.txt expected.txt && echo "[PASS] 10 (base 10) -> A (base 16)" || echo "[FAIL] 10 (base 10) -> A (base 16)"

	@printf "0\n2\n" | ./$(TARGET) > output.txt
	@printf "Введите десятичное число: Введите степень r (1-5) для 2^r: число 0 (основание 10)\nчисло 0 (основание 2^2 = 4)\n" > expected.txt
	@diff -w output.txt expected.txt && echo "[PASS] 0 (base 10) -> 0 (base 4)" || echo "[FAIL] 0 (base 10) -> 0 (base 4)"

	@printf "31\n5\n" | ./$(TARGET) > output.txt
	@printf "Введите десятичное число: Введите степень r (1-5) для 2^r: число 31 (основание 10)\nчисло V (основание 2^5 = 32)\n" > expected.txt
	@diff -w output.txt expected.txt && echo "[PASS] 31 (base 10) -> V (base 32)" || echo "[FAIL] 31 (base 10) -> V (base 32)"

	@printf -- "-10\n4\n" | ./$(TARGET) > output.txt
	@printf "Введите десятичное число: Введите степень r (1-5) для 2^r: число -10 (основание 10)\nчисло FFFFFFF6 (основание 2^4 = 16)\n" > expected.txt
	@diff -w output.txt expected.txt && echo "[PASS] -10 (base 10) -> FFFFFFFF6 (base 16)" || echo "[FAIL] -10 (base 10) -> FFFFFFFF6 (base 16)"

.PHONY: all clean test internal_tests test_errors test_functionality
