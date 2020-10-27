#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int main (int argc, char* argv[])
{

  int child_stat = 0;

	char mem[30]; // memory for execvp
	char input[20]; // for input in terminal(commands and arguments)
	char *token; // to tokenize string
	char *arg[30]; //array to store arg from input_str
  int i = 0; //index for arg array

  scanf("%[^\n]s", input); //scan the input in the terminal until enter key is pressed (\n)
  int quit = strcmp("quit", input); //returns 0 if input string matches "quit"

  while (quit != 0) //while user didn't enter quit
  {
    //break string input into tokens
    token = strtok(input, " ");

    while (token != NULL)
    {
      arg[i++]=token;
      token = strtok(NULL, " ");
    }

    child_stat = fork();

    if (child_stat < 0) //if error
    {
      perror("Fork Failed\n");
      exit(EXIT_FAILURE);
    }

    else if (child_stat == 0) //child process
    {
      //execute command and arguments from input
      execvp(arg[0], arg);

      // if the request file doesnt exist, then print error message
      if (execvp(arg[0], arg) < 0)
      {
        perror("\tUnknown Command");
        return 1;
      }

    }

    else //parent process
		{
      wait(&child_stat); //wait for child process
			execvp(argv[0], argv); //executes program again --> asks user for new command input
    }

	}

	return 0;
}