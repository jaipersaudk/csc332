#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{	
	int status, pid;
	pid = fork();   //Create the child
	wait(&status);
	if(pid != 0){
		printf("Parent's PID is: %d\n", getpid());  //Get parent's pid
	}

	else{
		printf("Child's PID is: %d\n", getpid());  //Get child's pid
        execl("/bin/date", "date", NULL);    // execute a file: date in bin file
		printf("EXECL Failed\n");
		
	}
	return 0;
}