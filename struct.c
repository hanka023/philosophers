# include "philo.h"


t_data *data_to_struct(int *arguments, int len)
{
	t_data *data;

	data = malloc (sizeof (t_data));
	if (!data)
		return (0);
	
	data -> num_of_philos = arguments[0];
	data -> time_to_die = arguments[1];
	data -> time_to_eat = arguments[2];
	data -> time_to_sleep = arguments[3];
	if (len == 5)
		data -> must_eat =  arguments[4];
	else
		data -> must_eat =  10;
	return (data);
}

t_philo *philo_to_struct( int len, t_data *data, pthread_mutex_t *forks)
{
	t_philo *philos;
	//pthread_mutex_t *forks;
	int i;
	//printf ("philo to struct jede\n");
	i = 0;
	philos = malloc(sizeof (t_philo) * len);
	if (!philos)
		return (NULL);
	//forks = mutex_init(len);
	while (i < len)
	{
		philos[i].id = i + 1;
        philos[i].left_fork = &forks[i];
        philos[i].right_fork = &forks[(i + 1) % len];
		philos[i].data = data;
		philos[i].meals_eaten = 0;
		philos[i].time_to_die = data -> time_to_die;
		philos[i].time_to_sleep = data -> time_to_sleep;
		philos[i].time_to_eat = data -> time_to_eat;
		philos[i].dead = 0;
		philos[i].num_to_eat = data -> must_eat;
		++i;	
	}
	return (philos);
}


// void mutex_to_thread(pthread_t *thread, pthread_mutex_t *mutex)
// {
	
// }

// void start_simulation(pthread_t *philos, pthread_mutex_t *mutex)
// {

	


// }