#include <stdio.h>
#include <unistd.h> 
#include <pthread.h>
#include "libft/libft.h"


typedef struct s_philo{
int 			id;
pthread_t 		thread;
int				meals_eaten;
size_t			last_meal;
size_t			time_to_die;
size_t			time_to_eat;
size_t			time_to_sleep;
int				num_times_to_eat;
int				*dead;
pthread_mutex_t	*left_fork;
pthread_mutex_t	*right_fork;
pthread_mutex_t	*write_lock;
} t_philo;

typedef struct s_data{
	int num_of_philos;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int num_of_each_must_eat;

}t_data;



t_data *data_to_struct(int *arguments, int len)
{
	t_data *data;

	data = NULL;
	data -> num_of_philos = arguments[0];
	data -> time_to_die = arguments[1];
	data -> time_to_eat = arguments[2];
	data -> time_to_sleep = arguments[3];
	if ((len == 5) && arguments[4])
		data -> num_of_each_must_eat =  arguments[4];
	return (data);
}

t_data *arg_reader(int argc, char **argv, int *arguments)
{
	if (!argv || argc < 4)
		return (0);
	
	t_data *data;
	int i;

	i = 0;
	while (i < (argc - 1))
	{
		arguments[i] = ft_atoi(argv[i + 1]);
		++i;
	}
	data = data_to_struct(arguments, argc - 1);
	return (data);
}


int main(int argc, char *argv[])
{
	t_data *data;
	int *arguments;
	
	if (argc < 5 || argc > 6)
		return (0);

	arguments = malloc(sizeof (int) * (argc - 1));
	if (!arguments)
		return (1);
	data = arg_reader(argc, argv, arguments);

	printf ("num of philos %d\n",data -> num_of_philos);

	free(arguments);
	return (0);
}
