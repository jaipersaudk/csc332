#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{

	int a = 10, b = 25, fq=0, fr=0;
	fq = fork();   // fork a child - call it process Q
	if(fq == 0){		
		a = a+b;
		printf("Process Q - Value of a: %d, Value of b: %d, Value of pid: %d\n", a, b, getpid());
		fr = fork();   // fork another child - call it process R
		if (fr != 0){
			b = b+20;
			printf("Process Q - Value of a: %d, Value of b: %d, Value of pid: %d\n", a, b, getpid());
		}
		else{
			a=(a*b)+30;
			printf("Process R - Value of a: %d, Value of b: %d, Value of pid: %d\n", a, b, getpid());
		}
	}
	else{
		b=a+b-5;
		printf("Process P - Value of a: %d, Value of b: %d, value of pid: %d\n", a, b, getpid());
	}

	return 0;
}
