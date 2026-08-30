#include <pthread.h>
#include <stdio.h>
#include <unistd.h> 

static int glob = 0;
// static void *


int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);

static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

/* Loop 'arg' times incrementing 'glob' */
void *threadFunc(void *arg)
{
	int loops = *((int *) arg);
	int loc, j;
	int s;

	s = pthread_mutex_lock(&mtx);

	for (j = 0; j < loops; j++) 
	{
		loc = glob;
		loc++;
		glob = loc;
	}

	s = pthread_mutex_unlock(&mtx);

	return NULL;
}
int main(int argc, char *argv[])
{
pthread_t t1, t2;
int loops, s;
loops =  10000000;
s = pthread_create(&t1, NULL, threadFunc, &loops);

s = pthread_create(&t2, NULL, threadFunc, &loops);

s = pthread_join(t1, NULL);

s = pthread_join(t2, NULL);

printf("glob = %d\n", glob);
return(0);
}