/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:16:10 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/05 15:11:25 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av, int ac)
{
	int		num_philos;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	num_times_eat;

	if (is_valid(ac, av))
		return (1);
	num_philos = ft_atoi(av[1]);
	time_to_die = ft_atoilong(av[2]);
	time_to_eat = ft_atoilong(av[3]);
	time_to_sleep = ft_atoilong(av[4]);
	if (num_philos <= 0 || num_philos > 200)
		return (1);
	if (time_to_die < 60 || time_to_eat < 60 || time_to_sleep < 60)
		return (1);
	if (ac == 6)
	{
		num_times_eat = ft_atoi(av[5]);
		if (num_times_eat <= 0)
			return (1);
	}
	return (0);
}

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	is_valid(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (!is_valid_number(av[i]))
			return (1);
		i++;
	}
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
