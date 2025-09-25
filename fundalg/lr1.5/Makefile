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
	rm -f $(TARGET) $(TEST_RUNNER) input.txt out_input.txt custom_out.txt expected.txt

test: all
	@echo "--- Running External (Makefile) Tests ---"
	@printf "line with digits 123\nHello World!\nSpecial chars: !@#\n" > input.txt

	@$(MAKE) test_errors
	@$(MAKE) test_functionality

	@$(MAKE) clean
	@echo "--- All external tests finished ---"

test_errors:
	@echo "\n--> Testing Error Handling..."
	-@./$(TARGET) >/dev/null 2>&1; if [ $$? -eq 1 ]; then echo "[PASS] No arguments"; else echo "[FAIL] No arguments"; fi
	-@./$(TARGET) -x input.txt >/dev/null 2>&1; if [ $$? -eq 2 ]; then echo "[PASS] Unknown flag"; else echo "[FAIL] Unknown flag"; fi
	-@./$(TARGET) -d non_existent_file.txt >/dev/null 2>&1; if [ $$? -eq 4 ]; then echo "[PASS] Input file not found"; else echo "[FAIL] Input file not found"; fi

test_functionality:
	@echo "\n--> Testing Functionality..."
	@./$(TARGET) -d input.txt
	@printf "line with digits \nHello World!\nSpecial chars: !@#\n" > expected.txt
	@diff -w out_input.txt expected.txt && echo "[PASS] -d flag (auto filename)" || echo "[FAIL] -d flag (auto filename)"

	@./$(TARGET) /ni input.txt custom_out.txt
	@printf "14\n10\n12\n" > expected.txt
	@diff -w custom_out.txt expected.txt && echo "[PASS] /ni flag (custom filename)" || echo "[FAIL] /ni flag (custom filename)"

	@./$(TARGET) -s input.txt
	@printf "0\n1\n4\n" > expected.txt
	@diff -w out_input.txt expected.txt && echo "[PASS] -s flag (auto filename)" || echo "[FAIL] -s flag (auto filename)"

	@./$(TARGET) /na input.txt custom_out.txt
	@printf "6C696E6520776974682064696769747320123\n48656C6C6F20576F726C6421\n5370656369616C2063686172733A20214023\n" > expected.txt
	@diff -w custom_out.txt expected.txt && echo "[PASS] /na flag (custom filename)" || echo "[FAIL] /na flag (custom filename)"


.PHONY: all clean test internal_tests test_errors test_functionality
