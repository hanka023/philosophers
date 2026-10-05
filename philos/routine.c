/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/04 23:38:46 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	before_start(t_philo *philo)
{
	// if ((philo -> id) % 2 != 0)
	// 	ft_usleep(1, philo -> data);
	// if (philo -> id == 1)
	// 	ft_usleep (2, philo -> data);
	if (philo -> data -> died == 1)
		return ;
	pthread_mutex_lock(&philo->mtx);
	(philo -> last_meal) = get_time_in_ms ();
	pthread_mutex_unlock(&philo->mtx);
}

void	finished(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtx);
	(philo -> data -> finished)++;
	pthread_mutex_unlock(&philo->mtx);
}

void	one_philo(t_philo *philo)
{
	long long	ts;

	pthread_mutex_lock(philo -> left_fork);
	ts = (get_time_in_ms() - philo -> data -> start_time);
	printf(CYAN "%lld	%d has taken a fork\n" RESET, ts, philo -> id);
	ft_usleep(philo -> data -> time_to_die, philo -> data);
	pthread_mutex_unlock(philo -> left_fork);
}

void	*routine(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	if (!philo || !philo -> data)
		return (NULL);
	before_start(philo);
	if (philo -> data -> num_of_philos == 1)
	{
		one_philo(philo);
		return (NULL);
	}
	while (1)
	{
		if ((philo->meals_eaten) >= (philo->to_eat) && (philo->to_eat) != -1)
		{
			finished(philo);
			break ;
		}
		eating (philo);
		sleeping (philo);
		thinking (philo);

		if (is_simulation_over(philo))
			break;
	}
	return (0);
}
