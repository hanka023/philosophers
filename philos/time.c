/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/04 23:05:48 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

void	ft_usleep(long long time_in_ms, t_data *data)
{
	long long	start_time;

	start_time = get_time_in_ms();
	while ((get_time_in_ms() - start_time) < (long long) time_in_ms)
	{
		usleep(100);
		if (data -> died == 1)
			return ;
	}
}

long long	count_time_to_think(t_philo *philo)
{
	long long	time_to_think;
	long long	rest;

	rest = get_time_in_ms() - philo -> last_meal - philo -> data->time_to_eat;
	time_to_think = (philo -> data->time_to_die - rest) / 2;
	if (time_to_think < 1)
		time_to_think = 0;
	if (time_to_think > 1000)
		time_to_think = 200;
	return (time_to_think);
}
