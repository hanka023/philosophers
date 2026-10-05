/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/05 18:14:15 by haskalov         ###   ########.fr       */
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
	long long	timestamp;
	
	if (is_simulation_over(philo))
		return;
	timestamp = (get_time_in_ms() - philo -> data -> start_time);
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(PURPLE "%lld	%d is sleeping\n" RESET, timestamp, philo -> id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
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
	long long	timestamp;

	if (is_simulation_over(philo))
		return ;
	time = get_time_in_ms();
	timestamp = (time - (philo -> data -> start_time));
	time_to_think = t_think(philo);
	if (time_to_think > 0)
	{
		pthread_mutex_lock(&philo -> data -> print_mutex);
		printf(PINK "%lld	%d  is thinking\n" RESET, timestamp, philo->id);
		pthread_mutex_unlock(&philo -> data -> print_mutex);
		ft_usleep (time_to_think, philo -> data);
	}
}

void	eating(t_philo *philo)
{
	long long	timestamp;

	if (is_simulation_over(philo))
		return;
	if (!lock_forks(philo))
		return;
	pthread_mutex_lock(&philo -> mtx);
	(philo -> last_meal) = get_time_in_ms();
	pthread_mutex_unlock (&philo -> mtx);
	timestamp = get_time_in_ms() - philo -> data -> start_time;
	if (is_simulation_over(philo))
    {
		unlock_forks(philo);
        return ;
    }
	pthread_mutex_lock(&philo -> data -> print_mutex);
	printf(GREEN "%lld	%d is eating\n" RESET, timestamp, philo->id);
	pthread_mutex_unlock(&philo -> data -> print_mutex);
	pthread_mutex_lock(&philo -> mtx);
	(philo -> meals_eaten)++;
	if (philo -> meals_eaten == philo -> to_eat)
		philo -> finish = 1;
	pthread_mutex_unlock (&philo -> mtx);	
	ft_usleep (philo -> data -> time_to_eat, philo -> data);
	unlock_forks(philo);
}
