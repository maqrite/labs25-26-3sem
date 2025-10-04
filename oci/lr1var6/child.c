#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static int my_atoi(const char *str) {
  int result = 0;
  int sign = 1;
  int i = 0;
  if (str[0] == '-') {
    sign = -1;
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    result = result * 10 + (str[i] - '0');
    i++;
  }
  return result * sign;
}

static void process_line(char *line_buf) {
  int sum = 0;
  size_t i = 0;

  while (line_buf[i] != '\0') {
    while (line_buf[i] == ' ') {
      i++;
    }
    if (line_buf[i] == '\0') {
      break;
    }

    char num_str[21];
    size_t j = 0;
    while (line_buf[i] != ' ' && line_buf[i] != '\0') {
      if (j < sizeof(num_str) - 1) {
        num_str[j++] = line_buf[i];
      }
      i++;
    }
    num_str[j] = '\0';

    if (j > 0) {
      sum += my_atoi(num_str);
    }
  }

  char result_buf[32];
  int len = snprintf(result_buf, sizeof(result_buf), "%d\n", sum);
  write(STDOUT_FILENO, result_buf, len);
}
int main(void) {
  char line_buf[128];
  size_t line_pos = 0;
  char current_char;

  while (read(STDIN_FILENO, &current_char, 1) > 0) {
    if (current_char != '\n') {
      if (line_pos < sizeof(line_buf) - 1) {
        line_buf[line_pos++] = current_char;
      }
    } else {
      if (line_pos > 0) {
        line_buf[line_pos] = '\0';
        process_line(line_buf);
      }
      line_pos = 0;
    }
  }

  if (line_pos > 0) {
    line_buf[line_pos] = '\0';
    process_line(line_buf);
  }

  return 0;
}
