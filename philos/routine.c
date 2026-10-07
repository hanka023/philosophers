/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/07 14:24:07 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	before_start(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx);
	(philo -> last_meal) = get_time_in_ms ();
	pthread_mutex_unlock(&philo->mtx);
}

void	one_philo(t_philo *philo)
{
	long long	timestamp;

	if (is_simulation_over(philo))
		return ;
	timestamp = (get_time_in_ms() - (philo -> data -> start_time));
	pthread_mutex_lock(philo -> left_fork);
	print_fork(philo);
	pthread_mutex_unlock(philo -> left_fork);
	ft_usleep(philo -> data -> time_to_die, philo -> data);
	timestamp = (get_time_in_ms() - (philo -> data -> start_time));
	print_death(philo -> data, 0, timestamp);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (!philo || !philo -> data || is_simulation_over(philo))
		return (NULL);
	before_start(philo);
	if (philo -> data -> num_of_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		eating (philo);
		sleeping (philo);
		thinking (philo);
		if (is_simulation_over(philo))
			break ;
	}
	return (NULL);
}
