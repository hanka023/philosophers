/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/05 18:18:00 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_death(t_data *data, int i, long long timestamp)
{
	if (!is_simulation_over(&data -> philos[i]))
	{
		pthread_mutex_lock(&data->died_mutex);
		data -> died = 1;
		pthread_mutex_unlock(&data->died_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf(RED "%lld	%d died\n" RESET, timestamp, i + 1);
		pthread_mutex_unlock(&data->print_mutex);
	}
}

int	died(t_data *data, int i)
{
	long long	time;
	long long	timestamp;
	long long	last;

	time = get_time_in_ms();
	pthread_mutex_lock(&data -> philos[i].mtx);
	last = data -> philos[i].last_meal;
	pthread_mutex_unlock(&data -> philos[i].mtx);
	if ((data->philos[i].finish == 0) && (time - last) > (data->time_to_die))
	{
		pthread_mutex_lock(&data->died_mutex);
		(data -> philos[i].died = 1);
		pthread_mutex_unlock(&data->died_mutex);
		timestamp = (get_time_in_ms() - (data -> start_time));
		print_death(data, i, timestamp);
		return (1);
	}
	else
		return (0);
}

void	*m_routine(void *arg)
{
	t_data		*data;
	int			i;
	int			finished;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		finished = 0;
		while (i < (data -> num_of_philos))
		{
			pthread_mutex_lock(&data->philos[i].mtx);
			if ((data -> philos[i].meals_eaten) == (data -> must_eat))
				finished++;
			pthread_mutex_unlock(&data->philos[i].mtx);
			if (died (data, i) == 1)
				break ;
			++i;
		}
		if (finished >= (data -> num_of_philos) || simulation_over(data))
			break ;
		ft_usleep (1, data);
	}
	return (NULL);
}

pthread_t	monitoring(t_data *data)
{
	pthread_t	monitor;
	int			m;

	m = pthread_create(&monitor, NULL, m_routine, data);
	if (m != 0)
		return (0);
	return (monitor);
}
