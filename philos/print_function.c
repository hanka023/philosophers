/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/06 15:44:13 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_died(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo -> data -> died_mutex);
	result = philo -> data -> died;
	pthread_mutex_unlock(&philo -> data -> died_mutex);
	return (result);
}

void print_fork(t_philo *philo)
{
	long long	ts;

	if (philo_died(philo))
		return;
	ts = get_time_in_ms() - philo -> data -> start_time;
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(CYAN"%lld	%d has taken a fork\n"RESET, ts, philo -> id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
}

void print_eating(t_philo *philo)
{
	long long	timestamp;

	if (philo_died(philo))
		return;
	timestamp = get_time_in_ms() - philo -> data -> start_time;
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(GREEN "%lld	%d is eating\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
}


void print_sleeping(t_philo *philo)
{
	long long	timestamp;

	if (philo_died(philo))
		return;
	timestamp = get_time_in_ms() - philo -> data -> start_time;
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(PURPLE "%lld	%d is sleeping\n" RESET, timestamp, philo -> id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
}


void print_thinking(t_philo *philo)
{
	long long	timestamp;

	if (philo_died(philo))
		return;
	timestamp = get_time_in_ms() - philo -> data -> start_time;
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(PINK "%lld	%d  is thinking\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
}

