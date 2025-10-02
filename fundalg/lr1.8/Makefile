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
	-@./$(TARGET) some_arg >/dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] Invalid CLI arguments"; else echo "[FAIL] Invalid CLI arguments"; fi
	-@printf "abc\n" | ./$(TARGET) > actual.tmp 2>/dev/null; if [ $$? -eq 2 ]; then echo "[PASS] Invalid base (not a number)"; else echo "[FAIL] Invalid base (not a number)"; fi
	-@printf "37\n" | ./$(TARGET) > actual.tmp 2>/dev/null; if [ $$? -eq 3 ]; then echo "[PASS] Invalid base (out of range)"; else echo "[FAIL] Invalid base (out of range)"; fi

test_functionality:
	@echo "\n--> Testing Functionality..."

	@printf "10\n10\n-5\n20\nstop\n" | ./$(TARGET) > actual.tmp
	@printf "Введите основание системы счисления в диапазоне [2, 36]:\tВведите числа в системе счисления 10. Для завершения введите stop\nМаксимальное число по модулю: 20\nB 9 c/c: 22\nB 18 c/c: 12\nB 27 c/c: K\nB 36 c/c: K\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Positive max number" || echo "[FAIL] Positive max number"

	@printf "16\nA\n1F\n-20\nstop\n" | ./$(TARGET) > actual.tmp
	@printf "Введите основание системы счисления в диапазоне [2, 36]:\tВведите числа в системе счисления 16. Для завершения введите stop\nМаксимальное число по модулю: -20\nB 9 c/c: -35\nB 18 c/c: -1E\nB 27 c/c: -15\nB 36 c/c: -W\n" > expected.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Negative max number" || echo "[FAIL] Negative max number"

	@printf "10\nstop\n" | ./$(TARGET) > actual.tmp
	@grep -q "Не было передано ни одного корректного числа" actual.tmp && echo "[PASS] No valid numbers entered" || echo "[FAIL] No valid numbers entered"

	@printf "8\n10\nabc\n77\nstop\n" | ./$(TARGET) > actual.tmp
	@grep -q "Некорректный ввод /abc/" actual.tmp && grep -q "Максимальное число по модулю: 77" actual.tmp && echo "[PASS] Mixed valid/invalid input" || echo "[FAIL] Mixed valid/invalid input"

.PHONY: all clean test internal_tests test_errors test_functionality

VPS_USER = artem
VPS_HOST = 5.129.251.235
VPS_DEST_PATH = .

deploy:
	@echo "--> Отправка файлов на VPS: $(VPS_HOST)..."
	@scp -r * $(VPS_USER)@$(VPS_HOST):$(VPS_DEST_PATH)
	@echo "--> Файлы успешно отправлены."

.PHONY: deploy
