/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/07 14:59:53 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_philo *philo)
{
	int	died;
	int	finished;

	died = 0;
	finished = 0;
	pthread_mutex_lock(&philo -> data -> died_mutex);
	died = philo -> data -> died;
	pthread_mutex_unlock(&philo -> data -> died_mutex);
	if (died == 1)
		return (1);
	pthread_mutex_lock(&philo -> mtx);
	if ((philo -> meals_eaten) == (philo -> to_eat) && (philo->to_eat) != -1)
		finished = 1;
	pthread_mutex_unlock(&philo -> mtx);
	if (finished == 1)
		return (1);
	else
		return (0);
}

int	simulation_over(t_data *data)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&data -> died_mutex);
	result = data -> died;
	pthread_mutex_unlock(&data -> died_mutex);
	return (result);
}

int	philo_died(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo -> data -> died_mutex);
	result = philo -> data -> died;
	pthread_mutex_unlock(&philo -> data -> died_mutex);
	return (result);
}
