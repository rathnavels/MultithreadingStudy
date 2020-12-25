#include<stdio.h>
#define __USE_GNU
#include<pthread.h>
#include<stdlib.h>

#define NUM_HANDLER_THREADS 3

pthread_mutex_t requestMutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_cond_t gotRequest = PTHREAD_COND_INITIALIZER;

int numreqs = 0;

struct request
{
	int number;
	struct request* next;
};

struct request* requests = NULL;
struct request* lastreq = NULL;

void add_request(int requestNum, pthread_mutex_t* p_mutex, pthread_cond_t* p_cond_var)
{
	int rc;
	struct request* a_request;

	a_request = (struct request*)malloc(sizeof(struct request));
	
	a_request->number = requestNum;
	a_request->next = NULL;

	pthread_mutex_lock(p_mutex);
	if(numreqs == 0)
	{
		requests = a_request;
		lastreq = a_request;
	}
	else
	{
		lastreq->next = a_request;
		lastreq = a_request;
	}

	numreqs++;
	printf("No of reqs: %d\n",numreqs);
	pthread_mutex_unlock(p_mutex);
	pthread_cond_signal(p_cond_var);
}

struct request* get_request(pthread_mutex_t* p_mutex)
{
	struct request* a_request;
	pthread_mutex_lock(p_mutex);

	if(numreqs > 0)
	{
		a_request = requests;
		requests = requests->next;
		if(requests == NULL)
			lastreq = NULL;
		numreqs--;
	}
	else
		a_request = NULL;

	pthread_mutex_unlock(p_mutex);
	return a_request;
}

void handle_request(struct request* a_request, int thread_id)
{
	if(a_request)
	{
		printf("Thread %d handled request %d\n",thread_id,a_request->number);
		fflush(stdout);
	}
}

void *handle_requests_loop(void* data)
{
	int rc;
	struct request* a_request;
	int thread_id = *((int*)data);
	printf("Starting thread %d\n",thread_id);
	fflush(stdout);
	while(1)
	{
		//printf("Thread %d, numreqs = %d\n",thread_id,numreqs);
		//fflush(stdout);

		if(numreqs > 0)
		{
			a_request = get_request(&requestMutex);
			if(a_request)
			{
				handle_request(a_request,thread_id);
			}	
			else
			{
				pthread_cond_wait(&gotRequest,&requestMutex);
			}
		}
	}
}

int main(int argc, char **argv)
{
	int i;
	int thr_id[NUM_HANDLER_THREADS];
	pthread_t p_threads[NUM_HANDLER_THREADS];
	struct timespec delay;

	for(i = 0; i<NUM_HANDLER_THREADS; i++)
	{
		thr_id[i] = i;
		pthread_create(&p_threads[i],NULL,handle_requests_loop,(void*)&thr_id[i]);
	}
	sleep(3);

	for(int i=0; i<10; i++)
	{
		add_request(i,&requestMutex,&gotRequest);
		if(rand() > 3 * (RAND_MAX/4))
		{
			delay.tv_sec = 0;
			delay.tv_nsec = 10;
			nanosleep(&delay,NULL);
		}
	}
	sleep(5);
	printf("Glory we are done.\n");
	return 0;
}
























