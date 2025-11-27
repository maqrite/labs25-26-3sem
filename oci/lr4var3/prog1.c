#include "contracts.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
  char buffer[128];
  char out_buffer[128];
  int bytes_read;

  int len = snprintf(out_buffer, sizeof(out_buffer),
                     "программа 1 (статическая). Введите команду:\n");
  write(STDERR_FILENO, out_buffer, len);

  while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[bytes_read] = '\0';

    int cmd;

    if (sscanf(buffer, "%d", &cmd) != 1) {
      continue;
    }

    if (cmd == 1) {
      float a, b, e;

      if (sscanf(buffer, "%*d %f %f %f", &a, &b, &e) == 3) {
        float res = sin_integral(a, b, e);
        len = snprintf(out_buffer, sizeof(out_buffer),
                       "результат (интеграла): %f\n", res);
        write(STDOUT_FILENO, out_buffer, len);
      } else {
        len = snprintf(out_buffer, sizeof(out_buffer), "некорректный ввод\n");
        write(STDOUT_FILENO, out_buffer, len);
      }
    } else if (cmd == 2) {
      int a, b;

      if (sscanf(buffer, "%*d %d %d", &a, &b) == 2) {
        int res = gcd(a, b);
        len = snprintf(out_buffer, sizeof(out_buffer), "рузультат НОД: %d\n",
                       res);
        write(STDOUT_FILENO, out_buffer, len);
      }

    } else if (cmd == 0) {
      len = snprintf(out_buffer, sizeof(out_buffer),
                     "смена не поддерживается при статической линковке\n");
      write(STDOUT_FILENO, out_buffer, len);
    }
  }

  return 0;
}
