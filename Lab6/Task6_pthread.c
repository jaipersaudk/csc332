#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t table = PTHREAD_COND_INITIALIZER;
pthread_cond_t tobacco = PTHREAD_COND_INITIALIZER;
pthread_cond_t match = PTHREAD_COND_INITIALIZER;
pthread_cond_t paper = PTHREAD_COND_INITIALIZER;

int examples = 0; //to show 10 examples in the program
char *ingred[] = {"Tobacco", "Match", "Paper"};

void *agent_process()
{
  while (1)
  {
    pthread_mutex_lock(&mutex); //lock
    pthread_cond_wait(&table, &mutex);

    // used for agent to place random ingredient on the table
    int ingred1 = 0;
    int ingred2 = 0;
    int smoker = 0; //calculate which smoker to select based on ingredient on table

    //generate random number (0-2) for ingredient (must be different)
    while (ingred1 == ingred2)
    {
      ingred1 = rand() % 3;
      ingred2 = rand() % 3;
      smoker = ingred1+ingred2;
      // ingredient: 0 - Tobacco, 1 - Match, 2 - paper
      // smoker: 1 - paper, 2 - Match, 3 - Tobacco
    }

    //select ingredient according to random number
    printf("Agent places %s and %s on table.\n", ingred[ingred1], ingred[ingred2]);
    if (smoker == 1) //tobacco and match on table - smoker paper
      pthread_cond_signal(&paper);
    else if (smoker == 2) // tobacco and paper on table - smoker has match
      pthread_cond_signal(&match);
    else if (smoker == 3) // match and paper on the table - smoker has tobacco
      pthread_cond_signal(&tobacco);
    pthread_mutex_unlock(&mutex);

    examples++;
  }
}

//similar implementation to one using semaphores
void *smoker_tobacco()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&tobacco, &mutex);
    printf("Smoker with Tobacco makes cigarette with Match and Paper on table. Smokes the cigarette.\n");
    pthread_mutex_unlock(&mutex);
    if (examples >= 10)
      exit (0);
  }
}

//similar implementation to one using semaphores
void *smoker_match()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&match, &mutex);
    printf("Smoker with Match makes cigarette with Paper and Tobacco on table. Smokes the cigarette.\n");
    pthread_mutex_unlock(&mutex);
    if (examples >= 10)
      exit (0);
  }
}

//similar implementation to one using semaphores
void *smoker_paper()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_wait(&paper, &mutex);
    printf("Smoker with Paper makes cigarette with Tobacco and Match on table. Smokes the cigarette.\n");
    pthread_mutex_unlock(&mutex);
    if (examples >= 10)
      exit (0);
  }
}


void *table_process()
{
  while(1)
  {
    pthread_mutex_lock(&mutex);
    pthread_cond_signal(&table);
    pthread_mutex_unlock(&mutex);
    if (examples >= 10)
      exit (0);
  }
}

int main()
{
  //the threads used to create and join
  pthread_t table, agent, tobacco, match, paper;

  //to generate more random-like numbers
  srand(time(NULL));

  //create threads for smokers, agent, and table
  pthread_create(&table, NULL, &table_process, NULL);
  pthread_create(&agent, NULL, &agent_process, NULL);
  pthread_create(&tobacco, NULL, &smoker_tobacco, NULL);
  pthread_create(&paper, NULL, &smoker_paper, NULL);
  pthread_create(&match, NULL, &smoker_match, NULL);

  //wait for threads to finish
  pthread_join(table, NULL);
  pthread_join(agent, NULL);
  pthread_join(tobacco, NULL);
  pthread_join(paper, NULL);
  pthread_join(match, NULL);

  exit(0);
}

