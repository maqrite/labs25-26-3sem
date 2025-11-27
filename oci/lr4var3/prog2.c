#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef float (*sin_integral_func)(float, float, float);
typedef int (*gcd_func)(int, int);

int main(void) {
  char buffer[128];
  char out_buffer[128];
  int bytes_read;

  const char *lib_paths[] = {"./libimpl1.so", "./libimpl2.so"};
  int current_lib = 0;

  void *handle = NULL;
  sin_integral_func sin_integral = NULL;
  gcd_func gcd = NULL;

  handle = dlopen(lib_paths[current_lib], RTLD_LAZY);
  if (!handle) {
    int len = snprintf(out_buffer, sizeof(out_buffer),
                       "ошибка загрузки библиотеки: %s\n", dlerror());
    write(STDOUT_FILENO, out_buffer, len);
    return 1;
  }

  sin_integral = (sin_integral_func)dlsym(handle, "sin_integral");
  gcd = (gcd_func)dlsym(handle, "gcd");

  if (!sin_integral || !gcd) {
    int len =
        snprintf(out_buffer, sizeof(out_buffer), "ошибка загрузки символов\n");
    write(STDOUT_FILENO, out_buffer, len);
    return 1;
  }

  int len =
      snprintf(out_buffer, sizeof(out_buffer),
               "Программа 2 (дин библиотеки): %s", lib_paths[current_lib]);
  write(STDOUT_FILENO, out_buffer, len);

  while ((bytes_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0) {
    buffer[bytes_read] = '\0';
    int cmd;

    if (sscanf(buffer, "%d", &cmd) != 1) {
      continue;
    }

    if (cmd == 0) {
      dlclose(handle);
      current_lib = 1 - current_lib;

      handle = dlopen(lib_paths[current_lib], RTLD_LAZY);
      if (!handle) {
        len = snprintf(out_buffer, sizeof(out_buffer),
                       "ошибка смены библиотеки\n");
        write(STDOUT_FILENO, out_buffer, len);
        return 1;
      }

      sin_integral = (sin_integral_func)dlsym(handle, "sin_integral");
      gcd = (gcd_func)dlsym(handle, "gcd");

      len = snprintf(out_buffer, sizeof(out_buffer), "изменено на: %s\n",
                     lib_paths[current_lib]);
      write(STDOUT_FILENO, out_buffer, len);
    } else if (cmd == 1) {
      float a, b, e;

      if (sscanf(buffer, "%*d %f %f %f", &a, &b, &e) == 3) {
        float res = sin_integral(a, b, e);
        len = snprintf(out_buffer, sizeof(out_buffer),
                       "результат интеграла: %f\n", res);
        write(STDOUT_FILENO, out_buffer, len);
      }
    } else if (cmd == 2) {
      int a, b;

      if (sscanf(buffer, "%*d %d %d", &a, &b) == 2) {
        int res = gcd(a, b);
        len = snprintf(out_buffer, sizeof(buffer), "результат НОД: %d\n", res);
        write(STDOUT_FILENO, out_buffer, len);
      }
    }
  }

  if (handle) {
    dlclose(handle);
  }

  return 0;
}
