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

  if (child == -1) //if error
  {
    perror("Child Fork Failed\n");
    exit(EXIT_FAILURE);
  }

  if (child == 0) //child process
  {
    printf("Child created successful.\nChild PID: %d\n", getpid()); //print child pid
    execl("/bin/date","date",NULL); //execute date file to display date and time
    printf("EXECL FAILED\n"); //error for execution of date
    exit(EXIT_SUCCESS);
  }

  else //parent process
  {
    printf("Parent PID: %d\n", getpid()); //print parent pid
  }

  return 0;
}