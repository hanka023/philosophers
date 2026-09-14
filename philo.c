# include "philo.h"


void *routine (void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;


	if (!philo)
    {
        printf("CHYBA: philo je NULL!\n");
        return (NULL);
    }
    if (!philo->data)
    {
        printf("CHYBA: philo->data je NULL!\n");
        return (NULL);
    }

	while (1)
	{

		if ((philo -> meals_eaten) > (philo -> data -> must_eat))
		{
			printf("philo %d is finished xxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n", philo -> id);
			break;
		}
		pthread_mutex_lock(philo -> left_fork);
		printf("philo %d has taken left fork\n", philo -> id);
		fflush(stdout);
		pthread_mutex_lock(philo -> right_fork);
		printf("philo %d has taken right fork\n", philo -> id);
		fflush(stdout);
		
		printf ("philo %d is eating\n", philo -> id);
		fflush(stdout);
		(philo -> meals_eaten) ++;
		printf ("philo %d meals eaten: %d\n", philo -> id, philo -> meals_eaten);
		fflush(stdout);
		ft_usleep(philo -> time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
	//	printf("philo %d vratil right fork\n", philo -> id);
		fflush(stdout);
        pthread_mutex_unlock(philo->left_fork);
		//printf("philo %d vratil left fork\n", philo -> id);
		fflush(stdout);
		printf ("philo %d is sleeping\n", philo -> id);
		fflush(stdout);
		ft_usleep(philo -> time_to_sleep);
		printf ("philo %d is thinking\n", philo -> id);
	}
	return (0);
}


pthread_mutex_t *mutex_init(int len)
{
	pthread_mutex_t *fork;
	int i;

	i = 0;
	fork = malloc(sizeof(pthread_mutex_t) * len);
	if (!fork)
		return (NULL);

	while (i < len)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	i = 0;
	// while (i < len)
	// {
	// 	pthread_mutex_destroy(&fork[i]);
	// 	++i;
	// }
	return (fork);
}


pthread_t *pthread_init(int len, t_philo *philos)
{
	pthread_t	*thread;
	// t_philo		*philos;
	int i;

	i = 0;
	// philos = philo_to_struct(len, data);
	thread = malloc(sizeof (pthread_t) * len);
	if (!thread)
		return (NULL);

	if (!thread)
		return (NULL);

	while (i < len)
	{
		pthread_create(&thread[i], NULL, &routine, &philos[i]);
		
		i++;
	}
	return (thread);
}

void my_pthreads_join(pthread_t *thread, int len)
{
	int i; 

	i = 0;
	while (i < len)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	return;
}
