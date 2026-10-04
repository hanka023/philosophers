/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/04 22:40:02 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*data_to_struct(int *arguments, int len, pthread_mutex_t *forks)
{
	t_data	*data;

	data = malloc (sizeof (t_data));
	if (!data)
		return (0);
	data -> num_of_philos = arguments[0];
	data -> time_to_die = arguments[1];
	data -> time_to_eat = arguments[2];
	data -> time_to_sleep = arguments[3];
	if (len == 5)
		data -> must_eat = arguments[4];
	else
		data -> must_eat = 10;
	data -> forks = forks;
	data -> finished = 0;
	data -> died = 0;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->died_mutex, NULL);
	return (data);
}

t_philo	*philo_to_struct(t_data *data, pthread_mutex_t *forks)
{
	t_philo	*philos;
	int		len;
	int		i;

	i = 0;
	len = data -> num_of_philos;
	philos = malloc(sizeof (t_philo) * len);
	if (!philos)
		return (NULL);
	while (i < len)
	{
		philos[i].id = i + 1;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % len];
		philos[i].meals_eaten = 0;
		philos[i].died = 0;
		philos[i].num_to_eat = data -> must_eat;
		philos[i].last_meal = get_time_in_ms();
		philos[i].finish = 0;
		philos[i].data = data;
		++i;
	}
	return (philos);
}
