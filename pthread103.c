#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 2

typedef struct _thread_data_t
{
	int tid;
	double stuff;
}thread_data_t;

void *threadFun(void *arg)
{
	thread_data_t *data = (thread_data_t*)arg;
	printf("Hello from threadFunc, thread id: %d\n", data->tid);

	pthread_exit(NULL);
}

void runPthread103()
{
	pthread_t thr[NUM_THREADS];
	int i;
	thread_data_t threadData[NUM_THREADS];

	for(i = 0; i < NUM_THREADS; i++)
	{
		threadData[i].tid = i;
		pthread_create(&thr[i], NULL, threadFun, &threadData[i]);
	}

	for(i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(thr[i],NULL);
	}
}




