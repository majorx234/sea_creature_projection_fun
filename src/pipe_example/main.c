#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int main() {
  pid_t childpid;
  char  send_string[] = "Hello, my parent!\n";
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
  // parent process should read date through the pipe
  if(childpid == 0) { // child
    int nbytes = 0;
    // child process don't need reading -> close file descriptor
    close(fd[0]);
    // close stdin on child:
    close(stdin);

    nbytes = write(fd[1], send_string, (strlen(send_string)+1));
    printf("send %d bytes\n", nbytes);
    exit(0);
  }
  else { // parent
    int nbytes = 0;
    // parent don't need writing -> close file descriptor
    close(fd[1]);
    sleep(1);
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
    printf("received %d bytes: %s\n",nbytes, readbuffer);
    exit(0);
  }
}
