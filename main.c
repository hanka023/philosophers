# include "philo.h"


int main(int argc, char *argv[])
{

	t_data *data;
	pthread_t *philos;

	t_philo		*phil;
	//pthread_mutex_t	*mutex;
	int *arguments;
	int len;
	pthread_mutex_t *forks;
	int num_of_phils;

	num_of_phils = ft_atoi (argv[1]);
	//printf ("main jede\n");
	fflush(stdout);

	if (argc < 5 || argc > 6)
		return (0);
	len = argc - 1;
	arguments = arg_reader(argc, argv);
	//printf ("main  stale jede\n");
	fflush(stdout);

	forks = mutex_init(num_of_phils);

	data = data_to_struct(arguments, len, forks);
	
	phil = philo_to_struct(data, forks);
	// while (1)
	// {
		
		philos = pthread_init (data -> num_of_philos, phil);
		monitoring (data);
	
	//}

	printf (" x x x x x x x x x x \n\n\n");
	//ft_usleep(100);
	
	//mutex = mutex_init(len);
	//print_data (data, len);
	//mutex_to_thread(philos, mutex);
	//start_simulation (philos, mutex);
	//pthread_join(monitor, NULL);
	my_pthreads_join(philos, data -> num_of_philos);
	free(arguments);
	free(data -> philos);
	free(data);
	free(philos);
	free(phil);
	free(forks);
	return (0);
}
