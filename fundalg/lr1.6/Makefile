CC = gcc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lm
TARGET = app
SOURCES = main.c actions.c
TEST_RUNNER = run_tests
TEST_SOURCES = tests.c actions.c

all: $(TARGET)

$(TARGET): $(SOURCES) actions.h
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) $(LDFLAGS)

internal_tests: $(TEST_RUNNER)
	@echo "--- Running Internal (assert) Tests ---"
	./$(TEST_RUNNER)
	@echo "---------------------------------------"

$(TEST_RUNNER): $(TEST_SOURCES) actions.h
	$(CC) $(CFLAGS) -o $(TEST_RUNNER) $(TEST_SOURCES) $(LDFLAGS)

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
	-@./$(TARGET) -e > actual.tmp
	@echo "Ошибка в парсинге эпсилон" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Missing epsilon value" || echo "[FAIL] Missing epsilon value"

	-@./$(TARGET) -e -0.5 -a > actual.tmp
	@echo "Ошибка в парсинге эпсилон" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Negative epsilon" || echo "[FAIL] Negative epsilon"

	-@./$(TARGET) -x -e 0.01 > actual.tmp
	@echo "Некорректный или неизвестный флаг" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Unknown flag" || echo "[FAIL] Unknown flag"

	-@./$(TARGET) -a -b -e 0.01 > actual.tmp
	@echo "ошибка при выборе опции или при ее парсинге" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Multiple option flags" || echo "[FAIL] Multiple option flags"

test_functionality:
	@echo "\n--> Testing Functionality..."

	@./$(TARGET) -e 0.0001 -a | grep -qE '^[0-9]+\.[0-9]{12}$$' && echo "[PASS] Flag -a runs successfully" || echo "[FAIL] Flag -a runs successfully"

	@./$(TARGET) -b -e 0.0001 | grep -qE '^[0-9]+\.[0-9]{12}$$' && echo "[PASS] Flag -b runs successfully" || echo "[FAIL] Flag -b runs successfully"

	@./$(TARGET) -e 0.0001 -c | grep -qE '^[0-9]+\.[0-9]{12}$$' && echo "[PASS] Flag -c runs successfully" || echo "[FAIL] Flag -c runs successfully"

	@./$(TARGET) -e 0.0001 -d | grep -qE '^[0-9]+\.[0-9]{12}$$' && echo "[PASS] Flag -d runs successfully" || echo "[FAIL] Flag -d runs successfully"


.PHONY: all clean test internal_tests test_errors test_functionality
