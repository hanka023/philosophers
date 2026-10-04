/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/04 23:15:10 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo -> data -> died_mutex);
	result = philo -> data -> died;
	pthread_mutex_unlock(&philo -> data -> died_mutex);
	return (result);
}


void	sleeping(t_philo *philo)
{
	long long	timestamp;
	
	if (is_simulation_over(philo))
		return ;

	timestamp = (get_time_in_ms() - philo -> data -> start_time);
	printf(PURPLE "%lld	%d  is sleeping\n" RESET, timestamp, philo -> id);
	ft_usleep(philo -> data -> time_to_sleep, philo -> data);
}


void	thinking(t_philo *philo)
{
	long long	time;
	long long	time_to_think;
	long long	timestamp;
	long long	time_since_last_meal;


	if (is_simulation_over(philo))
		return ;
	time = get_time_in_ms();
	timestamp = (time - (philo -> data -> start_time));
	pthread_mutex_lock(&philo->mtx);
	time_since_last_meal = time - philo -> last_meal;
	pthread_mutex_unlock(&philo->mtx);
	time_to_think = (philo -> data -> time_to_die - time_since_last_meal) / 2;
	if (time_to_think > 200)
	{
		printf(PINK "%lld	%d  is thinking\n" RESET, timestamp, philo->id);
		ft_usleep (100, philo -> data);
	}
	else if (time_to_think > 10)
	{
		printf(PINK "%lld	%d  is thinking\n" RESET, timestamp, philo->id);
		ft_usleep(time_to_think, philo -> data);
	}
}

void	eating(t_philo *philo)
{
	long long	timestamp;

	if (is_simulation_over(philo))
		return;
	
	//printf (" [%d] [%d] philo chcipl\n", is_simulation_over(philo), philo -> id);

	lock_forks(philo);
	pthread_mutex_lock(&philo -> mtx);
	(philo -> last_meal) = get_time_in_ms();
	timestamp = get_time_in_ms() - philo -> data -> start_time;
	printf(GREEN "%lld	%d is eating\n" RESET, timestamp, philo->id);
	(philo -> meals_eaten)++;
	if (philo -> meals_eaten == philo -> num_to_eat)
		philo -> finish = 1;
	pthread_mutex_unlock (&philo -> mtx);
	ft_usleep (philo -> data -> time_to_eat, philo -> data);
	pthread_mutex_unlock (philo -> right_fork);
	pthread_mutex_unlock (philo -> left_fork);
}
