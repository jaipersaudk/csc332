#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char* argv[])
{
  int child_status = 0;
  int child = fork();
  wait(&child_status); //let child process execute first then parent


  if (child == -1)
  {
    perror("Child Fork Failed\n");
    exit(EXIT_FAILURE);
  }

  if (child == 0)
  {
    printf("Child created successful. PID: %d\n", getpid());
    execl("/bin/date","date",NULL);
    exit(EXIT_SUCCESS);
  }

  else
  {
    printf("Parent PID: %d\n", getpid());
  }

  return 0;
}