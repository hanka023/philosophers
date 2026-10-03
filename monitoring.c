# include "philo.h"

void *m_routine(void *arg)  
{
	t_data		*data;
	int			i;
	int			died;
	int			count;
	long long	last;
	int finished;
	

	i = 0;
	died = 0;
	data = (t_data *)arg;
	count = data -> num_of_philos;
	finished = 0;

	printf (" ++++ monitoring jedee   +++   pocet filosofu [%d] +++ \n", count);
	ft_usleep (1);
	while (1)
	{
		i = 0;
		while (i < (data -> num_of_philos))
		{
			pthread_mutex_lock(&data -> philos[i].mtx);
			last = data -> philos[i].last_meal;
			finished = data -> finished;
			long long time = get_time_in_ms();
			pthread_mutex_unlock(&data -> philos[i].mtx);
			printf (" * * * time[%lld]\n", time);
			if ((data -> philos[i].meals_eaten) == (data -> must_eat))
			{
				printf (" x x philo %d se nazral a konci  x x\n", i + 1);
				finished++;
			}
			else if ((data -> philos[i].finish == 0) && (get_time_in_ms() - last) > (data -> time_to_die))
			{
				(data -> philos[i].died = 1);
				data -> died = 1;
				died = 1;
				//printf (" x x philo %d chcipnul hladem :( x  bez jidla[%lld] last_meal[%lld] aktualni cas [%lld]\n", i + 1, (get_time_in_ms() - (last)),last,  get_time_in_ms());
				//printf ( "* * * * * * * * * finished [%d]\n",finished);
			}

			++i;
			if (data -> died == 1)
				printf ( " + + + + + +  chcipli hladem + +\n");

		}
		
		if (finished >= data -> num_of_philos)
		{
			printf (" vsichni dojedli !!!!!!\n");
			break;
		}
		else if (died == 1)
			break;
		ft_usleep (10);
	}

	return (NULL);
}
