#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main (void)
{
  int child_status = 0;
  int child = fork();
  wait(&child_status);

  if (child == -1) //if error
  {
    perror("Child Fork Failed\n");
    exit(EXIT_FAILURE);
  }

  if (child == 0) //child process
  {
    printf("Child created successful.\nChild PID: %d\n", getpid()); //print child pid
    char *argv[] = {"ls", "-laxo", NULL};
    execvp(argv[0], argv);
    printf("EXECL FAILED\n"); //if error
    exit(EXIT_SUCCESS);
  }

  else //parent process
  {
    printf("Parent PID: %d\n", getpid()); //print parent pid
  }


  return 0;
}
