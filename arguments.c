# include "philo.h"

// t_data *data_to_struct(int *arguments, int len)
// {
// 	t_data *data;

// 	data = malloc (sizeof (t_data));
// 	if (!data)
// 		return (0);
	
// 	data -> num_of_philos = arguments[0];
// 	data -> time_to_die = arguments[1];
// 	data -> time_to_eat = arguments[2];
// 	data -> time_to_sleep = arguments[3];
// 	if (len == 5)
// 		data -> num_of_each_must_eat =  arguments[4];
// 	return (data);
// }

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
	printf ("time to die	%d\n",data -> time_to_die);
	printf ("time to eat	%d\n",data -> time_to_eat);
	printf ("time to sleep	%d\n",data -> time_to_sleep);
	
	if ((len == 5))
		printf("n each must eat %d\n",data -> num_of_each_must_eat);
	return ;

}