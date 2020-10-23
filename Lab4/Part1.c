#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main (int argc, char* argv[])
{

  char memory[30];
  char input_str[20];
  char *token;
  char *arg_arr[30];

  int child_status = 0;

  scanf("%[^\n]s", input_str);
  int quit = strcmp("quit", input_str);
  int args = 0;

  while (quit != 0)
  {
    token = strtok(input_str, " ");

    while (token != NULL);
    {
      arg_arr[args++]=token;
      token = strtok(NULL, " ");
    }

    child_status = fork();

    if (child_status == -1) //if error
    {
    perror("Child Fork Failed\n");
    exit(EXIT_FAILURE);
    }

    else if (child_status == 0) //child process
    {
      if (execvp(*arg_arr, arg_arr) < 0)
      {
        perror("Fail\n");
        return 1;
      }
    }

    else //parent process
    {
      wait(&child_status);
      execvp(argv[0], argv);
    }
  }

  return 0;
}
