# include "philo.h"


int *arg_reader(int argc, char **argv)
{
	if (!argv || argc < 4)
		return (0);

	int i;
	int *arguments;

	i = 0;
	arguments = malloc (sizeof(int) * (argc - 1));
	if (!arguments)
		return (NULL);
	while (i < (argc - 1))
	{
		arguments[i] = ft_atoi(argv[i + 1]);
		++i;
	}
	return (arguments);
}

void print_data(t_data *data, int len)
{
	printf ("num of philos	%d\n",data -> num_of_philos);
	printf ("time to die	%lld\n",data -> time_to_die);
	printf ("time to eat	%ld\n",data -> time_to_eat);
	printf ("time to sleep	%ld\n",data -> time_to_sleep);
	
	if ((len == 5))
		printf("n each must eat %d\n",data -> must_eat);
	return ;

}