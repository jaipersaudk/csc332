#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int main (int argc, char* argv[])
{
  int buff1_size = 53; // to read 50 characters for destination1
  char buffer1[buff1_size]; //buffer to put 50 characters of source
  char buffer1_58[buff1_size]; //to store only 5's and 8's of buffer1
  int count1 = 0;

  int buff2_size = 102;// to read 100 characters for destination2
  char buffer2[buff2_size];
  int count2 = 0;

  int dest1_fd, dest2_fd, source_fd;
  source_fd = open("source.txt", O_RDONLY); // open source file for reading
  dest1_fd = open("destination1.txt", O_RDWR); //open destination1 for read and write
  dest2_fd = open("destination2.txt", O_RDWR); //open destination2 for read and write

  if (source_fd == -1 || dest1_fd == -1 || dest2_fd == -1) // if there is an error opening any of the files
  {
    printf("Error opening source or destination files\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    printf ("Source and Destination Files Opened Successfully\n");


    count1 = read(source_fd, buffer1, buff1_size); // read source file 50 bytes at a time into the buffer
    int j = 0; //for index of buffer1_58

    for (int i = 0; i < count1; i++)
    {
      if (buffer1[i] == '5' || buffer1[i] == '8')
      {
        buffer1_58[j] = buffer1[i]; // save buffer1[i] into buffer1_58[j] only if it contains a 5 or 8
        j++;
      }
    }
    write(dest1_fd, buffer1_58, j); //write contents of buffer1_58
    printf("Writing to destination1.txt successful\n");

    count2 = read(source_fd, buffer2, buff2_size); //read the next 100 bytes of source file into buffer
    write(dest2_fd, buffer2, count2); //write to destination from buffer
    printf("Writing to destination2.txt successful\n");
  }


  close(source_fd);
  close(dest1_fd);
  close(dest2_fd);


  return 0;

}