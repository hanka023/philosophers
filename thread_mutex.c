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




// int monitoring (t_data *data)
// {
// 	pthread_t	monitor;
// 	int m;

// 	pthread_mutex_t *mtx;
// 	mtx = &data -> philos -> mtx;

// 	pthread_mutex_init(mtx, NULL);

// 	m = pthread_create(&monitor, NULL, m_routine, data);
// 	if (m != 0)
// 		return (0);
// 	// pthread_join(monitor, NULL);

// //	pthread_mutex_destroy(mtx);
// 	return(0);
// }



// pthread_t *pthread_init(int len, t_philo *philos)
// {
// 	pthread_t	*thread;

// 	int i;

// 	i = 0;
// 	// philos = philo_to_struct(len, data);
// 	thread = malloc(sizeof (pthread_t) * len);
// 	if (!thread)
// 		return (NULL);

// 	while (i < len)
// 	{
// 		pthread_create(&thread[i], NULL, &routine, &philos[i]);
// 		//printf (" + + + + + + + + +  spoustim vlakno [%d] \n", i);
		
// 		i++;
// 	}
// 	return (thread);
// }



pthread_t monitoring (t_data *data)
{
	pthread_t	monitor;
	int m;

	pthread_mutex_t *mtx;
	mtx = &data -> philos -> mtx;

	pthread_mutex_init(mtx, NULL);

	m = pthread_create(&monitor, NULL, m_routine, data);
	if (m != 0)
		return (0);
	// pthread_join(monitor, NULL);

//	pthread_mutex_destroy(mtx);
	return(monitor);
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
		//printf (" + + + + + + + + +  spoustim vlakno [%d] \n", i);
		
		i++;
	}
	return (thread);
}




void my_pthreads_join(pthread_t *thread, int len)
{
	int i; 

	i = 0;
	// printf ("  x x x  %d x x x \n", len);
	// fflush(stdout);
	while (i < len)
	{
		pthread_join(thread[i], NULL);
		printf (" thread %d join\n", i+1 );
		fflush(stdout);
		++i;
	}
	return;
}
