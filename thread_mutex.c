# include "philo.h"


pthread_mutex_t *mutex_init(int len)
{
	pthread_mutex_t *mtx;
	int i;

	i = 0;
	mtx = malloc(sizeof(pthread_mutex_t) * len);
	if (!mtx)
		return (NULL);
	while (i < len)
	{
		pthread_mutex_init(&mtx[i], NULL);
		i++;
	}
	return (mtx);
}

pthread_t *pthread_init(int len, t_philo *philos)
{
	pthread_t	*thread;
	int i;

	i = 0;
	// philos = philo_to_struct(len, data);
	thread = malloc(sizeof (pthread_t) * len);
	if (!thread)
		return (NULL);

	while (i < len)
	{
		pthread_create(&thread[i], NULL, &routine, &philos[i]);
		
		i++;
	}
	return (thread);
}

void my_pthreads_join(pthread_t *thread, int len)
{
	int i; 

	i = 0;
	printf ("  x x x  %d x x x \n", len);
	fflush(stdout);
	while (i < len)
	{
		pthread_join(thread[i], NULL);
		printf (" thread %d join\n", i+1 );
		fflush(stdout);
		++i;
	}
	return;
}
