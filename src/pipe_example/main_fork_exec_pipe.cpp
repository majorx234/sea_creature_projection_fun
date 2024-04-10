#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main() {
  pid_t childpid;
  char  send_string[] = "beta\nalpha\nceta\nomega\ngamma\ndelta\n";
  char  readbuffer[80];
  int fd[2];
  // pipe:
  //   fd[0] is reading
  //   fd[1] is writing

  if(pipe(fd)){
    printf("could not create pip\n");
  }

  // fork the proces
  if((childpid = fork()) == -1)
  {
    perror("fork");
    exit(1);
  }

  // child process should write data
  // parent process should read data through the pipe
  // - execs a shell command sort
  if(childpid == 0) { // child
    int nbytes = 0;
    // child don't read -> close file descriptor
    close(fd[0]);
    nbytes = write(fd[1], send_string, (strlen(send_string)+1));
    printf("send %d bytes\n", nbytes);
    close(fd[1]);
    exit(0);
  }
  else { // parent
    int nbytes = 0;
    // parent process don't need writing -> close file descriptor
    close(fd[1]);
    // map fd[0] to STDIN
    dup2(fd[0], STDIN_FILENO);
    execlp("sort", "sort", NULL);
  }
  return 0;
}
