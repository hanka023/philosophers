#include "philo.h"

void even(t_philo *philo)
{
	long long ts;

	pthread_mutex_lock(philo -> right_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_lock(philo -> left_fork);
		return;
	}
	printf(CYAN"%lld	%d has taken a fork\n"RESET, ts, philo -> id);
	pthread_mutex_lock(philo -> left_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
		return ;
	printf(CYAN"%lld	%d has taken a fork\n"RESET, ts, philo -> id);
}

void odd(t_philo *philo)
{
	long long ts;

	pthread_mutex_lock(philo -> left_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_lock(philo -> right_fork);
		return;
	}
	printf(CYAN "%lld	%d has taken a fork\n" RESET, ts, philo ->id);
	pthread_mutex_lock(philo -> right_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	if (is_simulation_over(philo) == 1)
		return ;
	printf(CYAN "%lld	%d has taken a fork\n" RESET, ts, philo ->id);
}

void	lock_forks(t_philo *philo)
{
	
	if (is_simulation_over(philo))
		return;
	if (philo -> id % 2 == 0)
		even(philo);
	else
		odd(philo);
}