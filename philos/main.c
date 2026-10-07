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

int	*arg_reader(int argc, char **argv)
{
	int	i;
	int	*arguments;

	if (!argv || argc < 4)
		return (0);
	i = 0;
	arguments = malloc (sizeof(int) * (argc - 1));
	if (!arguments)
		return (NULL);
	while (i < (argc - 1))
	{
		arguments[i] = ft_atoi(argv[i + 1]);
		++i;
	}
	return (arguments);
}

int	main(int argc, char *argv[])
{
	t_data			*data;
	pthread_mutex_t	*forks;
	int				*arguments;
	int				num_of_phils;

	num_of_phils = ft_atoi (argv[1]);
	if (argc < 5 || argc > 6)
		return (0);
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
