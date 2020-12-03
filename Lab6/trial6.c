#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t put = PTHREAD_COND_INITIALIZER;
pthread_cond_t tobacco = PTHREAD_COND_INITIALIZER;
pthread_cond_t paper = PTHREAD_COND_INITIALIZER;
pthread_cond_t match = PTHREAD_COND_INITIALIZER;

int times=10;
// i1 & i2: 2 itmes will be put on table  
char *item[] = {"tobacco", "paper", "match"};
void *agentfunc();
void *tobaccofunc();
void *paperfunc();
void *matchfunc();
void *helpfunc();

int main() {
    pthread_t help, agent, tobacco, paper, match;
    srand(time(NULL));
    pthread_create(&help, NULL, &helpfunc, NULL);
    pthread_create(&agent, NULL, &agentfunc, NULL);
    pthread_create(&tobacco, NULL, &tobaccofunc, NULL);
    pthread_create(&paper, NULL, &paperfunc, NULL);
    pthread_create(&match, NULL, &matchfunc, NULL);
    
    pthread_join(help, NULL);
    pthread_join(agent, NULL);
    pthread_join(tobacco,NULL);
    pthread_join(paper,NULL);
    pthread_join(match,NULL);
}

void *helpfunc() {
    while(1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_signal(&put);
        pthread_mutex_unlock(&mutex);
        if(times<=0) exit(0);
    }
}

void *agentfunc() {
    while(1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&put, &mutex);
        times--;
        int i1=0, i2=0;
        while(i1==i2) {
            i1=rand()%3;
            i2=rand()%3;
        }
        printf("Put %s on table\n", item[i1]);
        printf("Put %s on table\n", item[i2]);
        if(i1+i2==1) pthread_cond_signal(&match);
        if(i1+i2==2) pthread_cond_signal(&paper);
        if(i1+i2==3) pthread_cond_signal(&tobacco);
        pthread_mutex_unlock(&mutex);
        if(times<=0) exit(0); 
    }
}

void *tobaccofunc() {
    while(1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&tobacco, &mutex);
        printf("Smoker 1 with tobacco picks up match\n");
        printf("Smoker 1 with tobacco picks up paper\n");
        printf("Smoker 1 smokes\n");
        pthread_mutex_unlock(&mutex);
        if(times<=0) exit(0);
    }
}

void *paperfunc() {
    while(1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&paper, &mutex);
        printf("Smoker 2 with paper picks up match\n");
        printf("Smoker 2 with paper picks up tobacco\n");
        printf("Smoker 2 smokes\n");
        pthread_mutex_unlock(&mutex);
        if(times<=0) exit(0);
    }
}

void *matchfunc() {
    while(1) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&match, &mutex);
        printf("Smoker 3 with match picks up paper\n");
        printf("Smoker 3 with match picks up tobacco\n");
        printf("Smoker 3 smokes\n");
        pthread_mutex_unlock(&mutex);
        if(times<=0) exit(0);
    }
}
