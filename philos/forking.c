/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/07 14:21:12 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo -> left_fork);
	pthread_mutex_unlock(philo -> right_fork);
}

int	even(t_philo *philo)
{
	pthread_mutex_lock(philo -> right_fork);
	print_fork(philo);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_unlock(philo -> right_fork);
		return (0);
	}
	pthread_mutex_lock(philo -> left_fork);
	print_fork(philo);
	if (is_simulation_over(philo) == 1)
	{
		unlock_forks(philo);
		return (0);
	}
	return (1);
}

int	odd(t_philo *philo)
{
	pthread_mutex_lock(philo -> left_fork);
	print_fork(philo);
	if (is_simulation_over(philo) == 1)
	{
		pthread_mutex_unlock(philo -> left_fork);
		return (0);
	}
	pthread_mutex_lock(philo -> right_fork);
	print_fork(philo);
	if (is_simulation_over(philo) == 1)
	{
		unlock_forks(philo);
		return (0);
	}
	return (1);
}

int	lock_forks(t_philo *philo)
{
	int	result;

	result = 0;
	if (is_simulation_over(philo))
		return (0);
	if (philo -> id % 2 == 0)
		result = even(philo);
	else
		result = odd(philo);
	return (result);
}
