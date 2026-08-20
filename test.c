#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>


void *funkce(void *arg)
{
	printf ("neco");

}

int main()
{
   pthread_t t1;
   int i = 1;

   pthread_create(&t1, NULL, funkce, &i);

   pthread_join(t1, NULL);
   return (0);
}