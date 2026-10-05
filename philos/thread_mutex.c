/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_mutex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/04 22:41:05 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*mutex_init(int len)
{
	pthread_mutex_t	*forks;
	int				i;

	i = 0;
	forks = malloc(sizeof(pthread_mutex_t) * len);
	if (!forks)
		return (NULL);
	while (i < len)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}

int	mutex_destroy(pthread_mutex_t *mtx, int len, t_data *data)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (i < len)
	{
		s = pthread_mutex_destroy(&mtx[i]);
		if (s != 0)
			printf ("error mutex destroy mtx[%d]\n", i);
		i++;
	}
	free (mtx);
	s = pthread_mutex_destroy(&data->print_mutex);
	if (s != 0)
		printf ("error mutex destroy printf_mutex\n");
    s = pthread_mutex_destroy(&data->died_mutex);
	if (s != 0)
		printf ("error mutex destroy dead_mutex\n");
	return (0);
}

pthread_t	*pthread_init(int len, t_philo *philos)
{
	pthread_t	*threads;
	int			i;

	i = 0;
	threads = malloc(sizeof (pthread_t) * len);
	if (!threads)
		return (NULL);
	while (i < len)
	{
		pthread_create(&threads[i], NULL, &routine, &philos[i]);
		i++;
	}
	return (threads);
}

void	my_pthreads_join(pthread_t *thread, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		pthread_join(thread[i], NULL);
		++i;
	}
	return ;
}

void	thread_func(t_data *data)
{
	pthread_t	*threads;
	pthread_t	monitor;

	threads = pthread_init(data -> num_of_philos, data -> philos);
	monitor = monitoring (data);
	my_pthreads_join(threads, data -> num_of_philos);
	pthread_join(monitor, NULL);
	free(threads);
}
