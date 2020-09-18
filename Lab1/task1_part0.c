#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h> // for open system call

int main (int argc, char* argv[])
{

/* Part 0 */

  char* filepath = argv[1]; //first parameter from cmd line
  int returnval;

  // Check file existence

  returnval = access (filepath, F_OK);
  if (returnval == 0)
    printf ("\n %s exists\n", filepath);
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

  /* Create and open a new file destination.txt */
  /* must use O_CREAT flag to create the new file --> must specify mode for user*/

  int fd = open("destination.txt", O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IXUSR);
  //S_IRUSR|S_IWUSR|S_IXUSR) --> grants user read, write, and execute permissions

  printf("fd = %d\n", fd); // to test value of fd
  close(fd); //close destination file

  return 0;
}
