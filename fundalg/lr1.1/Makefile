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
	rm -f $(TARGET) $(TEST_RUNNER) *.tmp


test: all
	@echo "--- Running External (Makefile) Tests ---"
	@$(MAKE) test_errors
	@$(MAKE) test_functionality
	@rm -f *.tmp
	@echo "--- All external tests finished ---"

test_errors: all
	@echo "\n--> Testing Error Handling..."
	@./$(TARGET) > /dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] INVALID_NUMBER_OF_ARGS: No arguments"; else echo "[FAIL] No arguments"; fi
	@./$(TARGET) 10 -a 20 > /dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] INVALID_NUMBER_OF_ARGS: Too many arguments"; else echo "[FAIL] Too many arguments"; fi
	@./$(TARGET) 10 -x > /dev/null 2>&1; if [ $$? -eq 2 ]; then echo "[PASS] UNKNOWN_FLAG"; else echo "[FAIL] UNKNOWN_FLAG"; fi
	@./$(TARGET) "abc" -a > /dev/null 2>&1; if [ $$? -eq 3 ]; then echo "[PASS] INCORRECT_NUMBER"; else echo "[FAIL] INCORRECT_NUMBER"; fi
	@./$(TARGET) 11 -e > /dev/null 2>&1; if [ $$? -eq 4 ]; then echo "[PASS] INCORRECT_NUMBER_FOR_FLAG (-e > 10)"; else echo "[FAIL] INCORRECT_NUMBER_FOR_FLAG (-e > 10)"; fi
	@./$(TARGET) 21 -f > /dev/null 2>&1; if [ $$? -eq 4 ]; then echo "[PASS] INCORRECT_NUMBER_FOR_FLAG (-f > 20)"; else echo "[FAIL] INCORRECT_NUMBER_FOR_FLAG (-f > 20)"; fi

test_functionality: all
	@echo "\n--> Testing Functionality..."
	@echo "Сумма равна: 55" > expected.tmp
	@./$(TARGET) 10 -a > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Sum (-a)" || echo "[FAIL] Sum (-a)"
	@echo "Число 7 является простым" > expected.tmp
	@./$(TARGET) 7 -p > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] IsPrime (-p, prime)" || echo "[FAIL] IsPrime (-p, prime)"
	@echo "Число 8 является составным" > expected.tmp
	@./$(TARGET) 8 -p > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] IsPrime (-p, composite)" || echo "[FAIL] IsPrime (-p, composite)"
	@echo "20\t40\t60\t80\t100\t" > expected.tmp
	@./$(TARGET) 20 -h > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Multiples (-h)" || echo "[FAIL] Multiples (-h)"
	@echo "Кратных натуральных чисел в пределах 100 нет" > expected.tmp
	@./$(TARGET) 101 -h > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] No Multiples (-h)" || echo "[FAIL] No Multiples (-h)"
	@printf "F F " > expected.tmp
	@./$(TARGET) 255 -s > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Hex Digits (-s)" || echo "[FAIL] Hex Digits (-s)"
	@echo "5! = 120" > expected.tmp
	@./$(TARGET) 5 -f > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Factorial (-f)" || echo "[FAIL] Factorial (-f)"
	@echo "Сумма равна: 55" > expected.tmp
	@./$(TARGET) 10 /a > actual.tmp
	@diff -w actual.tmp expected.tmp && echo "[PASS] Slash as flag prefix (/a)" || echo "[FAIL] Slash as flag prefix (/a)"
.PHONY: all clean test internal_tests test_errors test_functionality
