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
	-@./$(TARGET) > actual.tmp 2>&1
	@echo "Недопустимое количество аргументов" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] No arguments" || echo "[FAIL] No arguments"

	-@./$(TARGET) --const pi --method s > actual.tmp 2>&1
	@echo "Ошибка передачи флага" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Missing --eps flag" || echo "[FAIL] Missing --eps flag"

	-@./$(TARGET) --const pi --method s --eps -0.1 > actual.tmp 2>&1
	@echo "Эпсилон должен быть положительным" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Negative epsilon" || echo "[FAIL] Negative epsilon"

	-@./$(TARGET) --const pi --method x --eps 0.01 > actual.tmp 2>&1
	@echo "Ошибка вычисления" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Unknown method" || echo "[FAIL] Unknown method"

	-@./$(TARGET) --const unknown --method s --eps 0.01 > actual.tmp 2>&1
	@grep -q "Неизвестная комбинация константы" actual.tmp && echo "[PASS] Unknown constant" || echo "[FAIL] Unknown constant"

test_functionality:
	@echo "\n--> Testing Functionality..."
	@./$(TARGET) --const pi --method s --eps 0.01 > actual.tmp
	@grep -q "Результат:" actual.tmp && echo "[PASS] pi series" || echo "[FAIL] pi series"

	@./$(TARGET) --const exp --method l --eps 0.01 > actual.tmp
	@grep -q "Результат:" actual.tmp && echo "[PASS] exp limit" || echo "[FAIL] exp limit"

	@./$(TARGET) --method e --const ln2 --eps 0.001 > actual.tmp
	@grep -q "Результат:" actual.tmp && echo "[PASS] ln2 equation (reordered flags)" || echo "[FAIL] ln2 equation (reordered flags)"

	@./$(TARGET) --const sqrt2 --method s --eps 0.01 > actual.tmp
	@grep -q "Результат:" actual.tmp && echo "[PASS] sqrt2 series" || echo "[FAIL] sqrt2 series"

	@./$(TARGET) --const gamma --method l --eps 0.01 > actual.tmp
	@grep -q "Результат:" actual.tmp && echo "[PASS] gamma limit" || echo "[FAIL] gamma limit"


.PHONY: all clean test internal_tests test_errors test_functionality
