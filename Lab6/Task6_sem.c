#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include "sem.h"

#define N 2
#define buff_size 1
#define PERMS 0666

int*buffer;
