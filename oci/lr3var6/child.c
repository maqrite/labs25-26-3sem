#include <fcntl.h>
#include <semaphore.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 4096
#define EOF_SIGNAL "EOF_SIGNAL"

void report_error_and_exit(const char *msg) {
  int i = 0;
  while (msg[i]) {
    i++;
  }

  write(STDERR_FILENO, msg, i);
  write(STDERR_FILENO, "\n", 1);
  _exit(1);
}

int my_atoi(const char *str) {
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

void process_line(char *line_buf, void *shm_ptr, sem_t *sem_full,
                  sem_t *sem_empty) {
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
  (void)snprintf(result_buf, sizeof(result_buf), "%d\n", sum);

  sem_wait(sem_empty);

  strcpy((char *)shm_ptr, result_buf);

  sem_post(sem_full);
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    report_error_and_exit("Child: invalid argc");
  }

  char *shm_name = argv[1];
  char *sem_full_name = argv[2];
  char *sem_empty_name = argv[3];

  sem_t *sem_full = sem_open(sem_full_name, 0);
  if (sem_full == SEM_FAILED) {
    report_error_and_exit("Child: sem_open (full) failed");
  }

  sem_t *sem_empty = sem_open(sem_empty_name, 0);
  if (sem_empty == SEM_FAILED) {
    report_error_and_exit("Child: sem_open (empty) failed");
  }

  int shm_fd = shm_open(shm_name, O_RDWR, 0666);
  if (shm_fd == -1) {
    report_error_and_exit("Child: shm_open failed");
  }

  void *shm_ptr = mmap(NULL, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_ptr == MAP_FAILED) {
    report_error_and_exit("Child: mmap failed");
  }

  close(shm_fd);

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
        process_line(line_buf, shm_ptr, sem_full, sem_empty);
      }
      line_pos = 0;
    }
  }

  if (line_pos > 0) {
    line_buf[line_pos] = '\0';
    process_line(line_buf, shm_ptr, sem_full, sem_empty);
  }

  sem_wait(sem_empty);
  strcpy((char *)shm_ptr, EOF_SIGNAL);
  sem_post(sem_full);

  munmap(shm_ptr, SHM_SIZE);
  sem_close(sem_full);
  sem_close(sem_empty);

  return 0;
}
