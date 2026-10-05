#include "philo.h"


int even(t_philo *philo)
{
	long long ts;

	pthread_mutex_lock(philo -> right_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_unlock(philo -> right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(CYAN"%lld	%d has taken a fork\n"RESET, ts, philo -> id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	pthread_mutex_lock(philo -> left_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_unlock(philo -> right_fork);
		pthread_mutex_unlock(philo -> left_fork);
		return (0);
	}
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(CYAN"%lld	%d has taken a fork\n"RESET, ts, philo -> id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	return (1);
}

int odd(t_philo *philo)
{
	long long ts;

	pthread_mutex_lock(philo -> left_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_unlock(philo -> left_fork);
		return (0);
	}
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(CYAN "%lld	%d has taken a fork\n" RESET, ts, philo ->id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	pthread_mutex_lock(philo -> right_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_unlock(philo -> left_fork);
		pthread_mutex_unlock(philo -> right_fork);
		return (0);
	}
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(CYAN "%lld	%d has taken a fork\n" RESET, ts, philo ->id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	return (1);
}

int	lock_forks(t_philo *philo)
{
	int result;

	result = 0;
	if (is_simulation_over(philo))
		return 0;
	if (philo -> id % 2 == 0)
		result = even(philo);
	else
		result = odd(philo);
	return (result);
}

void unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock (philo -> right_fork);
	pthread_mutex_unlock (philo -> left_fork);
}
