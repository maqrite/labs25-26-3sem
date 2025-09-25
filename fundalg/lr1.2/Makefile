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
	rm -f $(TARGET) $(TEST_RUNNER) actual.tmp expected.tmp

test: all
	@echo "--- Running External (Makefile) Tests ---"
	@$(MAKE) test_errors
	@$(MAKE) test_functionality
	@rm -f actual.tmp expected.tmp
	@echo "--- All external tests finished ---"

test_errors:
	@echo "\n--> Testing Error Handling..."
	@printf "Недопустимое количество строк или введено не число\n" > expected.tmp
	-@printf "abc\n" | ./$(TARGET) > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Bad T (not a number)" || echo "[FAIL] Bad T (not a number)"
	@printf "2\n5\n-3\n" | ./$(TARGET) > actual.tmp
	@printf "11\nНедопустимое число в строке или введено не число\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Negative n" || echo "[FAIL] Negative n"
	@printf "2\n10\nxyz\n" | ./$(TARGET) > actual.tmp
	@printf "29\nНедопустимое число в строке или введено не число\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Bad n (not a number)" || echo "[FAIL] Bad n (not a number)"

test_functionality:
	@echo "\n--> Testing Functionality..."
	@printf "1\n10\n" | ./$(TARGET) > actual.tmp
	@printf "29\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Single valid request" || echo "[FAIL] Single valid request"
	@printf "3\n1\n2\n3\n" | ./$(TARGET) > actual.tmp
	@printf "2\n3\n5\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Multiple valid requests" || echo "[FAIL] Multiple valid requests"
	@printf "1\n100\n" | ./$(TARGET) > actual.tmp
	@printf "541\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Larger n (100th prime)" || echo "[FAIL] Larger n (100th prime)"
	@printf "4\n5\nabc\n10\n-1\n" | ./$(TARGET) > actual.tmp
	@printf "11\nНедопустимое число в строке или введено не число\n29\nНедопустимое число в строке или введено не число\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Mixed valid and invalid requests" || echo "[FAIL] Mixed valid and invalid requests"

.PHONY: all clean test internal_tests test_errors test_functionality
