# include "philo.h"
#include <stdio.h>

long long count_time_to_think(t_philo *philo)
{
	long long time_to_think;
	long long rest;

	rest = get_time_in_ms() - philo->last_meal - philo->data->time_to_eat;
	time_to_think = (philo->data->time_to_die - rest) / 2;
		if (time_to_think < 1)
		    time_to_think = 0;
		if (time_to_think > 1000)
		    time_to_think = 200;
	return (time_to_think);
}

void before_start(t_philo *philo)
{
	if ((philo -> id) %2 != 0)
		ft_usleep(1);
	if (philo -> id == 1)
		ft_usleep (2);
	pthread_mutex_lock(&philo->mtx);
	(philo -> last_meal) = get_time_in_ms ();
	pthread_mutex_unlock(&philo->mtx);
	philo->data->start_time =  get_time_in_ms();
}

void finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx);
	(philo->data->finished) ++;
	pthread_mutex_unlock(&philo->mtx);
}

void one_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
   	printf(CYAN "%d has taken a left fork\n" RESET,philo ->id);
	ft_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(philo->left_fork);
}

void lock_forks(t_philo *philo)
{
	long long timestamp;

	if (philo -> id %2 == 0)
	{	
		pthread_mutex_lock(philo -> right_fork);
		timestamp = (get_time_in_ms() - philo->data->start_time);
		printf(CYAN "%lld	%d has taken a right fork\n" RESET,timestamp, philo ->id);
		printf(CYAN "%d has taken a right fork\n" RESET,philo ->id);
		pthread_mutex_lock(philo -> left_fork);
		timestamp = (get_time_in_ms() - philo->data->start_time);
		printf(CYAN "%lld	%d has taken a left fork\n" RESET,timestamp, philo ->id);
		
	}
	else
	{
		pthread_mutex_lock(philo -> left_fork);
		timestamp = (get_time_in_ms() - philo->data->start_time);
		printf(CYAN "%lld	%d has taken a left fork\n" RESET,timestamp, philo ->id);
		pthread_mutex_lock(philo -> right_fork);
		timestamp = (get_time_in_ms() - philo->data->start_time);
		printf(CYAN "%lld	%d has taken a right fork\n" RESET,timestamp, philo ->id);
	}
}

void *routine (void *arg)
{
	t_philo		*philo;
	long long	time_to_think;
	long long	remaining;
	long long	timestamp; 

	philo = (t_philo *)arg;
	if (!philo || !philo->data)
        return (NULL);
	if (philo->data->num_of_philos == 1)
    {
		one_philo(philo);
        return(NULL) ;
    }
	before_start(philo);
	
	timestamp = get_time_in_ms() - philo->data->start_time;
	while (1)
	{
		if ((philo -> meals_eaten) >= (philo -> num_to_eat))
		{
			finished(philo);
			break;
		}
		if (philo -> data -> died == 1)
			break;

		lock_forks(philo);
		pthread_mutex_lock(&philo->mtx);
	
		(philo -> last_meal) = get_time_in_ms();
		timestamp = get_time_in_ms() - philo->data->start_time;
		printf(GREEN "%lld	%d is eating\n" RESET, timestamp, philo->id);
		remaining = philo->data->time_to_die - (get_time_in_ms() - philo->last_meal);
		(philo -> meals_eaten) ++;
		if (philo -> meals_eaten == philo -> num_to_eat)
			philo -> finish = 1;
		
		pthread_mutex_unlock(&philo->mtx);
		
		ft_usleep(philo -> data -> time_to_eat);
		pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
		if (philo -> data -> died == 1)
			break;
		ft_usleep(philo ->data-> time_to_sleep);
		remaining = philo->data->time_to_die - (get_time_in_ms() - philo->last_meal);

		time_to_think = remaining / 2;
	
		if (remaining > 200 )
			ft_usleep (25);
		else if (remaining > 10)
			ft_usleep(time_to_think);
	}
	return (0);
}


