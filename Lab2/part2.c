#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> //for EXIT_FAILURE
#include <sys/wait.h> //waitpid system call
#include <errno.h>

int main (int argc, char* argv[])
{
  int a = 10;
  int b = 25;
  int fq = 0;
  int fr = 0;

  fq = fork(); // fork a child (call it Process Q) - 0 is returned to child, and PID is returned to parent
  if (fq == 0) //child (Q) executes this
  {
    a = a+b;
    //print values of a,b, and process_id
    printf("Process Q \n\tThe value of a: %d \n\tThe value of b: %d \n\tThe Process ID: %d\n", a,b,getpid());

    fr = fork(); // fork another child (call it Process R) - 0 is returned to child, and PID is returned to parent
    if (fr != 0) //parent (Q) executes this
    {
      b = b+20;
      printf("Process Q \n\tThe value of a: %d \n\tThe value of b: %d \n\tThe Process ID: %d\n", a,b,getpid());
    }
    else // child (R) executes this --> new child process(Process R)
    {
      a = (a*b)+30;
      printf("Process R \n\tThe value of a: %d \n\tThe value of b: %d \n\tThe Process ID: %d\n", a,b,getpid());
    }
  }

  else // parent (P) executes this
  {
    b=a+b-5;
    printf("Process P \n\tThe value of a: %d \n\tThe value of b: %d \n\tThe Process ID: %d\n", a,b,getpid());
  }


  return 0;


}