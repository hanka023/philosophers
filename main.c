# include "philo.h"


int main(int argc, char *argv[])
{

	t_data *data;
	pthread_t *philos;
	//pthread_t monitor;
	t_philo		*philo;
	//pthread_mutex_t	*mutex;
	int *arguments;
	int len;
	pthread_mutex_t *forks;
	int num_of_phils;

	num_of_phils = ft_atoi (argv[1]);
	fflush(stdout);

	if (argc < 5 || argc > 6)
		return (0);
	len = argc - 1;
	arguments = arg_reader(argc, argv);
	
	forks = mutex_init(num_of_phils);

	data = data_to_struct(arguments, len, forks);
	
	philo = philo_to_struct(data, forks);
	
	//v teto funkci spoustim vlakna !!!!!!!!!	

	//monitor = monitoring (data);
	philos = pthread_init (data -> num_of_philos, philo);
	
	
	printf (" x x x x x x x x x x \n\n\n");
	
	mutex_destroy(forks,num_of_phils);

	my_pthreads_join(philos, data -> num_of_philos);
	//pthread_join(monitor, NULL);
	free(arguments);
	free(data -> philos);
	free(data);
	free(philos);
	free(philo);
	//free(forks);
	return (0);
}
