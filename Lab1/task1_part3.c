#include <stdio.h>
#include <stdlib.h> //for EXIT_FAILURE
#include <unistd.h>
#include <errno.h>
#include <fcntl.h> // for open system call

int main (int argc, char* argv[])
{
  int buff_size = 78;
  int count = 0;
  char buffer[buff_size];
  char buffer_abc[3] = {'A','B','C'};
  int returnval;

  for (int i = 1; i <= 2; i++)
  {
    char* filepath = argv[i];

    // Check file existence

    returnval = access (filepath, F_OK);
    if (returnval == 0)
      printf ("\n %s exists\n", filepath);
    /* if doesnt return 0, then errno will have a value */
    else
    {
      if (errno == ENOENT)
        printf ("\n %s does not exist\n", filepath);
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
      printf ("\n %s does not have read access\n", filepath);


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
  }


  int source_fd = open(argv[1], O_RDONLY); //open source file
  int dest_fd;

  //if error with opening source file, terminate program
  if (source_fd < 0)
  {
    perror ("\nSource File Failed to Open\n");
    exit(EXIT_FAILURE);
  }

  //if source file is open, then open dest file
  else
  {
    printf("\nSource File Opened Successfully\n");
    dest_fd = open(argv[2], O_RDWR);

    //if error with opening dest file, terminate program
    if (dest_fd < 0)
    {
      perror ("\nDestination File Failed to Open\n");
      exit(EXIT_FAILURE);
    }
    else
    {
      printf("\nDestination File Opened Successfully\n");
    }
  }

  //Read source file 75 bytes at a time into the buffer --> when count == 0, it reached the end of the file
  while ( (count = read(source_fd, buffer, buff_size)) != 0 )
  {
    //printf("\n Count_before = %d\n", count);
    //replace each '5' in the buffer with 'O'
    for (int i = 0; i<count; i++)
    {
      if (buffer[i] == '5')
        buffer[i] = 'O';
    }
    //write contents of source file 75 bytes at a time from buffer into the dest file
    count = write (dest_fd, buffer, count);
    //printf("\n Count_after = %d\n", count);
    if (count == buff_size)
    {
        write(dest_fd, buffer_abc,3);
    }
  }

  // close source and dest file
  close(source_fd);
  close(dest_fd);

  printf("\nCopy Successful\n");

  return 0;
}
