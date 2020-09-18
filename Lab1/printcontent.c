#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> // for EXIT_FAILURE
#include <errno.h>
#include <fcntl.h> // for open system call

int main (int argc, char* argv[])
{
  int count = 0; //for read and write
  char buffer[5]; //for read and write

  char* filepath = argv[1]; //first parameter from cmd line
  int returnval;

  // Check file existence

  returnval = access (filepath, F_OK);
  if (returnval == 0)
    printf ("\n %s exists\n", filepath);
  /* if doesnt return 0, then errno will have a value */
  else
  {
    if (errno == ENOENT)
      printf ("%s does not exist\n", filepath);
    else if (errno == EACCES)
    {
      printf ("%s is not accessible\n", filepath);
      return 0;
    }
  }

  //Check read access...

  returnval = access (filepath, R_OK);
  if (returnval == 0)
    printf ("\n %s has read access\n", filepath);
  else
    printf ("%s does not have read access\n", filepath);


  //Check write access..

  returnval = access(filepath, W_OK);
  if (returnval == 0)
    printf ("\n %s has write access\n", filepath);
  else if (errno == EACCES)
    printf ("\n %s does not have write access\n", filepath);
  else if (errno == EROFS) //EROFS read-only file system
  {
    printf ("\n %s does not have write access (only read access)\n", filepath);
  return 0;
  }

  //displaying file contents
  int fd = open(filepath, O_RDONLY); //open file in read-only

  //display message based on value of fd
  if (fd < 0)
  {
    perror("\n File Failed to Open\n"); //terminate program if file cannot open
    exit(EXIT_FAILURE);
  }
  else
  {
    printf ("\nFile Opened Successfully\n");

    //Read the file 5 bytes at a time into the buffer --> when count == 0, it reached the end of the file
    while ((count = read(fd, buffer, 5)) != 0)
    {
      //write contents of file 5 bytes at a time from buffer --> fd == 1 for stdout
      count = write (1,buffer,count);
    }

  }

  //close the file after reading and writing from it
  close(fd);

  printf("\n");

  return 0;
}
