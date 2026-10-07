/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/07 15:02:20 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleeping(t_philo *philo)
{
	if (is_simulation_over(philo))
		return ;
	print_sleeping(philo);
	ft_usleep(philo -> data -> time_to_sleep, philo -> data);
}

void	thinking(t_philo *philo)
{
	long long	think_time;

	if (is_simulation_over(philo))
		return ;
	if (philo -> data -> num_of_philos % 2 == 0)
		return ;
	think_time = (philo->data->time_to_eat * 2) - (philo->data->time_to_sleep);
	if (think_time < 0)
		think_time = 0;
	else if (think_time > 0)
	{
		print_thinking(philo);
		ft_usleep (think_time * 0.8, philo -> data);
	}
}

void	eating(t_philo *philo)
{
	if (is_simulation_over(philo))
		return ;
	if (!lock_forks(philo))
		return ;
	pthread_mutex_lock(&philo -> mtx);
	(philo -> last_meal) = get_time_in_ms();
	pthread_mutex_unlock (&philo -> mtx);
	if (is_simulation_over(philo))
	{
		unlock_forks(philo);
		return ;
	}
	print_eating(philo);
	pthread_mutex_lock(&philo -> mtx);
	(philo -> meals_eaten)++;
	if (philo -> meals_eaten == philo -> to_eat)
		philo -> finish = 1;
	pthread_mutex_unlock(&philo -> mtx);
	ft_usleep (philo -> data -> time_to_eat, philo -> data);
	unlock_forks(philo);
}
