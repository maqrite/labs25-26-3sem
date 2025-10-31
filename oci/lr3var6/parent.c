#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 4096
#define EOF_SIGNAL "EOF_SIGNAL"

#define SHM_NAME_TPL "/lab2_shm_%d"
#define SEM_FULL_TPL "/lab2_sem_full_%d"
#define SEM_EMPTY_TPL "/lab2_sem_empty_%d"

void report_error_and_exit(const char *msg) {
  int i = 0;
  while (msg[i]) {
    i++;
  }

  write(STDERR_FILENO, msg, i);
  write(STDERR_FILENO, "\n", 1);
  _exit(1);
}

int main(void) {
  const char *prompt = "Enter filename: ";
  write(STDERR_FILENO, prompt, 16);

  char filename[256];
  ssize_t bytes_read = read(STDERR_FILENO, filename, sizeof(filename) - 1);
  if (bytes_read <= 0) {
    report_error_and_exit("Parent: Failed to read filename");
  }

  if (filename[bytes_read - 1] == '\n') {
    filename[bytes_read - 1] = '\0';
  } else {
    filename[bytes_read] = '\0';
  }

  pid_t pid = getpid();
  char shm_name[256];
  char sem_full_name[256];
  char sem_empty_name[256];

  snprintf(shm_name, sizeof(shm_name), SHM_NAME_TPL, pid);
  snprintf(sem_full_name, sizeof(sem_full_name), SEM_FULL_TPL, pid);
  snprintf(sem_empty_name, sizeof(sem_empty_name), SEM_EMPTY_TPL, pid);

  sem_t *sem_full = sem_open(sem_full_name, O_CREAT | O_EXCL, 0666, 0);
  if (sem_full == SEM_FAILED) {
    report_error_and_exit("Parent: sem_open (full) failed");
  }

  sem_t *sem_empty = sem_open(sem_empty_name, O_CREAT | O_EXCL, 0666, 1);
  if (sem_empty == SEM_FAILED) {
    sem_unlink(sem_full_name);
    report_error_and_exit("Parent: sem_open (empty) failed");
  }

  int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    report_error_and_exit("Parent: shm_open failed");
  }

  if (ftruncate(shm_fd, SHM_SIZE) == -1) {
    report_error_and_exit("Parent: ftruncate failed");
  }

  void *shm_ptr =
      mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (shm_ptr == MAP_FAILED) {
    report_error_and_exit("Parent: mmap failed");
  }

  close(shm_fd);

  pid_t child_pid = fork();
  if (child_pid == -1) {
    report_error_and_exit("Parent: fork failed");
  }

  if (child_pid == 0) {
    sem_close(sem_full);
    sem_close(sem_empty);
    munmap(shm_ptr, SHM_SIZE);

    int file_fd = open(filename, O_RDONLY);
    if (file_fd == -1) {
      report_error_and_exit("Child: failed to open file");
    }

    if (dup2(file_fd, STDIN_FILENO) == -1) {
      report_error_and_exit("Child: dup2 for stdin failed");
    }

    close(file_fd);

    char *argv[] = {"./child", shm_name, sem_full_name, sem_empty_name, NULL};

    execv(argv[0], argv);

    report_error_and_exit("Child: execv failed");
  } else {
    while (1) {
      sem_wait(sem_full);

      if (strcmp((char *)shm_ptr, EOF_SIGNAL) == 0) {
        break;
      }

      ssize_t len = strlen((char *)shm_ptr);
      write(STDOUT_FILENO, shm_ptr, len);

      sem_post(sem_empty);
    }

    waitpid(child_pid, NULL, 0);

    munmap(shm_ptr, SHM_SIZE);
    sem_close(sem_full);
    sem_close(sem_empty);

    shm_unlink(shm_name);
    shm_unlink(sem_full_name);
    shm_unlink(sem_empty_name);
  }

  return 0;
}
