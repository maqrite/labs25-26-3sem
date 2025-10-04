#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

static void report_error_and_exit(const char *msg) {
  int i = 0;
  while (msg[i])
    i++;
  write(STDERR_FILENO, msg, i);
  write(STDERR_FILENO, "\n", 1);
  _exit(1);
}

int main(void) {
  const char *prompt = "Enter filename: ";
  write(STDERR_FILENO, prompt, 16);

  char filename[256];
  ssize_t bytes_read = read(STDIN_FILENO, filename, sizeof(filename) - 1);
  if (bytes_read <= 0) {
    report_error_and_exit("Parent: Failed to read filename.");
  }

  if (filename[bytes_read - 1] == '\n') {
    filename[bytes_read - 1] = '\0';
  } else {
    filename[bytes_read] = '\0';
  }

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    report_error_and_exit("Parent: Failed to create pipe.");
  }

  pid_t pid = fork();
  if (pid == -1) {
    report_error_and_exit("Parent: Fork failed.");
  }

  if (pid == 0) {

    int file_fd = open(filename, O_RDONLY);
    if (file_fd == -1) {
      report_error_and_exit("Child: Failed to open file.");
    }

    if (dup2(file_fd, STDIN_FILENO) == -1) {
      report_error_and_exit("Child: dup2 for stdin failed.");
    }

    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
      report_error_and_exit("Child: dup2 for stdout failed.");
    }

    close(file_fd);
    close(pipefd[0]);
    close(pipefd[1]);

    char *argv[] = {"./child", NULL};
    execv(argv[0], argv);

    report_error_and_exit("Child: execv failed.");

  } else {
    close(pipefd[1]);

    char buffer[256];
    ssize_t count;
    while ((count = read(pipefd[0], buffer, sizeof(buffer))) > 0) {
      write(STDOUT_FILENO, buffer, count);
    }
    close(pipefd[0]);

    waitpid(pid, NULL, 0);
  }

  return 0;
}
