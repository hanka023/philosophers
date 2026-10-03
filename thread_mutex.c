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

int mutex_destroy(pthread_mutex_t *mtx, int len)
{
	int i;
	int s;

	i = 0;
	s = 0;
	while (i < len)
	{
		s = pthread_mutex_destroy(&mtx[i]);
		if (s != 0)
			printf ("error mutex destroy \n");
		i++;
	}
	free (mtx);
	return (0);
}

pthread_t *pthread_init(int len, t_philo *philos)
{
	pthread_t	*threads;
	int 		i;

	i = 0;
	threads = malloc(sizeof (pthread_t) * len);
	if (!threads)
		return (NULL);
	while (i < len)
	{
		pthread_create(&threads[i], NULL, &routine, &philos[i]);
		i++;
	}
	return (threads);
}

void my_pthreads_join(pthread_t *thread, int len)
{
	int i; 

	i = 0;
	while (i < len)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	return;
}

void thread_func(t_data *data, t_philo *philo)
{
	pthread_t *threads;
	pthread_t monitor;

	threads = pthread_init(data -> num_of_philos, philo);
	monitor = monitoring (data);
	my_pthreads_join(threads, data -> num_of_philos);
	pthread_join(monitor, NULL);
	free(threads);
}


