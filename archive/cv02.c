#include <pthread.h>
#include <stdio.h>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int done = 0;

void *child(void *arg)
{
	puts("Child Begin");
	pthread_mutex_lock(&mutex);
	done = 1;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
	puts("Child End");
}

void thread_join()
{
	pthread_mutex_lock(&mutex);
	while(done == 0)
		pthread_cond_wait(&cond,&mutex);
	pthread_mutex_unlock(&mutex);
	
}

int main(int argc, char **argv)
{
	printf("Parent Begin\n");
	pthread_t p;
	pthread_create(&p,NULL,child,NULL);
	thread_join();
	puts("Parent End");
}
