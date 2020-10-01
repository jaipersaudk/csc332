#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> //for EXIT_FAILURE
#include <sys/wait.h> //waitpid system call
#include <errno.h>

int main (int argc, char* argv[])
{
  int w1,w2; //waitpid for children
  int child1_status = 0; //status for first child
  int child1 = fork();

  if (child1 == -1) //error
  {
    perror ("Child 1 Fork Failed");
    exit(EXIT_FAILURE);
  }

  else if (child1 == 0) //executed by child
  //specify child process
  {
    printf("I am child one, my PID is: %d.\n", getpid());
    exit(EXIT_SUCCESS);
  }

  else //executed by parent
  {
    int child2_status = 0; //status for second child
    int child2 = fork();

    if (child2 == -1) // error
    {
      perror("Child 2 Fork Failed");
      exit(EXIT_FAILURE);
    }

    else if (child2 == 0) //executed by child
    {
      printf("I am child two, my PID is: %d.\n", getpid());
      exit(EXIT_SUCCESS);
    }

    else // executed by parent
    {
      printf("I am the parent, my PID is: %d.\n", getpid());

      w1 = waitpid(child1, &child1_status, 0); //wait for the first process to stop. will return -1 for errors
      if (w1 == -1) //if there was an error
      {
        printf("Child 1 did not terminate\n");
        exit(EXIT_FAILURE);
      }

      else if (w1 == child1) // check how child 1 process was ended
      {
        if (WIFEXITED(child1_status))
          printf("Child 1 terminated normally\n");
        else if (WIFSIGNALED(child1_status))
          printf("Child 1 terminated by signal\n");
        else if (WIFSTOPPED(child1_status))
            printf("Child 1 process has stopped\n");
      }

      w2 = waitpid(child2, &child2_status, 0);//wait for the second process to stop. will return -1 for errors

      if (w2 == -1) //if there was an error
      {
        printf("Child 2 did not terminate\n");
        exit(EXIT_FAILURE);
      }

      else if (w2 == child2) //check how child 2 process was ended
      {
        if (WIFEXITED(child2_status))
          printf("Child 2 terminated normally\n");
        else if (WIFSIGNALED(child2_status))
          printf("Child 2 terminated by signal\n");
        else if (WIFSTOPPED(child2_status))
            printf("Child 2 process has stopped\n");
      }

      printf("The Parent's PID is: %d.\n", getpid());

    }

  }

  return 0;

}