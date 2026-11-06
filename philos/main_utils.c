/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
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

int	ft_isalldigit(char *c)
{
	int i;

	i = 0;
	while ((*c == ' ') || (*c >= 9 && *c <= 13))
		++c;
	if (*c == '+')
		++c;
	while (*c)
	{
		if (*c >= 48 && *c <= 57)
		{
			++c;
			i = 1;
		}	
		else
			return (0);
	}
	return (i);
}

int check_args(int argc, char **argv)
{
	int	i;

	if (!argv || argc < 4)
		return (0);
	i = 1;
	while (i < (argc))
	{
		if (!ft_isalldigit(argv[i]))
			return (0);
		++i;
	}
	return (i);
}
