# include "philo.h"

void *m_routine(void *arg)  
{
	t_data	*data;
	long long time;
	int		i;

	i = 0;
	data = (t_data *)arg;
	time = get_time_in_ms();
	// pthread_mutex_t *mtx;

	// mtx = malloc(sizeof(pthread_mutex_t) * (data -> num_of_philos));
	// if (!mtx)
	// 	return(0);

	// while (i < (data -> num_of_philos))
	// {
	// 	pthread_mutex_init(data->philos[i].mtx, NULL);
	// 	++i;
	// }

	while (1)
	{
		i = 1;
		while (i < (data -> num_of_philos))
		{
			time = get_time_in_ms();


			pthread_mutex_lock(&data -> philos[i].mtx);

			if ((time - (data -> philos[i].last_meal)) > (data -> time_to_die))
			{
				printf ("philo %d died :(\n", i);
				return (NULL);
			}

			
			pthread_mutex_unlock(&data -> philos[i].mtx);
			++i;
		}
		usleep (1000);
	}
	// 	while (i < (data -> num_of_philos))
	// {
	// 	pthread_mutex_destroy(&data->philos[i].mtx);
	// 	++i;
	// }  
	
	return (NULL);
}


pthread_t monitoring (t_data *data)
{
	pthread_t	monitor;
	

	pthread_mutex_t *mtx;
	mtx = &data -> philos -> mtx;

	pthread_mutex_init(mtx, NULL);

	if (pthread_create(&monitor, NULL, m_routine, data) != 0)
		return (0);

//	pthread_mutex_destroy(mtx);
	return(monitor);
}