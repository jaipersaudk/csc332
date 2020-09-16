#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h> // for open system call

int main (int argc, char* argv)
{
  char buffer[80];
  char msg[50] = "hello ifocus institute";
  int fd = open("check.txt", O_CREAT|O_RDWR, S_IRUSR|S_IWUSR|S_IXUSR);

  printf("fd = %d\n", fd);

  if (fd != -1)
  {
    printf("\n check.txt open with RDWR access\n");
    write(fd, msg, sizeof(msg));
    lseek(fd, 0, SEEK_SET);
    read(fd, buffer, sizeof(msg));
    printf("\n %s was written to my file\n", buffer);
    close(fd);
  }

  return 0;
}
