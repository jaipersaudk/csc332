#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

int main (int argc, char* argv[])
{
  int child1_status = 0;
  int child2_status = 0;
  int child2;

  int child1 = fork(); //for Process_P1
  wait(&child1_status); //wait for child1

  if (child1 == -1) //if error
  {
    printf ("Child Fork Failed\n");
    exit(EXIT_FAILURE);
  }

  if (child1 == 0) //for child process
  {
    printf ("Child created successful.\nChild PID: %d\n", getpid()); //print child pid
    execv("Process_P1", argv); //execute Process_P1 --> must have Process_P1.c compiled and executable filename as Process_P1
  }

  else //for parent process
  {
    printf("Parent PID: %d\n", getpid()); // print parent PID
    sleep(2); //sleep for 2 seconds
    child2 = fork(); //for Process_P2
    wait(&child2_status); //wait for child2

    if(child2 == -1) //if error
    {
      printf ("Child Fork Failed\n");
      exit(EXIT_FAILURE);
    }

    if (child2 == 0) //for child process
    {
      printf ("Child created successful.\nChild PID: %d\n", getpid()); //print child pid
      execv("Process_P2", argv); //execute Process_P2 --> must have Process_P2.c compiled and executable filename as Process_P2
    }

    else //for parent process
    {
      printf("Parent PID: %d\n", getpid()); //print parent PID
    }
  }

  return 0;
}