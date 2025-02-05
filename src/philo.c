/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rabu-shr <rabu-shr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 13:34:26 by rabu-shr          #+#    #+#             */
/*   Updated: 2025/02/05 16:05:59 by rabu-shr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	one_philo(t_philo *philo)
{
	philo->data->is_dead = 1;
	is_dead(philo);
	return (1);
}

int	main(int ar, char **av)
{
	t_philo	philo[PHILO_MAX];
	t_data	data;

	if (ar < 5 || ar > 6)
	{
		printf("Error: Invalid number of arguments.");
		return (1);
	}
	if (check_args(av, ar))
	{
		perror("ERROR");
		return (1);
	}
	init_values(&data, av, philo);
	init_forks(philo);
	init_philo(philo, &data);
	init_thread(philo);
	return (0);
}
