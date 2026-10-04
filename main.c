# include "philo.h"

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
	thread_func (data);
	mutex_destroy(forks,num_of_phils);
	free(arguments);
	free(data -> philos);
	free(data);
	return (0);
}

