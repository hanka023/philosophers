# include "philo.h"

void *m_routine(void *arg)  
{
	t_data		*data;
	int			i;
	int			died;
	int			count;

	i = 0;
	died = 0;
	data = (t_data *)arg;
	count = data -> num_of_philos;
	printf (" ++++   +++   pocet filosofu [%d] +++ \n", count);
	while (1)
	{
		i = 0;
		while (i < (data -> num_of_philos))
		{
			died = 0;
			pthread_mutex_lock(&data -> philos[i].mtx);
			if ((get_time_in_ms() - (data -> philos[i].last_meal)) > (data -> time_to_die))
			{

				(data -> philos[i].died = 1);
				data -> died = 1;
				died = 1;
				printf (" x x philo %d chcipnul hladem :( x  bez jidla[%lld]  cas [%lld]\n", i, (get_time_in_ms() - (data -> philos[i].last_meal)), get_time_in_ms());
			}
			pthread_mutex_unlock(&data -> philos[i].mtx);
			++i;
		}
		if (died == 1)
			break;
		ft_usleep (10);
	}
	return (NULL);
}

int monitoring (t_data *data)
{
	pthread_t	monitor;
	int m;

	pthread_mutex_t *mtx;
	mtx = &data -> philos -> mtx;

	pthread_mutex_init(mtx, NULL);

	m = pthread_create(&monitor, NULL, m_routine, data);
	if (m != 0)
		return (0);
	pthread_join(monitor, NULL);

//	pthread_mutex_destroy(mtx);
	return(0);
}