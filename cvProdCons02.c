#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFSIZE 3

int buffer[BUFSIZE];
int add = 0;
int rem = 0;
int num = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condProd = PTHREAD_COND_INITIALIZER;
pthread_cond_t condCons = PTHREAD_COND_INITIALIZER;

void *producer(void *arg)
{
	for(int i=1; i<=20; i++)
	{
		pthread_mutex_lock(&mutex);
		while(num == BUFSIZE)
			pthread_cond_wait(&condProd,&mutex);
		if(num > BUFSIZE)
			exit(1);
		buffer[add] = i;
		add = (add+1)%BUFSIZE;
		num++;
		printf("Producer: Inserted %d\n", i);
		fflush(stdout);	
		pthread_cond_signal(&condCons);
		pthread_mutex_unlock(&mutex);
	
		}
	printf("Producer: Quitting\n");
	fflush(stdout);
	pthread_exit(NULL);
}

void *consumer(void *arg)
{
	int i;
	while(1)
	{
		pthread_mutex_lock(&mutex);
	
		while(num == 0)
			pthread_cond_wait(&condCons,&mutex);
		
		i = buffer[rem];
		rem = (rem+1)%BUFSIZE;
		num--;	
		if(num < 0) 
			break;
		printf("Consume value %d\n",i);
		fflush(stdout);	
		pthread_cond_signal(&condProd);
		pthread_mutex_unlock(&mutex);
	
	}
	pthread_exit(NULL);
}

void main(int argc, char **argv)
{
	pthread_t prod,cons;
	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&cons,NULL,consumer,NULL);

	pthread_join(prod,NULL);
	pthread_join(cons,NULL);
	printf("Parent Quitting\n");

}
