#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include "sem.h"

int main ()
{
  int child; //for child processes
  int examples = 0; //to show 10 examples in the program
  int randNum; // pick random ingredients - tobacco and match (0), match and paper (1), paper and tobacco (2)
  //synchronize agent and smoker processes
  //we will need 5 semaphores - agents, 3 smokers, and lock
  int agent;
  int tobacco; //smoker with tobacco
  int match; //smoker with match
  int paper; //smoker with paper
  int lock;

  agent = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
  if (agent == -1) //if error
  {
    perror("semget failed\n");
    exit (-1);
  }

  tobacco = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
  if (tobacco == -1) //if error
  {
    perror("semget failed\n");
    exit (-1);
  }

  match = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
  if (match == -1) //if error
  {
    perror("semget failed\n");
    exit (-1);
  }

  paper = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
  if (paper == -1) //if error
  {
    perror("semget failed\n");
    exit (1);
  }

  lock = semget(IPC_PRIVATE,1,0666 | IPC_CREAT);
  if (lock == -1) //if error
  {
    perror("semget failed\n");
    exit (-1);
  }

  //create semaphores - according to the link in assignment, all semaphores are initialized to 0 except for lock, which is initialized to 1
  sem_create(agent,0);
  sem_create(tobacco,0);
  sem_create(match,0);
  sem_create(paper,0);
  sem_create(lock,1);

  //child processes for the different smokers
  if((child = fork()) == -1)
  {
    perror("Fork Failed\n");
    exit(1);
  }

  //code reflects the pseudocode from the website
  else if (child == 0)
  {
    while (1)
    {
      P(tobacco);
      P(lock);
      printf("Smoker with Tobacco makes cigarette with Match and Paper on table. Smokes the cigarette.\n");
      sleep(1);
      V(agent);
      V(lock);
    }

  }

  if((child = fork()) == -1)
  {
    perror("Fork Failed\n");
    exit(1);
  }

  //code reflects the pseudocode from the website
  else if (child == 0)
  {
    while (1)
    {
      P(match);
      P(lock);
      printf("Smoker with Match makes cigarette with Paper and Tobacco on table. Smokes the cigarette.\n");
      sleep(1);
      V(agent);
      V(lock);
    }

  }

  if((child = fork()) == -1)
  {
    perror("Fork Failed\n");
    exit(1);
  }

  //code reflects the pseudocode from the website
  else if (child == 0)
  {
    while (1)
    {
      P(paper);
      P(lock);
      printf("Smoker with Paper makes cigarette with Tobacco and Match on table. Smokes the cigarette.\n");
      sleep(1);
      V(agent);
      V(lock);
    }

  }

  //agent process
  while (examples < 10) // only 10 examples
  {
    P(lock);
    randNum = rand() % 3; //obtain random value between [0-2]
    if (randNum == 0)
    {
      printf("Agent places Tobacco and Match on table.\n");
      sleep(1);
      V(paper);
    }

    else if (randNum == 1)
    {
      printf("Agent places Match and Paper on table.\n");
      sleep(1);
      V(tobacco);
    }

    else if (randNum == 2)
    {
      printf("Agent places Paper and Tobacco on table.\n");
      sleep(1);
      V(match);
    }
    V(lock);
    P(agent);

    examples++;
  }

  exit(0);

}