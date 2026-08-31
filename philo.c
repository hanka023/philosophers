# include <stdio.h>
# include <unistd.h> 
# include <pthread.h>
# include "libft/libft.h"


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

	data = malloc (sizeof (t_data));
	if (!data)
		return (0);
	
	data -> num_of_philos = arguments[0];
	data -> time_to_die = arguments[1];
	data -> time_to_eat = arguments[2];
	data -> time_to_sleep = arguments[3];
	if (len == 5)
		data -> num_of_each_must_eat =  arguments[4];
	return (data);
}

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

void *routine (void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(philo -> left_fork);
		printf("philo has taken left fork\n");
		pthread_mutex_lock(philo -> right_fork);
		printf("philo has taken right fork\n");


		pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);


	}

	return (0);
}


pthread_t *philos(int len)
{
	pthread_t *philo;
	pthread_mutex_t *fork;
	int i;

	i = 0;

	philo = malloc(sizeof (pthread_t) * len);
	fork = malloc(sizeof(pthread_mutex_t) * len);
	if (!philo || !fork)
		return (NULL);

	while (i < len)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_create(&philo[i], NULL, &routine, NULL);
		i++;
	}
	i = 0;
	while (i < len)
	{
		pthread_join(philo[i], NULL);
		pthread_mutex_destroy(&fork[i]);
		++i;
	}
	free (fork);
	return (NULL);
}




int main(int argc, char *argv[])
{
	t_data *data;
	int *arguments;
	
	if (argc < 5 || argc > 6)
		return (0);
	
	arguments = arg_reader(argc, argv);
	data = data_to_struct(arguments, argc - 1);

	print_data (data, argc - 1);

	free(arguments);
	free(data);
	return (0);
}
