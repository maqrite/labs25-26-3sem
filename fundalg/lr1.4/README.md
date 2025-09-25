флаги: 
--const <exp/pi/ln2/sqrt2/gamma>

--method <s, e, l>  

s - series / e - equation / l - limit

--eps <0.0001>

для внешних тестов "make test"

для внутренних тестов "make internal_tests"

для компиляции "gcc -Wall -Werror -Wextra -Wpedantic -fsanitize=address main.c actions.c -o program -lm"

для запуска ./program --const exp --method s --eps 0.001
