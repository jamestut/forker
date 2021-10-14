#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char ** argv) {
  int fd;
  pid_t pid;

  if (argc <= 1) {
    puts("Usage: forker (executable) (args...)");
    return 0;
  }

  fd = open("/dev/null", O_RDWR);
  if (fd < 0) {
    perror("Cannot open /dev/null");
    return 1;
  }

  pid = fork();
  if (pid < 0) {
    perror("Cannot fork");
    return 1;
  }

  if (!pid) {
    // close stdin, out, err
    for (int i = 0; i <= 2; ++i) {
      close(i);
      int newfd = dup2(fd, i);
      if (newfd != i) {
        // return 1;
      }
    }

    // exec!
    if (execvp(argv[1], argv + 1) < 0) {
      perror("Error exec");
    }
  }
}