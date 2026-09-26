#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>


void *funkce(void *arg)
{
	
	int *id = (int *)arg;

	if (*id == 1)
		printf ("neco\n");
	else if (*id == 2)
		printf ("&id 2\n");
	return (NULL);
}

int main()
{
	pthread_t t1;
	pthread_t t2;
	int i = 1;
	int j = 2;
	
	pthread_create(&t1, NULL, funkce, &i);
  	pthread_create(&t2, NULL, funkce, &j);

	pthread_join(t1, NULL);
 	pthread_join(t2, NULL);

	return (0);
}