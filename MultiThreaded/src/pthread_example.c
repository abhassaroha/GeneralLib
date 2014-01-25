#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 2

void* printCount(void* arg)
{
	long tid = (long) arg;
	printf("%ld\n", tid);
	pthread_exit(NULL);
}

int main()
{
	pthread_t threads[NUM_THREADS];
	int status;
	long i;
	for (i = 0; i < NUM_THREADS; i++)
	{
		status =	pthread_create(&threads[i],NULL, printCount, (void*)i); 
		if (status) 
		{
			printf("Thread creation failed, error code: %d\n", status);
			exit(-1);
		}

	}
	pthread_exit(NULL);
	return 0;
}
