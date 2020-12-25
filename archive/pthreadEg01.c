#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>

int count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *count_to_big(void *arg)
{
	for(int i=0; i<(INT_MAX-2)/2; i++)
	{
		pthread_mutex_lock(&lock);
		count++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void runEg01()
{
	pthread_t thread;
	pthread_create(&thread,NULL,count_to_big,NULL);
	count_to_big(NULL);
	printf("%d\n",count);
	pthread_join(thread,NULL);
}
