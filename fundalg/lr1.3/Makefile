CC = gcc
CFLAGS = -Wall -Wextra -Werror -lm
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
	@$(MAKE) test_general_errors
	@$(MAKE) test_flag_m
	@$(MAKE) test_flag_t
	@$(MAKE) test_flag_q
	@rm -f actual.tmp expected.tmp
	@echo "--- All external tests finished ---"

test_general_errors:
	@echo "\n--> Testing General Errors..."
	@./$(TARGET) > actual.tmp 2>/dev/null || true
	@echo "Недопустимое количество аргументов" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] No arguments" || echo "[FAIL] No arguments"
	@./$(TARGET) -x 1 2 3 > actual.tmp 2>/dev/null || true
	@echo "Передан неизвестный флаг" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Unknown flag" || echo "[FAIL] Unknown flag"

test_flag_m:
	@echo "\n--> Testing Flag -m (Multiplicity)..."
	@./$(TARGET) -m 10 2 > actual.tmp
	@echo "Первое число кратно второму" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -m: Is multiple" || echo "[FAIL] -m: Is multiple"
	@./$(TARGET) /m 10 3 > actual.tmp
	@echo "Первое число не кратно второму" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -m: Is not multiple (with slash)" || echo "[FAIL] -m: Is not multiple (with slash)"
	@./$(TARGET) -m 10 > actual.tmp 2>/dev/null || true
	@echo "Недопустимое количество аргументов для флага" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -m: Too few arguments" || echo "[FAIL] -m: Too few arguments"
	@./$(TARGET) -m 10 abc > actual.tmp 2>/dev/null || true
	@echo "Неверный формат числового аргумента" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -m: Invalid argument" || echo "[FAIL] -m: Invalid argument"

test_flag_t:
	@echo "\n--> Testing Flag -t (Right Triangle)..."
	@./$(TARGET) -t 0.01 3 4 5 > actual.tmp
	@echo "Три числа могут являться длинами сторон прямоугольного треугольника" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -t: Is a right triangle" || echo "[FAIL] -t: Is a right triangle"
	@./$(TARGET) /t 0.01 3 4 6 > actual.tmp
	@echo "Три числа не могут являться длинами сторон прямоугольного треугольника" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -t: Not a right triangle (with slash)" || echo "[FAIL] -t: Not a right triangle (with slash)"
	@./$(TARGET) -t -0.5 3 4 5 > actual.tmp 2>/dev/null || true
	@echo "Эпсилон должен быть положительным" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -t: Negative epsilon" || echo "[FAIL] -t: Negative epsilon"

test_flag_q:
	@echo "\n--> Testing Flag -q (Quadratic Equation)..."
	@./$(TARGET) -q 0.001 1 1 1 > actual.tmp
	@echo "Действительных корней не найдено ни для одной перестановки" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -q: No real roots" || echo "[FAIL] -q: No real roots"
	@./$(TARGET) /q 0.001 1 0 -1 > actual.tmp
	@printf "Уникальные корни для всех перестановок:\n" > expected.tmp
	@printf "x1 = 1.000000\n" >> expected.tmp
	@printf "x2 = -1.000000\n" >> expected.tmp
	@printf "x3 = 0.000000\n" >> expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] -q: Known unique roots (with slash)" || echo "[FAIL] -q: Known unique roots (with slash)"

.PHONY: all clean test internal_tests test_general_errors test_flag_m test_flag_t test_flag_q
