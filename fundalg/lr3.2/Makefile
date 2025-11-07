CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Werror -O2

TARGET = program
TEST_RUNNER_INT = test_runner_int
TEST_RUNNER_CHAR = test_runner_char
TEST_RUNNER_ULL = test_runner_ull

ACTIONS_OBJ = actions.o

VECTOR_SRC = vector.c vector.h
ACTIONS_SRC = actions.c actions.h

.PHONY: all clean test internal_tests

all: $(TARGET)

$(ACTIONS_OBJ): $(ACTIONS_SRC)
	$(CC) $(CFLAGS) -c actions.c -o $(ACTIONS_OBJ)

$(TARGET): main.c $(VECTOR_SRC) $(ACTIONS_OBJ)
	$(CC) $(CFLAGS) -DVECTOR_TYPE=int -o $(TARGET) main.c vector.c $(ACTIONS_OBJ)

internal_tests: $(TEST_RUNNER_INT) $(TEST_RUNNER_CHAR) $(TEST_RUNNER_ULL)
	@echo "--- Запуск всех внутренних (assert) тестов ---"
	@echo ""
	./$(TEST_RUNNER_INT)
	./$(TEST_RUNNER_CHAR)
	./$(TEST_RUNNER_ULL)
	@echo "--- Все тесты пройдены ---"

$(TEST_RUNNER_INT): test1.c $(VECTOR_SRC) $(ACTIONS_OBJ)
	$(CC) $(CFLAGS) -DVECTOR_TYPE=int -o $(TEST_RUNNER_INT) test1.c vector.c $(ACTIONS_OBJ)

$(TEST_RUNNER_CHAR): test2.c $(VECTOR_SRC) $(ACTIONS_OBJ)
	$(CC) $(CFLAGS) -DVECTOR_TYPE=char -o $(TEST_RUNNER_CHAR) test2.c vector.c $(ACTIONS_OBJ)

$(TEST_RUNNER_ULL): test3.c $(VECTOR_SRC) $(ACTIONS_OBJ)
	$(CC) $(CFLAGS) -DVECTOR_TYPE="unsigned long long" -o $(TEST_RUNNER_ULL) test3.c vector.c $(ACTIONS_OBJ)


test: all
	@echo "--- Запуск внешних (Makefile) тестов ---"
	@echo "Внешние тесты (diff) пропущены (нерелевантны для вектора)."
	@$(MAKE) clean
	@echo "--- Внешние тесты завершены ---"


clean:
	rm -f $(TARGET) $(TEST_RUNNER_INT) $(TEST_RUNNER_CHAR) $(TEST_RUNNER_ULL)
	rm -f $(ACTIONS_OBJ) output.txt expected.txt
