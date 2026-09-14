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

	printf ("main jede\n");
	fflush(stdout);

	if (argc < 5 || argc > 6)
		return (0);
	len = argc - 1;
	arguments = arg_reader(argc, argv);
	printf ("main  stale jede\n");
	fflush(stdout);
	data = data_to_struct(arguments, len);
	printf ("main  stale jede  - po data to struct\n ");
	fflush(stdout);
	forks = mutex_init(len);
	phil = philo_to_struct(len, data, forks);
	philos = pthread_init (len, phil);
	//mutex = mutex_init(len);
	printf ("main  stale jede  - po pth inint\n");
	fflush(stdout);
	print_data (data, len);
	//mutex_to_thread(philos, mutex);
	//start_simulation (philos, mutex);

	my_pthreads_join(philos, len);
	free(arguments);
	free(data);
	free(philos);
	free(phil);
	free(forks);
	return (0);
}
