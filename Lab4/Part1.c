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
	char input_str[20]; // for input in terminal(commands and arguments)
	char *token; // to tokenize string
	char *arg[30]; //array to store arg from input_str
  int i = 0; //index for arg array

  scanf("%[^\n]s", input_str); //scan the input in the terminal until enter key is pressed (\n)
  int quit = strcmp("quit", input_str); //returns 0 if input string matches "quit"

  while (quit != 0) //while user didn't enter quit
  {
    token = strtok(input_str, " "); //get first token in string delimited by space

    while (token != NULL)
    {
      arg[i++]=token; // store token into arg_arr
      token = strtok(NULL, " "); //extract all tokens
    }

    child_stat = fork();

    if (child_stat < 0) //if error
    {
      perror("Fork Failed\n");
      exit(EXIT_FAILURE);
    }

    else if (child_stat == 0) //child process
    {
      if (execvp(arg[0], arg) < 0) // if the request file doesnt exist, then print error message
      {
        perror("\texecvp failed");
        return 1;
      }
    }

    else //parent process
		{
      wait(&child_stat); //wait for child process
			execvp(argv[0], argv); //execute command and their arguments
    }

	}

	return 0;
}