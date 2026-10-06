/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/06 15:40:20 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_simulation_over(t_philo *philo)
{
	int	died;
	int finished;

	died = 0;
	finished = 0;
	pthread_mutex_lock(&philo -> data -> died_mutex);
	died = philo -> data -> died;
	pthread_mutex_unlock(&philo -> data -> died_mutex);
	pthread_mutex_lock(&philo -> mtx);
	if ((philo -> meals_eaten) == (philo -> to_eat) && (philo->to_eat) != -1)
		finished = 1;
	pthread_mutex_unlock(&philo -> mtx);
	if ((died == 1) || (finished == 1))
		return (1);
	else 
		return (0);
}

int	is_philo_died(t_philo *philo)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&philo -> data -> died_mutex);
	result = philo -> data -> died;
	pthread_mutex_unlock(&philo -> data -> died_mutex);
	return (result);
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

void	sleeping(t_philo *philo)
{
	//long long	timestamp;
	
	if (is_simulation_over(philo))
		return;
	//timestamp = (get_time_in_ms() - philo -> data -> start_time);
	print_sleeping(philo);
	ft_usleep(philo -> data -> time_to_sleep, philo -> data);	
}

long long	t_think(t_philo *philo)
{
	long long	time_since_meal;
	long long	time_to_think;

	if (philo->data->num_of_philos % 2 == 0)
		return (0);

	time_to_think = (philo->data->time_to_eat * 2) - philo->data->time_to_sleep;
	if (time_to_think < 0)
		time_to_think = 0;

	pthread_mutex_lock(&philo->mtx);
	time_since_meal = get_time_in_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->mtx);

	if (time_to_think > (philo->data->time_to_die - time_since_meal) / 2)
		time_to_think = (philo->data->time_to_die - time_since_meal) / 2;

	if (time_to_think < 0)
		time_to_think = 0;
	return (time_to_think);
}

void	thinking(t_philo *philo)
{
	long long	time;
	long long	time_to_think;
	//long long	timestamp;

	if (is_simulation_over(philo))
		return ;
	time = get_time_in_ms();
	//timestamp = (time - (philo -> data -> start_time));
	time_to_think = t_think(philo);
	if (time_to_think > 0)
	{
		print_thinking(philo);
		ft_usleep (time_to_think, philo -> data);
	}
}

void	eating(t_philo *philo)
{

	if (is_simulation_over(philo))
		return;
	if (!lock_forks(philo))
		return;
	pthread_mutex_lock(&philo -> mtx);
	(philo -> last_meal) = get_time_in_ms();
	pthread_mutex_unlock (&philo -> mtx);

	if (is_simulation_over(philo))
    {
		unlock_forks(philo);
        return ;
    }
	//timestamp = get_time_in_ms() - philo -> data -> start_time;
	print_eating(philo);
	pthread_mutex_lock(&philo -> mtx);
	(philo -> meals_eaten)++;
	if (philo -> meals_eaten == philo -> to_eat)
		philo -> finish = 1;
	pthread_mutex_unlock (&philo -> mtx);	
	ft_usleep (philo -> data -> time_to_eat, philo -> data);
	unlock_forks(philo);
}
