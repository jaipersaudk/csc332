#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h> //for EXIT_FAILURE
#include <sys/wait.h> //waitpid system call
#include <errno.h>

int main (int argc, char* argv[])
{
  int b = 5;
  int a = 3;
  int c = 45;
  printf("Process Q \n\tThe value of a: %d \n\tThe value of b: %d \n\tThe Process ID: %d\n", a,b,c);
}