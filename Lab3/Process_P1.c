#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h> //for open system call

int main (int argc, char* argv[])
{
  //create destination1.txt - must use O_CREAT flag to create new file
  int fd1 = open("destination1.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR); //grant user read, write, and execute permissions

  if (fd1 == -1) // if there is an error
    printf("Failed to create/open destination1.txt\n");

  else
    printf("destination1.txt opened successfully\n");
  close(fd1); //close the file

  //create destination2.txt
  int fd2 = open ("destination2.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR);

  if (fd2 == -1)
    printf("Failed to create/open destination2.txt\n");

  else
    printf("destination2.txt opened successfully\n");

  close(fd2); //close the file

}
