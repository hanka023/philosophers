# include "philo.h"

void *m_routine(void *arg)  
{
	t_data		*data;
	int			i;
	long long	last;
	int			finished;

	data = (t_data *)arg;


	
	while (1)
	{
		i = 0;
		finished = 0;
		while (i < (data -> num_of_philos))
		{
			printf("MONITOR philo %d address: %p\n", data->philos[i].id, (void *)&data->philos[i]);
			pthread_mutex_lock(&data -> philos[i].mtx);
			last = data -> philos[i].last_meal;
			//printf (YELLOW" * * * * * philo %d meals eaten %d  time [%lld]\n"RESET, data ->philos[i].id, data -> philos[i].meals_eaten, get_time_in_ms());
			pthread_mutex_unlock(&data -> philos[i].mtx);
			if ((data -> philos[i].meals_eaten) == (data -> must_eat))
			{
				data->philos[i].finish = 1;
				finished++;
				printf ( CYAN "%d is finished\n" RESET, i + 1);
			}
				
			else if ((data->philos[i].finish == 0) && (get_time_in_ms()-last) > (data->time_to_die))
			{
				(data -> philos[i].died = 1);
				data -> died = 1;
				printf ( RED "%d is died\n" RESET, i + 1);
				break;
			}
			++i;
		}
		if (finished >= (data -> num_of_philos) ||  (data -> died == 1))
		{
			data->died = 1;
			break;
		}
		ft_usleep (10);
	}
	return (NULL);
}

pthread_t monitoring (t_data *data)
{
	pthread_t	monitor;
	int 		m;

	pthread_mutex_t *mtx;
	mtx = &data -> philos -> mtx;
	pthread_mutex_init(mtx, NULL);
	m = pthread_create(&monitor, NULL, m_routine, data);
	if (m != 0)
		return (0);
	return(monitor);
}