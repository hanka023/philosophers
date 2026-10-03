# include "philo.h"


// int main(int argc, char *argv[])
// {

// 	t_data *data;
// 	pthread_t *philos;
// 	pthread_t monitor;
// 	t_philo		*philo;

// 	int *arguments;
// 	int len;
// 	pthread_mutex_t *forks;
// 	int num_of_phils;

// 	num_of_phils = ft_atoi (argv[1]);
// 	if (argc < 5 || argc > 6)
// 		return (0);
// 	len = argc - 1;
// 	arguments = arg_reader(argc, argv);

// 	forks = mutex_init(num_of_phils);

// 	data = data_to_struct(arguments, len, forks);

// 	philo = philo_to_struct(data, forks);


// 	philos = pthread_init (data -> num_of_philos, philo);

// 	monitor = monitoring (data);

// 	mutex_destroy(forks,num_of_phils);

// 	my_pthreads_join(philos, data -> num_of_philos);
// 	pthread_join(monitor, NULL);
// 	free(arguments);
// 	free(data -> philos);
// 	free(data);
// 	free(philos);
// 	free(philo);
// 	return (0);
// }


// void thread_func(t_data *data, t_philo *philo)
// {
// 	pthread_t *philos;
// 	pthread_t monitor;

// 	philos = pthread_init (data -> num_of_philos, philo);
// 	monitor = monitoring (data);
// 	my_pthreads_join(philos, data -> num_of_philos);
// 	pthread_join(monitor, NULL);
// 	free(philos);
// }


int main(int argc, char *argv[])
{
	t_data			*data;
	//t_philo			*philos;
	pthread_mutex_t *forks;
	int				*arguments;
	int				num_of_phils;

	num_of_phils = ft_atoi (argv[1]);
	if (argc < 5 || argc > 6)
		return (0);
	arguments = arg_reader(argc, argv);
	forks = mutex_init(num_of_phils);
	data = data_to_struct(arguments, argc - 1, forks);
	//philos = philo_to_struct(data, forks);
	thread_func (data);
	mutex_destroy(forks,num_of_phils);
	free(arguments);
	free(data -> philos);
	free(data);
	//free(philos);
	return (0);
}

