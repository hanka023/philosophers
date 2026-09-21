# include "philo.h"

void *m_routine(void *arg)  
{
	t_data		*data;
	//long long	time;
	int			i;
	int			died;
	int			count;

	i = 0;
	data = (t_data *)arg;
	//time = get_time_in_ms();
	count = data -> num_of_philos;
	printf (" ++++   +++   pocet %d +++ \n", count);
	while (1)
	{
		i = 0;
		while (i < (data -> num_of_philos))
		{
			printf ("\n--------  monitoruju philo %d --------\n", i + 1);
			died = 0;
		//	time = get_time_in_ms();
			pthread_mutex_lock(&data -> philos[i].mtx);
		//	time = get_time_in_ms();
			//printf ("* * * * * * * * * \n ");
			// printf (" \n - - - time: %lld - - -data -> philos %d.last_meal %ld - - - data -> time_to_die %ld - - - \n\n", get_time_in_ms(),i, data -> philos[i].last_meal, data -> time_to_die);
			// printf(" ((get_time_in_ms() - (data -> philos[i].last_meal)): %lld\n",  ((get_time_in_ms() - (data -> philos[i].last_meal))));
			// printf(" (data -> time_to_die)): %ld\n",  (data -> time_to_die));
			// printf(" ((get_time_in_ms() - (data -> philos[i].last_meal)) > (data -> time_to_die)): %d\n",  ((get_time_in_ms() - (data -> philos[i].last_meal)) > (data -> time_to_die)));

			if ((get_time_in_ms() - (data -> philos[i].last_meal)) > (data -> time_to_die))
			{

				(data -> philos[i].died = 1);
				data -> died = 1;
				died = 1;
				printf (" x x x x philo %d chcipnul hladem :( x x x x x %lld\n", i, get_time_in_ms());
			}
			//printf ("\n\n\n time: %lld time -   philos[i].last_meal: %ld  data -> time_to_die %ld \n\n\n", time,data -> philos[i].last_meal, data -> time_to_die);
			pthread_mutex_unlock(&data -> philos[i].mtx);
			if (died == 1)
			{
				printf ("x x x  x x x x x x philo %d chcipnul :( at time: %lld   time of last meal %ld x x x x x x break 1\n", i, get_time_in_ms(), (data -> philos[i].last_meal));
				break;
			}
			++i;
		}
		if (died == 1)
		{
			printf ("break 2\n");
			break;
		}

		ft_usleep (10);
	}
	// 	while (i < (data -> num_of_philos))
	
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