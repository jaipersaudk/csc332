#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> //for EXIT_FAILURE
#include <sys/wait.h> //waitpid system call
#include <errno.h>

int main (int argc, char* argv[])
{
  int w1, w2; //for waitpid for both children
  int child1_status = 0; //status for first child
  int child1 = fork();

  if (child1 == -1) //error
  {
    perror ("Child 1 Fork Failed");
    exit(EXIT_FAILURE);
  }
  else if (child1 == 0) //success
  //specify child process
  {
    printf("I am child one, my PID is: %d.\n", getpid());
  }
  else
  {
    int child2_status = 0;
    int child2 = fork();

    if (child2 == -1) // error
    {
      perror("Child 2 Fork Failed");
      exit(EXIT_FAILURE);
    }

    else if (child2 == 0) //success
    {
      printf("I am child two, my PID is: %d.\n", getpid());
    }

    else
    {
      printf("I am the parent, my PID is: %d.\n", getpid());

      w1 = waitpid(child1, &child1_status, 0); //wait for the first process to stop. will return -1 for errors
      if (w1 == -1) //if there was an error
      {
        printf("Child 1 did not terminate\n");
      }
      else
      {
        printf("Child 1 terminated\n");
      }

      w2 = waitpid(child2,&child2_status, 0);//wait for the second process to stop. will return -1 for errors

      if (w2 == -1) //if there was an error
      {
        printf("Child 2 did not terminate\n");
      }
      else
      {
        printf("Child 2 terminated\n");
      }

      printf("The Parent's PID is: %d.\n", getpid());

    }

  }

  return 0;

}