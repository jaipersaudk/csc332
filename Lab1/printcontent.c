#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[])
{
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





  return 0;
}
