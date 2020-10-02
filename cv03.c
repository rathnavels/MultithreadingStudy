#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <stdint.h>

const size_t NUMTHREADS = 10;

int done = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* threadEntry(void *id)
{
	int threadId = (long)id;
	const uint8_t workLoops = 5;
	for(int i=1; i<=workLoops; i++)
	{
		printf("Thread %d working (%d/%d)\n", threadId,i,workLoops);
		sleep(1);
	}

	pthread_mutex_lock(&mutex);

	done++;
	printf("Thread %d: done is now %d. Signaling\n",threadId,done);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);	
}

int main(int argc, char **argv)
{
	puts("Thread Main Starting");
	pthread_t threads[NUMTHREADS];
	for(int t = 0; t < NUMTHREADS; t++)
		pthread_create(&threads[t],NULL,threadEntry,(void*)(long)t);

	pthread_mutex_lock(&mutex);
	while(done < NUMTHREADS)
	{
		printf("Thread Main: done is %d, which is < %d so waiting on cond\n",done,(int)NUMTHREADS);
		pthread_cond_wait(&cond,&mutex);
	}

	printf("Thread Main: done == %d so everyone is done\n",done);

	pthread_mutex_unlock(&mutex);
	return 0;
}
	





