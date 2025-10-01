#!/bin/bash

# Цвета для вывода
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# --- ШАГ 1: Компиляция программы ---
echo "Building the project..."
make clean > /dev/null 2>&1
if ! make; then
    echo -e "${RED}ERROR: Compilation failed.${NC}"
    exit 1
fi
echo -e "${GREEN}Build successful.${NC}"
echo "-------------------------------------"

# --- ОБЯЗАТЕЛЬНЫЙ ШАГ: Определение директории для тестов ---
TEST_DIR="test_data"
# Удаляем старую директорию, если она есть, и создаем новую
rm -rf "$TEST_DIR"
mkdir -p "$TEST_DIR"


# --- ШАГ 2: Определение и создание тестовых случаев ---

# Функция для создания тестового файла
create_test_file() {
    # $1: имя файла, $2: содержимое
    echo -e "$2" > "$TEST_DIR/$1"
}

# 1. Базовый тест
create_test_file "basic.txt" "10 20\n5 3\n100 1"
create_test_file "basic.expected" "30\n8\n101"

# 2. Тест с отрицательными числами
create_test_file "negative.txt" "-10 5\n-5 -5"
create_test_file "negative.expected" "-5\n-10"

# 3. Тест с нулями
create_test_file "zeros.txt" "0 0\n10 0\n-5 0"
create_test_file "zeros.expected" "0\n10\n-5"

# 4. Тест с пустым файлом
touch "$TEST_DIR/empty.txt"
touch "$TEST_DIR/empty.expected"

# 5. Тест с одной строкой
create_test_file "single_line.txt" "99 1"
create_test_file "single_line.expected" "100"

# 6. Тест на граничный случай: файл без новой строки в конце
create_test_file "no_newline.txt" "1 1\n2 2"
create_test_file "no_newline.expected" "2\n4"


# --- ШАГ 3: Запуск тестов ---
TOTAL_TESTS=0
PASSED_TESTS=0

# Функция для запуска одного теста
run_test() {
    local test_name="$1"
    local input_file="$TEST_DIR/$2"
    local expected_file="$TEST_DIR/${2%.txt}.expected"
    local result_file="$TEST_DIR/${2%.txt}.result"

    ((TOTAL_TESTS++))
    echo -n "Running test: '$test_name'... "

    # Запускаем программу, передаем ей имя файла, результат сохраняем
    echo "$input_file" | ./parent > "$result_file" 2>/dev/null # Игнорируем stderr для чистоты вывода

    # Сравниваем результат с ожидаемым
    if diff -q "$result_file" "$expected_file" >/dev/null 2>&1; then
        echo -e "${GREEN}PASS${NC}"
        ((PASSED_TESTS++))
    else
        echo -e "${RED}FAIL${NC}"
        echo "--------- Expected ---------"
        cat "$expected_file"
        echo "---------- Actual ----------"
        cat "$result_file"
        echo "--------------------------"
    fi
}

# Запуск тестов на корректность вычислений
run_test "Basic functionality" "basic.txt"
run_test "Negative numbers" "negative.txt"
run_test "Zero values" "zeros.txt"
run_test "Empty input file" "empty.txt"
run_test "Single line input" "single_line.txt"
run_test "File without trailing newline" "no_newline.txt"


# --- Тесты на обработку ошибок ---
((TOTAL_TESTS++))
echo -n "Running test: 'Non-existent file'... "
echo "non_existent_file.txt" | ./parent 2> "$TEST_DIR/error.result" &
sleep 0.1 && kill $! > /dev/null 2>&1
wait $! 2>/dev/null

if grep -q "Failed to open file" "$TEST_DIR/error.result"; then
    echo -e "${GREEN}PASS${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}FAIL${NC}"
fi


# --- ШАГ 4: Вывод итогов и очистка ---
echo "-------------------------------------"
echo "Test summary: $PASSED_TESTS / $TOTAL_TESTS passed."
echo "-------------------------------------"

rm -rf "$TEST_DIR"

if [ "$PASSED_TESTS" -ne "$TOTAL_TESTS" ]; then
    exit 1
fi

exit 0
