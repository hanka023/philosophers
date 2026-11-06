/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: haskalov <haskalov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 13:37:42 by haskalov          #+#    #+#             */
/*   Updated: 2026/10/07 15:31:24 by haskalov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data			*data;
	pthread_mutex_t	*forks;
	int				*arguments;
	int				num_of_phils;

	if (argc < 5 || argc > 6)
		return (0);
	if (!check_args(argc, argv))
		return (0);
	num_of_phils = ft_atoi (argv[1]);
	arguments = arg_reader(argc, argv);
	forks = mutex_init(num_of_phils);
	data = data_to_struct(arguments, argc - 1, forks);
	data -> philos = philo_to_struct(data, forks);
	thread_func (data);
	mutex_destroy (forks, num_of_phils, data);
	free (arguments);
	free (data -> philos);
	free (data);
	return (0);
}
